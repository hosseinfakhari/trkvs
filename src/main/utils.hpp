#include <string>
#include <vector>

#ifndef _KVS_UTILS
#define _KVS_UTILS

namespace TRKVS {

std::vector<std::string> split(std::string str, std::string token) {
    str.erase(str.find_last_not_of(' ') + 1);
    str.erase(0, str.find_first_not_of(' '));
    std::vector<std::string> result;
    while (str.size()) {
        int index = str.find(token);
        if (index != std::string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0) result.push_back(str);
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

template <typename T>
class InputValidator {
   public:
    virtual ~InputValidator(){};
    virtual InputValidator *setNext(InputValidator *nextValidator) = 0;
    virtual bool validate(T) = 0;
};

template <typename T>
class BaseValidator : public InputValidator<T> {
   protected:
    InputValidator<T> *next = nullptr;

   public:
    virtual ~BaseValidator() { delete next; }
    InputValidator<T> *setNext(InputValidator<T> *nextValidator) override {
        next = nextValidator;
        return next;
    }
    virtual bool validate(T testObject) override {
        if (this->next) {
            return this->next->validate(testObject);
        }
        return true;
    }
};

class NotEmptyValidator : public BaseValidator<std::string> {
   public:
    NotEmptyValidator() {}
    bool validate(std::string testString) {
        if (testString.empty()) {
            return false;
        }
        return BaseValidator::validate(testString);
    }
};

class CommandArgsValidator : public BaseValidator<std::vector<std::string>> {
    int validLength;

   public:
    CommandArgsValidator(int validLength) : validLength(validLength) {}
    bool validate(std::vector<std::string> testVector) {
        if (testVector.size() != validLength) {
            return false;
        }
        return BaseValidator::validate(testVector);
    }
};
}  // namespace TRKVS

#endif