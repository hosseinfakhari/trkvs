#include "gtest/gtest.h"

#include "src/lib/kvs.hpp"

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