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
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include <gtest/gtest.h>
#include <google/protobuf/descriptor.h>
#include "base/calllatertimer.h"
#include "maidsafe/maidsafe-dht.h"
#include "protobuf/rpcmessage.pb.h"
#include "rpcprotocol/channelimpl.h"
#include "tests/rpcprotocol/testservices.pb.h"
#include "transport/transportapi.h"

class PingTestService : public tests::PingTest {
 public:
  void Ping(google::protobuf::RpcController *controller,
            const tests::PingRequest *request,
            tests::PingResponse *response,
            google::protobuf::Closure *done) {
    rpcprotocol::Controller *ctrler =
        static_cast<rpcprotocol::Controller*>(controller);
    if (request->IsInitialized()) {
      if (request->ping() == "ping") {
        response->set_result("S");
        response->set_pong("pong");
        printf("got ping request, returning response\n");
      } else {
        response->set_result("F");
        response->set_pong("");
      }
    }
    ctrler->set_remote_ip(request->ip());
    ctrler->set_remote_port(request->port());
    done->Run();
  }
};

class TestOpService : public tests::TestOp {
 public:
  void Add(google::protobuf::RpcController *controller,
           const tests::BinaryOpRequest *request,
           tests::BinaryOpResponse *response,
           google::protobuf::Closure *done) {
    if (request->IsInitialized())
      response->set_result(request->first() + request->second());
    rpcprotocol::Controller *ctrler =
        static_cast<rpcprotocol::Controller*>(controller);
    ctrler->set_remote_ip(request->ip());
    ctrler->set_remote_port(request->port());
    done->Run();
  }
  void Multiplyl(google::protobuf::RpcController *controller,
           const tests::BinaryOpRequest *request,
           tests::BinaryOpResponse *response,
           google::protobuf::Closure *done) {
    if (request->IsInitialized())
      response->set_result(request->first() * request->second());
    rpcprotocol::Controller *ctrler =
        static_cast<rpcprotocol::Controller*>(controller);
    ctrler->set_remote_ip(request->ip());
    ctrler->set_remote_port(request->port());
    done->Run();
  }
};

class MirrorTestService : public tests::MirrorTest {
 public:
  void Mirror(google::protobuf::RpcController *controller,
              const tests::StringMirrorRequest *request,
              tests::StringMirrorResponse *response,
              google::protobuf::Closure *done) {
    if (request->IsInitialized()) {
      std::string message(request->message());
      std::string inverted(request->message());
      int index = 0;
      printf("Before reversing the string.\n");
      for (int n = message.length() -1; n > -1 ; n--) {
        inverted[index] = message[n];
        index++;
      }
      printf("Done reversing the string.\n");
      response->set_mirrored_string(inverted);
    }
    rpcprotocol::Controller *ctrler =
        static_cast<rpcprotocol::Controller*>(controller);
    ctrler->set_remote_ip(request->ip());
    ctrler->set_remote_port(request->port());
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    done->Run();
  }
};

class ResultHolder {
 public:
  ResultHolder() : ping_res(), op_res(), mirror_res() {
    ping_res.set_result("");
    op_res.set_result(-1);
    mirror_res.set_mirrored_string("-");
  }
  void GetPingRes(const tests::PingResponse *response) {
    printf("printf received result -- waiting for 1 second\n");
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    if (response->IsInitialized()) {
      ping_res.set_result(response->result());
      ping_res.set_pong(response->pong());
    } else {
      ping_res.set_result("F");
    }
    printf("finished callback func\n");
  }
  void GetOpResult(const tests::BinaryOpResponse *response) {
    if (response->IsInitialized()) {
      op_res.set_result(response->result());
    } else {
      op_res.set_result(-2);
    }
  }
  void GetMirrorResult(const tests::StringMirrorResponse *response) {
    if (response->IsInitialized()) {
//      mirror_res.set_mirrored_string(response->mirrored_string());
      mirror_res.set_mirrored_string("Fraser");
    } else {
      mirror_res.set_mirrored_string("+");
    }
  }
  void Reset() {
    ping_res.Clear();
    ping_res.set_result("");
    op_res.Clear();
    op_res.set_result(-1);
    mirror_res.Clear();
    mirror_res.set_mirrored_string("-");
  }
  tests::PingResponse ping_res;
  tests::BinaryOpResponse op_res;
  tests::StringMirrorResponse mirror_res;
};

inline void HandleDeadServer(const bool &, const std::string &,
  const boost::uint16_t&) {}

class RpcProtocolTest : public testing::Test {
 protected:
  RpcProtocolTest() {}
  ~RpcProtocolTest() {}
  static void SetUpTestCase() {
    server_chann_manager = new rpcprotocol::ChannelManager();
    client_chann_manager = new rpcprotocol::ChannelManager();
  }
  static void TearDownTestCase() {
    delete client_chann_manager;
    delete server_chann_manager;
    UDT::cleanup();
  }
  virtual void SetUp() {
    server_chann_manager->StartTransport(35001,
      boost::bind(&HandleDeadServer, _1, _2, _3));
    server_chann_manager->ptransport()->StartPingRendezvous(true, "", 0);
    client_chann_manager->StartTransport(35002,
      boost::bind(&HandleDeadServer, _1, _2, _3));
    client_chann_manager->ptransport()->StartPingRendezvous(true, "", 0);
  }
  virtual void TearDown() {
    server_chann_manager->ClearChannels();
    client_chann_manager->ClearChannels();
    client_chann_manager->StopTransport();
    server_chann_manager->StopTransport();
  }
  static boost::shared_ptr<base::CallLaterTimer> stimer, ctimer;
  static rpcprotocol::ChannelManager *server_chann_manager,
                                     *client_chann_manager;
 private:
  RpcProtocolTest(const RpcProtocolTest&);
  RpcProtocolTest& operator=(const RpcProtocolTest&);
};

rpcprotocol::ChannelManager* RpcProtocolTest::server_chann_manager = NULL;
rpcprotocol::ChannelManager* RpcProtocolTest::client_chann_manager = NULL;

TEST_F(RpcProtocolTest, BEH_RPC_RegisterAChannel) {
  PingTestService *service = new PingTestService();
  // creating a channel for the service
  rpcprotocol::Channel *service_channel = new rpcprotocol::Channel(
      server_chann_manager);
  service_channel->SetService(service);
  server_chann_manager->RegisterChannel(service->GetDescriptor()->name(),
      service_channel);
  // creating a channel for the client to send a request to the service
  rpcprotocol::Controller controller;
  controller.set_timeout(5);
  rpcprotocol::Channel *out_channel =
      new rpcprotocol::Channel(client_chann_manager, "127.0.0.1", 35001, true);
  tests::PingTest* stubservice = new tests::PingTest::Stub(out_channel);
  tests::PingRequest req;
  tests::PingResponse resp;
  req.set_ping("ping");
  req.set_ip("127.0.0.1");
  req.set_port(35002);
  ResultHolder resultholder;
  google::protobuf::Closure *done = google::protobuf::NewCallback<ResultHolder,
      const tests::PingResponse*>(&resultholder, &ResultHolder::GetPingRes,
      &resp);
  stubservice->Ping(&controller, &req, &resp, done);
  while (resultholder.ping_res.result() == "")
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));

  ASSERT_EQ("S", resultholder.ping_res.result());
  ASSERT_TRUE(resultholder.ping_res.has_pong());
  ASSERT_EQ("pong", resultholder.ping_res.pong());
  delete service_channel;
  delete stubservice;
  delete out_channel;
  delete service;
}

TEST_F(RpcProtocolTest, BEH_RPC_MultipleChannelsRegistered) {
  PingTestService *service1 = new PingTestService();
  TestOpService *service2 = new TestOpService();
  MirrorTestService *service3 = new MirrorTestService();
  MirrorTestService *service4 = new MirrorTestService();
  // creating a channel for the service
  rpcprotocol::Channel *service_channel1 = new rpcprotocol::Channel(
      server_chann_manager);
  service_channel1->SetService(service1);
  server_chann_manager->RegisterChannel(service1->GetDescriptor()->name(),
      service_channel1);
  rpcprotocol::Channel *service_channel2 = new rpcprotocol::Channel(
      server_chann_manager);
  service_channel2->SetService(service2);
  server_chann_manager->RegisterChannel(service2->GetDescriptor()->name(),
      service_channel2);
  rpcprotocol::Channel *service_channel3 = new rpcprotocol::Channel(
      server_chann_manager);
  service_channel3->SetService(service3);
  server_chann_manager->RegisterChannel(service3->GetDescriptor()->name(),
      service_channel3);
  rpcprotocol::Channel *service_channel4 = new rpcprotocol::Channel(
      server_chann_manager);
  service_channel4->SetService(service4);
  server_chann_manager->RegisterChannel(service4->GetDescriptor()->name(),
      service_channel4);
  // creating a channel for the client to send a request to the service
  rpcprotocol::Controller controller;
  controller.set_timeout(5);
  rpcprotocol::Channel *out_channel =
      new rpcprotocol::Channel(client_chann_manager, "127.0.0.1", 35001, true);
  tests::PingTest* stubservice1 = new tests::PingTest::Stub(out_channel);
  tests::PingRequest req1;
  tests::PingResponse resp1;
  req1.set_ping("ping");
  req1.set_ip("127.0.0.1");
  req1.set_port(35002);
  ResultHolder resultholder;
  google::protobuf::Closure *done1 = google::protobuf::NewCallback<ResultHolder,
      const tests::PingResponse*>(&resultholder, &ResultHolder::GetPingRes,
      &resp1);
  stubservice1->Ping(&controller, &req1, &resp1, done1);
  while (resultholder.ping_res.result() == "") {
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  }
  ASSERT_EQ("S", resultholder.ping_res.result());
  ASSERT_TRUE(resultholder.ping_res.has_pong());
  ASSERT_EQ("pong", resultholder.ping_res.pong());
  resultholder.Reset();

  tests::TestOp* stubservice2 = new tests::TestOp::Stub(out_channel);
  tests::BinaryOpRequest req2;
  tests::BinaryOpResponse resp2;
  req2.set_first(3);
  req2.set_second(2);
  req2.set_ip("127.0.0.1");
  req2.set_port(35002);
  google::protobuf::Closure *done2 = google::protobuf::NewCallback<ResultHolder,
      const tests::BinaryOpResponse*>(&resultholder, &ResultHolder::GetOpResult,
      &resp2);
  rpcprotocol::Controller controller2;
  controller2.set_timeout(6);
  stubservice2->Add(&controller2, &req2, &resp2, done2);
  while (resultholder.op_res.result() == -1) {
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  }
  ASSERT_EQ(5, resultholder.op_res.result());

  tests::MirrorTest* stubservice3 = new tests::MirrorTest::Stub(out_channel);
  tests::StringMirrorRequest req3;
  tests::StringMirrorResponse resp3;
  req3.set_message(base::RandomString(5 * 1024 * 1024));
  req3.set_ip("127.0.0.1");
  req3.set_port(35002);
  google::protobuf::Closure *done3 = google::protobuf::NewCallback<ResultHolder,
      const tests::StringMirrorResponse*>(&resultholder,
      &ResultHolder::GetMirrorResult, &resp3);
  rpcprotocol::Controller controller3;
  controller3.set_timeout(1);
  stubservice3->Mirror(&controller3, &req3, &resp3, done3);
  while (resultholder.mirror_res.mirrored_string() == "-") {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
  }
  if ("+" != resultholder.mirror_res.mirrored_string()) {
    printf("did not timed out\n");
    FAIL();
  }
//  ASSERT_EQ("+", resultholder.mirror_res.mirrored_string()) <<
//    "Result of mirror wrong.";

  resultholder.Reset();
  tests::MirrorTest* stubservice4 = new tests::MirrorTest::Stub(out_channel);
  tests::StringMirrorRequest req4;
  tests::StringMirrorResponse resp4;
  req4.set_message(base::RandomString(5 * 1024 * 1024));
  req4.set_ip("127.0.0.1");
  req4.set_port(35002);
  google::protobuf::Closure *done4 = google::protobuf::NewCallback<ResultHolder,
      const tests::StringMirrorResponse*>(&resultholder,
      &ResultHolder::GetMirrorResult, &resp4);
  rpcprotocol::Controller controller4;
  controller4.set_timeout(20);
  stubservice4->Mirror(&controller4, &req4, &resp4, done4);
  while (resultholder.mirror_res.mirrored_string() == "-") {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
  }
  ASSERT_NE("+", resultholder.mirror_res.mirrored_string()) <<
    "Result of mirror wrong.";

  delete service_channel1;
  delete service_channel2;
  delete service_channel3;
  delete service_channel4;
  delete stubservice1;
  delete stubservice2;
  delete stubservice3;
  delete stubservice4;
  delete out_channel;
  delete service1;
  delete service2;
  delete service3;
  delete service4;
}

TEST_F(RpcProtocolTest, BEH_RPC_ServerAndClientAtSameTime) {
  TestOpService *service1 = new TestOpService();
  rpcprotocol::Channel *service_channel1 = new rpcprotocol::Channel(
      server_chann_manager);
  service_channel1->SetService(service1);
  server_chann_manager->RegisterChannel(service1->GetDescriptor()->name(),
      service_channel1);
  TestOpService *service2 = new TestOpService();
  rpcprotocol::Channel *service_channel2 = new rpcprotocol::Channel(
      client_chann_manager);
  service_channel2->SetService(service2);
  client_chann_manager->RegisterChannel(service2->GetDescriptor()->name(),
      service_channel2);
  rpcprotocol::Controller controller1;
  controller1.set_timeout(5);
  rpcprotocol::Controller controller2;
  controller2.set_timeout(5);
  rpcprotocol::Channel *out_channel1 =
      new rpcprotocol::Channel(server_chann_manager, "127.0.0.1", 35002, true);
  rpcprotocol::Channel *out_channel2 =
      new rpcprotocol::Channel(client_chann_manager, "127.0.0.1", 35001, true);
  tests::TestOp* stubservice1 = new tests::TestOp::Stub(out_channel1);
  tests::BinaryOpRequest req1;
  tests::BinaryOpResponse resp1;
  req1.set_first(3);
  req1.set_second(2);
  req1.set_ip("127.0.0.1");
  req1.set_port(35001);
  ResultHolder resultholder;
  google::protobuf::Closure *done1 = google::protobuf::NewCallback<ResultHolder,
      const tests::BinaryOpResponse*>(&resultholder, &ResultHolder::GetOpResult,
      &resp1);
  stubservice1->Add(&controller1, &req1, &resp1, done1);
  while (resultholder.op_res.result() == -1)
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  ASSERT_EQ(5, resultholder.op_res.result());
  resultholder.Reset();
  tests::TestOp* stubservice2 = new tests::TestOp::Stub(out_channel2);
  tests::BinaryOpRequest req2;
  tests::BinaryOpResponse resp2;
  req2.set_first(4);
  req2.set_second(4);
  req2.set_ip("127.0.0.1");
  req2.set_port(35002);
  google::protobuf::Closure *done2 = google::protobuf::NewCallback<ResultHolder,
      const tests::BinaryOpResponse*>(&resultholder, &ResultHolder::GetOpResult,
      &resp2);
  stubservice2->Multiplyl(&controller2, &req2, &resp2, done2);
  while (resultholder.op_res.result() == -1)
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  ASSERT_EQ(16, resultholder.op_res.result());
  delete service_channel1;
  delete service_channel2;
  delete stubservice1;
  delete stubservice2;
  delete out_channel1;
  delete out_channel2;
  delete service1;
  delete service2;
}

TEST_F(RpcProtocolTest, BEH_RPC_Timeout) {
  // creating a channel for the client to send a request to the service
  rpcprotocol::Controller controller;
  int timeout = 3;
  controller.set_timeout(timeout);
  rpcprotocol::Channel *out_channel =
      new rpcprotocol::Channel(client_chann_manager, "127.0.0.1", 35003, true);
  tests::PingTest* stubservice = new tests::PingTest::Stub(out_channel);
  tests::PingRequest req;
  tests::PingResponse resp;
  req.set_ping("ping");
  req.set_ip("127.0.0.1");
  req.set_port(35002);
  ResultHolder resultholder;
  google::protobuf::Closure *done = google::protobuf::NewCallback<ResultHolder,
      const tests::PingResponse*>(&resultholder, &ResultHolder::GetPingRes,
      &resp);
  stubservice->Ping(&controller, &req, &resp, done);
  boost::this_thread::sleep(boost::posix_time::seconds(timeout+1));
  ASSERT_EQ("F", resultholder.ping_res.result());
  ASSERT_FALSE(resultholder.ping_res.has_pong());
  delete out_channel;
  delete stubservice;
}
