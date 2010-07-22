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

/*******************************************************************************
 * NOTE: This header is unlikely to have any breaking changes applied.         *
 *       However, it should not be regarded as finalised until this notice is  *
 *       removed.                                                              *
 ******************************************************************************/
/*
* TODO
* 1:  Allow Listening ports to be closed individually and as a group
* 2:  Create managed connection interface
* 3:  Add an Open method for rendezvous connections
* 4:  Create a ping at network level (in UDT this is a connect)
* 5:  Use managed connections for rendezvous
* 6:  Add tcp listen capability, may be another transport
* 7:  Provide a brodcast tcp method " " " " "
* 8:  When a knode can it will start a tcp listener on 80 and 443 and add this
*     to the contact tuple (prononced toople apparently :-) )
* 9:  Thread send including connect
* 10  Use thread pool
* 11: On thread pool filling up move all incoming connecitons to an async
*     connection method until a thread becomes available.
* 12: Complete NAT traversal management (use upnp, nat-pmp and hole punching)
*     allong prioratising of method type.
* 13: Use TCP to beackon on port 5483 when contact with kademlia network lost
* 14: Profile profile and profile. The send recive test should be under 100ms
*     preferrably less than 25ms.
* 15: Decide on how / when to fire the Stats signals
* 16: Provide channel level encryption (diffie Hellman -> AES xfer)
*/

#ifndef MAIDSAFE_TRANSPORT_TRANSPORTUDT_H_
#define MAIDSAFE_TRANSPORT_TRANSPORTUDT_H_

#include <boost/cstdint.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/detail/atomic_count.hpp>
#include <maidsafe/transport/transport.h>
#include <list>
#include <map>
#include <set>
#include <string>
#include "maidsafe/udt/udt.h"


namespace  bs2 = boost::signals2;
namespace  fs = boost::filesystem;

namespace transport {

class HolePunchingMessage;
// struct IncomingMessages;

typedef int UdtSocketId;

const int kDefaultSendTimeout(10000);  // milliseconds

struct UdtStats : public SocketPerformanceStats {
 public:
  enum UdtSocketType { kSend, kReceive };
  UdtStats(const UdtSocketId &udt_socket_id,
           const UdtSocketType &udt_socket_type)
      : udt_socket_id_(udt_socket_id),
        udt_socket_type_(udt_socket_type),
        performance_monitor_() {}
  ~UdtStats() {}
  UdtSocketId udt_socket_id_;
  UdtSocketType udt_socket_type_;
  UDT::TRACEINFO performance_monitor_;
};

class TransportUDT : public Transport {
 public:
  TransportUDT();
  ~TransportUDT();
  static void CleanUp();
  Port StartListening(const IP &ip,
                      const Port &port,
                      TransportCondition *transport_condition);
  bool StopListening(const Port &port);
  bool StopAllListening();
  // Create a hole to remote endpoint using rendezvous endpoint.
  TransportCondition PunchHole(const IP &remote_ip,
                               const Port &remote_port,
                               const IP &rendezvous_ip,
                               const Port &rendezvous_port);
  void Send(const TransportMessage &transport_message,
            const IP &remote_ip,
            const Port &remote_port,
            const int &response_timeout);
  // Convenience function - calls PunchHole followed by Send.
  void SendWithRendezvous(const TransportMessage &transport_message,
                          const IP &remote_ip,
                          const Port &remote_port,
                          const IP &rendezvous_ip,
                          const Port &rendezvous_port,
                          int &response_timeout,
                          SocketId *socket_id);
  void SendResponse(const TransportMessage &transport_message,
                    const SocketId &socket_id);
  // Used to send a file in response to a request received on socket_id.
  void SendFile(fs::path &path, const SocketId &socket_id);
  // Adds an endpoint that is checked at frequency milliseconds, or which keeps
  // alive the connection if frequency == 0.  Checking persists until
  // RemoveManagedEndpoint called, or endpoint is unavailable.
  // Return value is the socket id or -1 on error.  For frequency == 0 (implies
  // stay connected) the ManagedEndpointId can be used as the SocketId for
  // sending further messages.  For frequency > 0, new connections are
  // regularly made and broken, so ManagedEndpointId cannot be used as SocketId.
  // On failure to connect, retry_count further attempts at retry_frequency (ms)
  // are performed before failure.
  ManagedEndpointId AddManagedEndpoint(
      const IP &remote_ip,
      const Port &remote_port,
      const IP &rendezvous_ip,
      const Port &rendezvous_port,
      const boost::uint16_t &frequency,
      const boost::uint16_t &retry_count,
      const boost::uint16_t &retry_frequency);
  TransportCondition RemoveManagedEndpoint(
      const ManagedEndpointId &managed_endpoint_id);
 private:
  TransportUDT& operator=(const TransportUDT&);
  TransportUDT(const TransportUDT&);
  TransportCondition Connect(const IP &remote_ip,
                             const Port &remote_port,
                             SocketId * udt_socket_id);
  void AcceptConnection(const UdtSocketId &udt_socket_id);
  // General method for sending data
  TransportCondition SendData(const TransportMessage &transport_message,
                              const UdtSocketId &udt_socket_id,
                              const int &send_timeout,
                              const int &receive_timeout);
  // Send the size of the pending message
  TransportCondition SendDataSize(const TransportMessage &transport_message,
                                  const UdtSocketId &udt_socket_id);
  // Send the content of the message
  TransportCondition SendDataContent(const TransportMessage &transport_message,
                                     const UdtSocketId &udt_socket_id);
  // General method for receiving data
  void ReceiveData(const UdtSocketId &udt_socket_id,
                   const int &receive_timeout);
  // Receive the size of the forthcoming message
  DataSize ReceiveDataSize(const UdtSocketId &udt_socket_id);
  // Receive the content of the message
  bool ReceiveDataContent(const UdtSocketId &udt_socket_id,
                          const DataSize &data_size,
                          TransportMessage *transport_message);
  bool HandleTransportMessage(const TransportMessage &transport_message,
                              const UdtSocketId &udt_socket_id,
                              const float &rtt);
  void AsyncReceiveData(const UdtSocketId &udt_socket_id,
                        const int &timeout);
  // Check a socket can send data (close it otherwise)
  bool CheckSocketSend(const UdtSocketId &udt_socket_id);
  // Check a socket can receive data (close it otherwise)
  bool CheckSocketReceive(const UdtSocketId &udt_socket_id);
  // Check a socket can send or receive data (close it otherwise)
  bool CheckSocket(const UdtSocketId &udt_socket_id, bool send);
  std::vector<SocketId> ManagedEndpointIds_;






//  TransportType transport_type_;
//  IP rendezvous_ip_;
//  Port rendezvous_port_;
//  std::map<ConnectionId, IncomingData> incoming_sockets_;
//  std::list<OutgoingData> outgoing_queue_;
//  std::list<IncomingMessages> incoming_msgs_queue_;
//  boost::condition_variable send_cond_, ping_rend_cond_, recv_cond_;
//  boost::condition_variable msg_hdl_cond_;
//  bool ping_rendezvous_, directly_connected_/*, handle_non_transport_msgs_*/;
//  int accepted_connections_, msgs_sent_;
//  ConnectionId last_id_;
//  std::set<ConnectionId> data_arrived_;
//  std::map<ConnectionId, struct sockaddr> ips_from_connections_;
//  boost::function<void(const ConnectionId&, const bool&)> send_notifier_;
//  std::map<ConnectionId, UdtSocketId> send_sockets_;
//  static ConnectionId connection_id_;
//  boost::shared_array<char> data_;
};

}  // namespace transport

#endif  // MAIDSAFE_TRANSPORT_TRANSPORTUDT_H_

