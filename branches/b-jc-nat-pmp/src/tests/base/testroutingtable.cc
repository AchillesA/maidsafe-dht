/* Copyright (c) 2009 maidsafe.net limited
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    * Neither the name of the maidsafe.net limited nor the names of its
    contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>
#include "maidsafe/maidsafe-dht_config.h"

TEST(PDRoutingTableHandlerTest, BEH_BASE_AddTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  float rtt = 200;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 55555;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id, host_ip, host_port,
      rendezvous_ip, rendezvous_port, public_key, rtt, rank, space);
  base::PDRoutingTableHandler rt_handler;
  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store));
  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store));

  base::PDRoutingTableHandler rt_handler1;
  ASSERT_EQ(0, rt_handler1.AddTuple(tuple_to_store));
  ASSERT_EQ(0, rt_handler1.AddTuple(tuple_to_store));
  rt_handler.Clear();
  rt_handler1.Clear();
}

TEST(PDRoutingTableHandlerTest, BEH_BASE_ReadTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  float rtt = 200;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 55555;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id, host_ip, host_port,
      rendezvous_ip, rendezvous_port, public_key, rtt, rank, space);

  base::PDRoutingTableHandler rt_handler;

  base::PDRoutingTableTuple non_existing_tuple;
  ASSERT_EQ(1, rt_handler.GetTupleInfo(kademlia_id, &non_existing_tuple));
  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store));
  base::PDRoutingTableTuple retrieved_tuple;
  ASSERT_EQ(0, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ(tuple_to_store.kademlia_id(), retrieved_tuple.kademlia_id());
  ASSERT_EQ(tuple_to_store.rendezvous_ip(), retrieved_tuple.rendezvous_ip());
  ASSERT_EQ(tuple_to_store.rendezvous_port(),
    retrieved_tuple.rendezvous_port());
  ASSERT_EQ(tuple_to_store.public_key(), retrieved_tuple.public_key());
  ASSERT_EQ(tuple_to_store.rtt(), retrieved_tuple.rtt());
  ASSERT_EQ(tuple_to_store.rank(), retrieved_tuple.rank());
  ASSERT_EQ(tuple_to_store.space(), retrieved_tuple.space());

  base::PDRoutingTableTuple tuple_to_store1(kademlia_id, host_ip, host_port + 1,
      rendezvous_ip, rendezvous_port + 1, public_key, rtt + 1, rank, space + 1);

  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store1));
  base::PDRoutingTableTuple retrieved_tuple1;
  ASSERT_EQ(0, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple1));
  ASSERT_EQ(tuple_to_store1.kademlia_id(), retrieved_tuple1.kademlia_id());
  ASSERT_EQ(tuple_to_store1.rendezvous_ip(), retrieved_tuple1.rendezvous_ip());
  ASSERT_EQ(tuple_to_store1.rendezvous_port(),
    retrieved_tuple1.rendezvous_port());
  ASSERT_EQ(tuple_to_store1.public_key(), retrieved_tuple1.public_key());
  ASSERT_EQ(tuple_to_store1.rtt(), retrieved_tuple1.rtt());
  ASSERT_EQ(tuple_to_store1.rank(), retrieved_tuple1.rank());
  ASSERT_EQ(tuple_to_store1.space(), retrieved_tuple1.space());

  float prev_rtt = tuple_to_store1.rtt();
  tuple_to_store1.rtt_ = 0.0;
  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store1));
  base::PDRoutingTableTuple retrieved_tuple2;
  ASSERT_EQ(0, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple2));
  ASSERT_EQ(tuple_to_store1.kademlia_id(), retrieved_tuple2.kademlia_id());
  ASSERT_EQ(tuple_to_store1.rendezvous_ip(), retrieved_tuple2.rendezvous_ip());
  ASSERT_EQ(tuple_to_store1.rendezvous_port(),
    retrieved_tuple2.rendezvous_port());
  ASSERT_EQ(tuple_to_store1.public_key(), retrieved_tuple2.public_key());
  ASSERT_EQ(prev_rtt, retrieved_tuple2.rtt());
  ASSERT_EQ(tuple_to_store1.rank(), retrieved_tuple2.rank());
  ASSERT_EQ(tuple_to_store1.space(), retrieved_tuple2.space());

  rt_handler.Clear();
}

TEST(PDRoutingTableHandlerTest, BEH_BASE_DeleteTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  float rtt = 32;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 3232;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id, host_ip, host_port,
      rendezvous_ip, rendezvous_port, public_key, rtt, rank, space);

  base::PDRoutingTableHandler rt_handler;

  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store));
  base::PDRoutingTableTuple retrieved_tuple;
  ASSERT_EQ(0, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ(0, rt_handler.DeleteTupleByKadId(kademlia_id));
  ASSERT_EQ(1, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple));

  rt_handler.Clear();
}

TEST(PDRoutingTableHandlerTest, BEH_BASE_UpdateTuple) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  float rtt = 32;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 3232;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id, host_ip, host_port,
      rendezvous_ip, rendezvous_port, public_key, rtt, rank, space);
  base::PDRoutingTableHandler rt_handler;

  ASSERT_EQ(2, rt_handler.ContactLocal(kademlia_id));
  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store));
  ASSERT_EQ(2, rt_handler.ContactLocal(kademlia_id));
  ASSERT_EQ(0, rt_handler.UpdateHostIp(kademlia_id, "211.11.11.11"));
  ASSERT_EQ(0, rt_handler.UpdateHostPort(kademlia_id, 9999));
  ASSERT_EQ(0, rt_handler.UpdateRendezvousIp(kademlia_id, "86.11.11.11"));
  ASSERT_EQ(0, rt_handler.UpdateRendezvousPort(kademlia_id, 888));
  ASSERT_EQ(0, rt_handler.UpdatePublicKey(kademlia_id, "fafevcddc"));
  ASSERT_EQ(0, rt_handler.UpdateRtt(kademlia_id, 50));
  ASSERT_EQ(0, rt_handler.UpdateRank(kademlia_id, 10));
  ASSERT_EQ(0, rt_handler.UpdateSpace(kademlia_id, 6666));
  ASSERT_EQ(0, rt_handler.UpdateContactLocal(kademlia_id, "211.11.11.11", 0));
  ASSERT_EQ(0, rt_handler.ContactLocal(kademlia_id));
  base::PDRoutingTableTuple retrieved_tuple;
  ASSERT_EQ(0, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ("211.11.11.11", retrieved_tuple.host_ip());
  ASSERT_EQ(9999, retrieved_tuple.host_port());
  ASSERT_EQ("86.11.11.11", retrieved_tuple.rendezvous_ip());
  ASSERT_EQ(888, retrieved_tuple.rendezvous_port());
  ASSERT_EQ("fafevcddc", retrieved_tuple.public_key());
  ASSERT_EQ(static_cast<boost::uint32_t>(50), retrieved_tuple.rtt());
  ASSERT_EQ(static_cast<boost::uint16_t>(10), retrieved_tuple.rank());
  ASSERT_EQ(static_cast<boost::uint32_t>(6666), retrieved_tuple.space());
  ASSERT_EQ(0, rt_handler.UpdateContactLocal(kademlia_id, "210.11.11.11", 1));
  ASSERT_EQ(1, rt_handler.ContactLocal(kademlia_id));
  ASSERT_EQ(0, rt_handler.GetTupleInfo(kademlia_id, &retrieved_tuple));
  ASSERT_EQ("210.11.11.11", retrieved_tuple.host_ip());

  rt_handler.Clear();
}

TEST(PDRoutingTableHandlerTest, BEH_BASE_UpdateToUnknown) {
  std::string kademlia_id = base::RandomString(64);
  std::string host_ip("192.168.1.188");
  std::string local_ip("192.168.1.187");
  boost::uint16_t local_port = 7777;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  float rtt = 32;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 3232;
  base::PDRoutingTableTuple tuple_to_store(kademlia_id, local_ip, local_port,
      rendezvous_ip, rendezvous_port, public_key, rtt, rank, space);
  base::PDRoutingTableHandler rt_handler;
  ASSERT_EQ(2, rt_handler.ContactLocal(kademlia_id));
  ASSERT_EQ(0, rt_handler.AddTuple(tuple_to_store));
  ASSERT_EQ(2, rt_handler.ContactLocal(kademlia_id));
  ASSERT_EQ(0, rt_handler.UpdateContactLocal(kademlia_id, local_ip, 0));
  ASSERT_EQ(0, rt_handler.ContactLocal(kademlia_id));
  ASSERT_EQ(0, rt_handler.UpdateLocalToUnknown(local_ip, local_port));
  ASSERT_EQ(2, rt_handler.ContactLocal(kademlia_id));
  rt_handler.Clear();
}

TEST(PDRoutingTableHandlerTest, BEH_BASE_GetClosestRtt) {
  std::vector<base::PDRoutingTableTuple> tuples;
  tuples.push_back(base::PDRoutingTableTuple("id1", "192.168.1.188", 8888, "",
      0, "", 35.55, 1, 3232));
  tuples.push_back(base::PDRoutingTableTuple("id2", "192.168.1.186", 8889, "",
      0, "", 24.95, 1, 3232));
  tuples.push_back(base::PDRoutingTableTuple("id3", "192.168.1.188", 8890, "",
      0, "", 64.8, 1, 3232));
  tuples.push_back(base::PDRoutingTableTuple("id4", "192.168.1.187", 8891, "",
      0, "", 35.44, 1, 3232));
  tuples.push_back(base::PDRoutingTableTuple("id5", "192.168.1.190", 8892, "",
      0, "", 48.69, 1, 3232));
  base::PDRoutingTableHandler rt_handler;
  float rtt = 30;
  std::set<std::string> ex_ids;
  base::PDRoutingTableTuple rec_tuple;
  ASSERT_EQ(1, rt_handler.GetClosestRtt(rtt, ex_ids, &rec_tuple));
  for (unsigned int n = 0; n < tuples.size(); n++)
    ASSERT_EQ(0, rt_handler.AddTuple(tuples[n]));
  ASSERT_EQ(0, rt_handler.GetClosestRtt(rtt, ex_ids, &rec_tuple));
  ASSERT_EQ(tuples[1].kademlia_id_, rec_tuple.kademlia_id_);
  ASSERT_EQ(tuples[1].host_ip_, rec_tuple.host_ip_);
  ASSERT_EQ(tuples[1].rendezvous_ip_, rec_tuple.rendezvous_ip_);
  ASSERT_EQ(tuples[1].rendezvous_port_, rec_tuple.rendezvous_port_);
  ASSERT_EQ(tuples[1].rank_, rec_tuple.rank_);
  ASSERT_EQ(tuples[1].rtt_, rec_tuple.rtt_);
  ASSERT_EQ(tuples[1].space_, rec_tuple.space_);

  float distance = rtt - rec_tuple.rtt_;
  if (distance < 0)
    distance = distance * -1;

  for (unsigned int n = 0; n < tuples.size(); n++) {
    float tmp_distance = rtt - tuples[n].rtt_;
    if (tmp_distance < 0)
      tmp_distance = tmp_distance * -1;
    ASSERT_LE(distance, tmp_distance);
  }

  ex_ids.insert(rec_tuple.kademlia_id_);
  ASSERT_EQ(0, rt_handler.GetClosestRtt(rtt, ex_ids, &rec_tuple));
  ASSERT_EQ(tuples[3].kademlia_id_, rec_tuple.kademlia_id_);
  ASSERT_EQ(tuples[3].host_ip_, rec_tuple.host_ip_);
  ASSERT_EQ(tuples[3].rendezvous_ip_, rec_tuple.rendezvous_ip_);
  ASSERT_EQ(tuples[3].rendezvous_port_, rec_tuple.rendezvous_port_);
  ASSERT_EQ(tuples[3].rank_, rec_tuple.rank_);
  ASSERT_EQ(tuples[3].rtt_, rec_tuple.rtt_);
  ASSERT_EQ(tuples[3].space_, rec_tuple.space_);
  distance = rtt - rec_tuple.rtt_;
  if (distance < 0)
    distance = distance * -1;

  for (unsigned int n = 0; n < tuples.size(); n++) {
    if (ex_ids.find(tuples[n].kademlia_id_) == ex_ids.end()) {
      float tmp_distance = rtt - tuples[n].rtt_;
      if (tmp_distance < 0)
        tmp_distance = tmp_distance * -1;
      ASSERT_LE(distance, tmp_distance);
    }
  }

  rtt = tuples[4].rtt_;
  ASSERT_EQ(0, rt_handler.GetClosestRtt(rtt, ex_ids, &rec_tuple));
  ASSERT_EQ(tuples[4].kademlia_id_, rec_tuple.kademlia_id_);
  ASSERT_EQ(tuples[4].host_ip_, rec_tuple.host_ip_);
  ASSERT_EQ(tuples[4].rendezvous_ip_, rec_tuple.rendezvous_ip_);
  ASSERT_EQ(tuples[4].rendezvous_port_, rec_tuple.rendezvous_port_);
  ASSERT_EQ(tuples[4].rank_, rec_tuple.rank_);
  ASSERT_EQ(tuples[4].rtt_, rec_tuple.rtt_);
  ASSERT_EQ(tuples[4].space_, rec_tuple.space_);
}

TEST(PDRoutingTableTest, BEH_BASE_MultipleHandlers) {
  std::string dbname1("routingtable");
  dbname1 += boost::lexical_cast<std::string>(base::random_32bit_uinteger()) +
            std::string(".db");
  std::string dbname2("routingtable");
  dbname2 += boost::lexical_cast<std::string>(base::random_32bit_uinteger()) +
            std::string(".db");
  ASSERT_NE(dbname1, dbname2);
  std::string kademlia_id1 = base::RandomString(64);
  std::string kademlia_id2 = base::RandomString(64);
  ASSERT_NE(kademlia_id1, kademlia_id2);
  std::string host_ip("192.168.1.188");
  boost::uint16_t host_port = 8888;
  std::string rendezvous_ip("81.149.64.82");
  boost::uint16_t rendezvous_port = 5555;
  std::string public_key = base::RandomString(64);
  float rtt = 200;
  boost::uint16_t rank = 5;
  boost::uint32_t space = 55555;
  base::PDRoutingTableTuple tuple_to_store1(kademlia_id1, host_ip, host_port,
      rendezvous_ip, rendezvous_port, public_key, rtt, rank, space);
  ASSERT_EQ(0, (*base::PDRoutingTable::getInstance())[dbname1]->AddTuple(
      tuple_to_store1));
  base::PDRoutingTableTuple tuple_to_store2(kademlia_id2, host_ip, host_port-1,
      rendezvous_ip, rendezvous_port-1, public_key, rtt-100, rank-2, space);
  ASSERT_EQ(0, (*base::PDRoutingTable::getInstance())[dbname2]->AddTuple(
      tuple_to_store2));

  base::PDRoutingTableTuple rec_tuple_1, rec_tuple_2;
  ASSERT_EQ(1, (*base::PDRoutingTable::getInstance())[dbname1]->GetTupleInfo(
      kademlia_id2, &rec_tuple_1));
  ASSERT_EQ(0, (*base::PDRoutingTable::getInstance())[dbname1]->GetTupleInfo(
      kademlia_id1, &rec_tuple_1));
  ASSERT_EQ(tuple_to_store1.kademlia_id(), rec_tuple_1.kademlia_id());
  ASSERT_EQ(tuple_to_store1.rendezvous_ip(), rec_tuple_1.rendezvous_ip());
  ASSERT_EQ(tuple_to_store1.rendezvous_port(), rec_tuple_1.rendezvous_port());
  ASSERT_EQ(tuple_to_store1.public_key(), rec_tuple_1.public_key());
  ASSERT_EQ(tuple_to_store1.rtt(), rec_tuple_1.rtt());
  ASSERT_EQ(tuple_to_store1.rank(), rec_tuple_1.rank());
  ASSERT_EQ(tuple_to_store1.space(), rec_tuple_1.space());

  ASSERT_EQ(1, (*base::PDRoutingTable::getInstance())[dbname2]->GetTupleInfo(
      kademlia_id1, &rec_tuple_2));
  ASSERT_EQ(0, (*base::PDRoutingTable::getInstance())[dbname2]->GetTupleInfo(
      kademlia_id2, &rec_tuple_2));
  ASSERT_EQ(tuple_to_store2.kademlia_id(), rec_tuple_2.kademlia_id());
  ASSERT_EQ(tuple_to_store2.rendezvous_ip(), rec_tuple_2.rendezvous_ip());
  ASSERT_EQ(tuple_to_store2.rendezvous_port(), rec_tuple_2.rendezvous_port());
  ASSERT_EQ(tuple_to_store2.public_key(), rec_tuple_2.public_key());
  ASSERT_EQ(tuple_to_store2.rtt(), rec_tuple_2.rtt());
  ASSERT_EQ(tuple_to_store2.rank(), rec_tuple_2.rank());
  ASSERT_EQ(tuple_to_store2.space(), rec_tuple_2.space());
}