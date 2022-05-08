#include "kvsmanager.hpp"

namespace TRKVS {

KVSManager::KVSManager() {
    dbstack.push_back(new KVS());
}

KVSManager::~KVSManager() {}

KVSManager &KVSManager::getInstance() {
    static KVSManager instance;
    return instance;
}

std::string KVSManager::get_item(std::string key) {
    std::list<KVS *>::reverse_iterator it;
    std::string value;
    for (it = dbstack.rbegin(); it != dbstack.rend(); it++) {
        value = (*it)->get_item(key);
        if (!value.empty()) {
            return value;
        }
    }
    return "key not set";
}

void KVSManager::set_item(std::string key, std::string value) {
    currentKVS = dbstack.back();
    currentKVS->set_item(key, value);
}

void KVSManager::delete_item(std::string key) {
    currentKVS = dbstack.back();
    currentKVS->delete_item(key);
}

int KVSManager::count_item(std::string value) {
    int count = 0;
    std::list<KVS *>::iterator it;
    for (it = dbstack.begin(); it != dbstack.end(); it++) {
        count += (*it)->count_of(value);
    }
    return count;
}

void KVSManager::begin_transaction() {
    dbstack.push_back(new KVS());
}

void KVSManager::commit_transaction() {
    if (dbstack.size() <= 1) {
        std::cout << "no transaction" << std::endl;
        return;
    }
    currentKVS = dbstack.back();
    std::list<KVS *>::iterator it = dbstack.end();
    it--;
    it--;
    KVS *destKVS = *it;
    std::vector<std::string> keys = currentKVS->get_keys();
    for (auto key : keys) {
        std::string value = currentKVS->get_item(key);
        destKVS->set_item(key, value);
    }
    dbstack.pop_back();
}

void KVSManager::rollback_transaction() {
    if (dbstack.size() <= 1) {
        std::cout << "no transaction" << std::endl;
        return;
    }
    dbstack.pop_back();
}

}  // namespace TRKVS