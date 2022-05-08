#include <iostream>
#include <list>
#include <string>

#include "kvs.hpp"

#ifndef _KVS_MANAGER
#define _KVS_MANAGER

namespace TRKVS {
class KVSManager {
    std::list<KVS*> dbstack;
    KVS* currentKVS;

    KVSManager();

   public:
    KVSManager(const KVSManager&) = delete;
    KVSManager(KVSManager&&) = delete;
    KVSManager& operator=(const KVSManager&) = delete;
    KVSManager& operator=(KVSManager&&) = delete;
    ~KVSManager();
    std::string get_item(std::string key);
    void set_item(std::string key, std::string value);
    void delete_item(std::string key);
    int count_item(std::string value);
    void begin_transaction();
    void commit_transaction();
    void rollback_transaction();

    static KVSManager& getInstance();
};

}  // namespace TRKVS
#endif