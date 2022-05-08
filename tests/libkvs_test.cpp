#include "gtest/gtest.h"

#include "src/lib/kvs.hpp"
#include "src/lib/kvsmanager.hpp"

TEST(KVSLibTest, BasicKVSFunctions) {
  TRKVS::KVS kvs;
  
  kvs.set_item("name", "hossein");
  EXPECT_EQ("hossein", kvs.get_item("name"));
  
  kvs.set_item("username", "hossein");
  EXPECT_EQ(2, kvs.count_of("hossein"));
  
  kvs.delete_item("name");
  auto keys = kvs.get_keys();
  EXPECT_EQ(keys[0], "username");
}

TEST(KVSManager, KVSManagerBasicFunctionalities) {
  TRKVS::KVSManager *manager = &TRKVS::KVSManager::getInstance();
  manager->set_item("name", "hossein");
  EXPECT_EQ("hossein", manager->get_item("name"));
  
  manager->set_item("username", "hossein");
  EXPECT_EQ(2, manager->count_item("hossein"));
  
  manager->delete_item("name");
  EXPECT_EQ(manager->get_item("name"), "key not set");
}

TEST(KVSManager, KVSManagerTransactionTest) {
  TRKVS::KVSManager *manager = &TRKVS::KVSManager::getInstance();
  
  manager->set_item("name", "hossein");
  EXPECT_EQ("hossein", manager->get_item("name"));

  manager->begin_transaction();
  manager->set_item("name", "fakhari");
  EXPECT_EQ("fakhari", manager->get_item("name"));
  manager->rollback_transaction();
  EXPECT_EQ("hossein", manager->get_item("name"));

  manager->begin_transaction();
  manager->set_item("name", "fakhari");
  EXPECT_EQ("fakhari", manager->get_item("name"));
  manager->commit_transaction();
  EXPECT_EQ("fakhari", manager->get_item("name"));
}


TEST(KVSManager, KVSManagerNestedTransactionTest) {
  TRKVS::KVSManager *manager = &TRKVS::KVSManager::getInstance();
  
  manager->set_item("name", "hossein");
  EXPECT_EQ("hossein", manager->get_item("name"));

  manager->begin_transaction();
  manager->set_item("name", "fakhari");
  EXPECT_EQ("fakhari", manager->get_item("name"));
  manager->rollback_transaction();
  EXPECT_EQ("hossein", manager->get_item("name"));

  manager->begin_transaction();
  manager->set_item("name", "zahra");
  EXPECT_EQ("zahra", manager->get_item("name"));
  manager->begin_transaction();
  manager->set_item("name", "hossein");
  EXPECT_EQ("hossein", manager->get_item("name"));
  manager->rollback_transaction();
  manager->commit_transaction();
  EXPECT_EQ("zahra", manager->get_item("name"));
}