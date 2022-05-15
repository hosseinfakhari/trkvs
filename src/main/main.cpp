#include <iostream>

#include "src/main/utils.hpp"
#include "src/lib/kvsmanager.hpp"

using namespace TRKVS;

int main(int argc, char **argv) {
    KVSManager *kvsm = &KVSManager::getInstance();

    std::string input;
    std::vector<std::string> args;

    std::cout << "> ";
    while (std::getline(std::cin, input)) {
        if (input.size() <= 1) continue;
        args.clear();
        args = split(input, " ");
        for(auto item: args) {
            std::cout << item << " ";
        } std::cout << std::endl;
        std::cout << "> ";
    }
}