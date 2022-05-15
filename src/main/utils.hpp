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
}  // namespace TRKVS

#endif