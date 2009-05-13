/*
 * copyright maidsafe.net limited 2008
 * The following source code is property of maidsafe.net limited and
 * is not meant for external use. The use of this code is governed
 * by the license file LICENSE.TXT found in teh root of this directory and also
 * on www.maidsafe.net.
 *
 * You are not free to copy, amend or otherwise use this source code without
 * explicit written permission of the board of directors of maidsafe.net
 *
 *  Created on: Mar 11, 2009
 *      Author: haiyang
 */

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include "base/utils.h"
#include "base/routingtable.h"

class PDRoutingTableHandlerTest: public testing::Test {
 protected:
  PDRoutingTableHandlerTest() {
  }
  virtual ~PDRoutingTableHandlerTest() {
  }
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

//TEST_F(PDRoutingTableHandlerTest, ConnectAndCloseRoutingtable) {
//  base::PDRoutingTableHandler routingtable;
//  ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
//  ASSERT_EQ(0, routingtable.Close());
//  try {
//    boost::filesystem::remove(boost::filesystem::path("routingtable.db"));
//  } catch(std::exception &) {}
//}

TEST_F(PDRoutingTableHandlerTest, AddTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  boost::uint32_t rtt = 200;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 55555;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id,
                                     host_ip,
                                     host_port,
                                     rendezvous_ip,
                                     rendezvous_port,
                                     public_key,
                                     rtt,
                                     rank,
                                     space);
  base::PDRoutingTableHandler routingtable;
  // ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
  ASSERT_EQ(0, routingtable.AddTuple(tuple_to_store));
  ASSERT_EQ(0, routingtable.AddTuple(tuple_to_store));
//  ASSERT_EQ(0, routingtable.Close());
  try {
    boost::filesystem::remove(boost::filesystem::path("routingtable.db"));
  } catch(std::exception &) {}
  base::PDRoutingTableHandler routingtable1("routingtable1.db");
  // ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
  ASSERT_EQ(0, routingtable1.AddTuple(tuple_to_store));
  ASSERT_EQ(0, routingtable1.AddTuple(tuple_to_store));
  routingtable.Clear();
  routingtable1.Clear();
}

TEST_F(PDRoutingTableHandlerTest, ReadTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  boost::uint32_t rtt = 200;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 55555;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id,
                                     host_ip,
                                     host_port,
                                     rendezvous_ip,
                                     rendezvous_port,
                                     public_key,
                                     rtt,
                                     rank,
                                     space);
  base::PDRoutingTableHandler routingtable;
  // ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
  base::PDRoutingTableTuple non_existing_tuple;
  ASSERT_EQ(1, routingtable.GetTupleInfo(kademlia_id, &non_existing_tuple));
  ASSERT_EQ(0, routingtable.AddTuple(tuple_to_store));
  base::PDRoutingTableTuple retrieved_tuple;
  ASSERT_EQ(0, routingtable.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ(tuple_to_store.kademlia_id(), retrieved_tuple.kademlia_id());
  ASSERT_EQ(tuple_to_store.rendezvous_ip(), retrieved_tuple.rendezvous_ip());
  ASSERT_EQ(tuple_to_store.rendezvous_port(),
    retrieved_tuple.rendezvous_port());
  ASSERT_EQ(tuple_to_store.public_key(), retrieved_tuple.public_key());
  ASSERT_EQ(tuple_to_store.rtt(), retrieved_tuple.rtt());
  ASSERT_EQ(tuple_to_store.rank(), retrieved_tuple.rank());
  ASSERT_EQ(tuple_to_store.space(), retrieved_tuple.space());

  base::PDRoutingTableTuple tuple_to_store1(kademlia_id,
                                     host_ip,
                                     host_port + 1,
                                     rendezvous_ip,
                                     rendezvous_port + 1,
                                     public_key,
                                     rtt + 1,
                                     rank,
                                     space + 1);
  // ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
  ASSERT_EQ(0, routingtable.AddTuple(tuple_to_store1));
  base::PDRoutingTableTuple retrieved_tuple1;
  ASSERT_EQ(0, routingtable.GetTupleInfo(kademlia_id, &retrieved_tuple1));
  ASSERT_EQ(tuple_to_store1.kademlia_id(), retrieved_tuple1.kademlia_id());
  ASSERT_EQ(tuple_to_store1.rendezvous_ip(), retrieved_tuple1.rendezvous_ip());
  ASSERT_EQ(tuple_to_store1.rendezvous_port(),
    retrieved_tuple1.rendezvous_port());
  ASSERT_EQ(tuple_to_store1.public_key(), retrieved_tuple1.public_key());
  ASSERT_EQ(tuple_to_store1.rtt(), retrieved_tuple1.rtt());
  ASSERT_EQ(tuple_to_store1.rank(), retrieved_tuple1.rank());
  ASSERT_EQ(tuple_to_store1.space(), retrieved_tuple1.space());
  // ASSERT_EQ(0, routingtable.Close());
  try {
    boost::filesystem::remove(boost::filesystem::path("routingtable.db"));
  } catch(std::exception &) {}
  routingtable.Clear();
}

TEST_F(PDRoutingTableHandlerTest, DeleteTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  boost::uint32_t rtt = 32;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 3232;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id,
                                     host_ip,
                                     host_port,
                                     rendezvous_ip,
                                     rendezvous_port,
                                     public_key,
                                     rtt,
                                     rank,
                                     space);
  base::PDRoutingTableHandler routingtable;
  // ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
  ASSERT_EQ(0, routingtable.AddTuple(tuple_to_store));
  base::PDRoutingTableTuple retrieved_tuple;
  ASSERT_EQ(0, routingtable.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ(0, routingtable.DeleteTupleByKadId(kademlia_id));
  ASSERT_EQ(1, routingtable.GetTupleInfo(kademlia_id, &retrieved_tuple));
  // ASSERT_EQ(0, routingtable.Close());
  try {
    boost::filesystem::remove(boost::filesystem::path("routingtable.db"));
  } catch(std::exception &) {}
  routingtable.Clear();
}

TEST_F(PDRoutingTableHandlerTest, UpdateTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  boost::uint32_t rtt = 32;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 3232;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id,
                                     host_ip,
                                     host_port,
                                     rendezvous_ip,
                                     rendezvous_port,
                                     public_key,
                                     rtt,
                                     rank,
                                     space);
  base::PDRoutingTableHandler routingtable;
  // ASSERT_EQ(0, routingtable.Connect("routingtable.db"));
  ASSERT_EQ(2, routingtable.ContactLocal(kademlia_id));
  ASSERT_EQ(0, routingtable.AddTuple(tuple_to_store));
  ASSERT_EQ(2, routingtable.ContactLocal(kademlia_id));
  ASSERT_EQ(0, routingtable.UpdateHostIp(kademlia_id, "211.11.11.11"));
  ASSERT_EQ(0, routingtable.UpdateHostPort(kademlia_id, 9999));
  ASSERT_EQ(0, routingtable.UpdateRendezvousIp(kademlia_id, "86.11.11.11"));
  ASSERT_EQ(0, routingtable.UpdateRendezvousPort(kademlia_id, 888));
  ASSERT_EQ(0, routingtable.UpdatePublicKey(kademlia_id, "fafevcddc"));
  ASSERT_EQ(0, routingtable.UpdateRtt(kademlia_id, 50));
  ASSERT_EQ(0, routingtable.UpdateRank(kademlia_id, 10));
  ASSERT_EQ(0, routingtable.UpdateSpace(kademlia_id, 6666));
  ASSERT_EQ(0, routingtable.UpdateContactLocal(kademlia_id, 0));
  ASSERT_EQ(0, routingtable.ContactLocal(kademlia_id));
  base::PDRoutingTableTuple retrieved_tuple;
  ASSERT_EQ(0, routingtable.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ("211.11.11.11", retrieved_tuple.host_ip());
  ASSERT_EQ(9999, retrieved_tuple.host_port());
  ASSERT_EQ("86.11.11.11", retrieved_tuple.rendezvous_ip());
  ASSERT_EQ(888, retrieved_tuple.rendezvous_port());
  ASSERT_EQ("fafevcddc", retrieved_tuple.public_key());
  ASSERT_EQ(static_cast<boost::uint32_t>(50), retrieved_tuple.rtt());
  ASSERT_EQ(static_cast<boost::uint16_t>(10), retrieved_tuple.rank());
  ASSERT_EQ(static_cast<boost::uint32_t>(6666), retrieved_tuple.space());
  // ASSERT_EQ(0, routingtable.Close());
  try {
    boost::filesystem::remove(boost::filesystem::path("routingtable.db"));
  } catch(std::exception &) {}
  routingtable.Clear();
}