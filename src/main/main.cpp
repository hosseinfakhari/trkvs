#include <iostream>

#include "src/main/utils.hpp"
#include "src/main/commands.hpp"
#include "src/lib/kvsmanager.hpp"

using namespace TRKVS;

int main(int argc, char **argv) {
    KVSManager *kvsm = &KVSManager::getInstance();

    std::string input;
    std::vector<std::string> args;

    CommandFactory commandFactory(kvsm);

    std::cout << "> ";
    while (std::getline(std::cin, input)) {
        if (input.size() <= 1) continue;
        args.clear();
        args = split(input, " ");
        auto command = commandFactory.createCommand(args);
        command->execute();
        delete command;
        std::cout << "> ";
    }
}