#include "src/lib/kvsmanager.hpp"
#include "src/main/utils.hpp"

#ifndef _KVS_COMMANDS
#define _KVS_COMMANDS

namespace TRKVS {
class ICommand {
   public:
    virtual ~ICommand(){};
    virtual void execute() = 0;
};

class SetCommand : public ICommand {
    KVSManager *kvsm;
    std::vector<std::string> args;
    SetCommand();

   public:
    SetCommand(KVSManager *kvsm, std::vector<std::string> args) : kvsm(kvsm), args(args) {}
    void execute() {
        InputValidator<std::vector<std::string>> *setCommandInputValidator = new BaseValidator<std::vector<std::string>>;
        setCommandInputValidator->setNext(new CommandArgsValidator(3));
        InputValidator<std::string> *setCommandValidator = new BaseValidator<std::string>();
        setCommandValidator->setNext(new NotEmptyValidator);
        if (setCommandValidator->validate(args[1]) && setCommandInputValidator->validate(args)) {
            kvsm->set_item(args[1], args[2]);
        } else {
            std::cout << "Error: you should provice <key> and <value>" << std::endl;
        }
        delete setCommandInputValidator;
        delete setCommandValidator;
    }
};

class GetCommand : public ICommand {
    KVSManager *kvsm;
    std::vector<std::string> args;
    GetCommand();

   public:
    GetCommand(KVSManager *kvsm, std::vector<std::string> args) : kvsm(kvsm), args(args) {}
    void execute() {
        InputValidator<std::vector<std::string>> *inputValidator = new BaseValidator<std::vector<std::string>>;
        inputValidator->setNext(new CommandArgsValidator(2));
        if (inputValidator->validate(args)) {
            std::cout << kvsm->get_item(args[1]) << std::endl;
        } else {
            std::cerr << "Error: you should specify the key for lookup!" << std::endl;
        }
        delete inputValidator;
    }
};

class DeleteCommand : public ICommand {
    KVSManager *kvsm;
    std::vector<std::string> args;
    DeleteCommand();

   public:
    DeleteCommand(KVSManager *kvsm, std::vector<std::string> args) : kvsm(kvsm), args(args) {}
    void execute() {
        InputValidator<std::vector<std::string>> *inputValidator = new BaseValidator<std::vector<std::string>>;
        inputValidator->setNext(new CommandArgsValidator(2));
        if (inputValidator->validate(args)) {
            kvsm->delete_item(args[1]);
        } else {
            std::cerr << "Error: you should specify the key for deletion!" << std::endl;
        }
        delete inputValidator;
    }
};

class CountCommand : public ICommand {
    KVSManager *kvsm;
    std::vector<std::string> args;
    CountCommand();

   public:
    CountCommand(KVSManager *kvsm, std::vector<std::string> args) : kvsm(kvsm), args(args) {}
    void execute() {
        InputValidator<std::vector<std::string>> *inputValidator = new BaseValidator<std::vector<std::string>>;
        inputValidator->setNext(new CommandArgsValidator(2));
        if (inputValidator->validate(args)) {
            std::cout << kvsm->count_item(args[1]) << std::endl;
        } else {
            std::cerr << "Error: you should specify the value for counting!" << std::endl;
        }
        delete inputValidator;
    }
};

class BeginTransactionCommand : public ICommand {
    KVSManager *kvsm;
    BeginTransactionCommand();

   public:
    BeginTransactionCommand(KVSManager *kvsm) : kvsm(kvsm) {}
    void execute() {
        kvsm->begin_transaction();
    }
};

class CommitTransactionCommand : public ICommand {
    KVSManager *kvsm;
    CommitTransactionCommand();

   public:
    CommitTransactionCommand(KVSManager *kvsm) : kvsm(kvsm) {}
    void execute() {
        kvsm->commit_transaction();
    }
};

class RollbackTransactionCommand : public ICommand {
    KVSManager *kvsm;
    RollbackTransactionCommand();

   public:
    RollbackTransactionCommand(KVSManager *kvsm) : kvsm(kvsm) {}
    void execute() {
        kvsm->rollback_transaction();
    }
};

class ExitCommand : public ICommand {
   public:
    void execute() {
        exit(0);
    }
};

class NotFoundCommand : public ICommand {
   public:
    void execute() {
        std::cout << "Command Not Found!" << std::endl;
    }
};

class CommandFactory {
    KVSManager *kvsm;
    CommandFactory();

   public:
    CommandFactory(KVSManager *kvsm) : kvsm(kvsm) {}
    ICommand *createCommand(std::vector<std::string> arguments) {
        auto cmd = arguments[0];
        for (auto &c : cmd) {
            c = tolower(c);
        }
        if (cmd == "set") {
            return new SetCommand(kvsm, arguments);
        } else if (cmd == "get") {
            return new GetCommand(kvsm, arguments);
        } else if (cmd == "delete") {
            return new DeleteCommand(kvsm, arguments);
        } else if (cmd == "count") {
            return new CountCommand(kvsm, arguments);
        } else if (cmd == "begin") {
            return new BeginTransactionCommand(kvsm);
        } else if (cmd == "commit") {
            return new CommitTransactionCommand(kvsm);
        } else if (cmd == "rollback") {
            return new RollbackTransactionCommand(kvsm);
        } else if (cmd == "exit") {
            return new ExitCommand();
        } else {
            return new NotFoundCommand();
        }
    }
};
}  // namespace TRKVS

#endif