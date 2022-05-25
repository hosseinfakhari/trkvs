#include "kvs.hpp"

namespace TRKVS {
const std::vector<std::string> KVS::get_keys() {
    std::vector<std::string> vkeys;
    for (auto it = keys.begin(); it != keys.end(); ++it) {
        vkeys.push_back((*it).first);
    }
    return vkeys;
}

void KVS::set_item(const std::string key, const std::string value) {
    std::unordered_map<std::string, int>::iterator val;
    if (keys.find(key) != keys.end()) {
        this->delete_item(key);
    }
    if (values.find(value) == values.end()) {
        values[value] = 1;
    } else {
        values[value] += 1;
    }
    val = values.find(value);
    keys[key] = val;
}

const std::string KVS::get_item(const std::string key) {
    if (keys.find(key) != keys.end()) {
        return keys[key]->first;
    }
    return "";
}

void KVS::delete_item(const std::string key) {
    if (keys.find(key) == keys.end()) {
        return;
    }
    auto item = keys.find(key);
    const std::string item_value = item->second->first;
    item->second->second -= 1;
    if (item->second->second == 0) {
        values.erase(item_value);
    }
    keys.erase(item);
}

const int KVS::count_of(std::string val) {
    return values[val];
}
}  // namespace TRKVS