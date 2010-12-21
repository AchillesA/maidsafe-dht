/* Copyright (c) 2010 maidsafe.net limited
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

//  #ifndef MAIDSAFE_TRANSPORT_TCP_TRANSPORT2_H_
//  #define MAIDSAFE_TRANSPORT_TCP_TRANSPORT2_H_
//
//  #include <boost/asio/io_service.hpp>
//  #include <boost/asio.hpp>
//  #include "transport2.h"
//  #include "tcp_connection2.h"
//  #include "tcp_connection_manager2.h"
//
//  using namespace boost::asio;
//
//  namespace transport {
//
//  class tcp_transport2 : public Transport2 {
//  public:
//    explicit tcp_transport2(io_service& ioservice_, const Endpoint &endpoint);
//      ~tcp_transport2();
//
//    /**
//    * Enables the transport to accept incoming communication. Fails if already
//    * listening or the requested endpoint is unavailable.
//    * @param e It is not NULL if an error has occured whcih may affect the operations in the method.
//    * @return Success or an appropriate error code.
//    */
//  
//    void accept_connection(const boost::system::error_code& e);
//    void start();
//    void stop();
//
//  private:
//    tcp_connection_manager2 tcp_connection_manager_;
//    tcp_connection_ptr connection_;
//    //Acceptor listens for incoming connections.
//    boost::asio::ip::tcp::acceptor acceptor_;
//  };
//
//  }  // namespace transport
//
//  #endif  // MAIDSAFE_TRANSPORT_TCPTRANSPORT2_H_
//  //  /**
//  //   * Sends the given message within an already established conversation.
//  //   * @param data The message data to transmit.
//  //   * @param conversation_id ID of the conversation to respond to.
//  //   * @param timeout Time after which to terminate a conversation.
//  //   */
//  //  virtual void Respond(const std::string &data,
//  //                       const ConversationId &conversation_id,
//  //                       const boost::posix_time::milliseconds &timeout);
//  //  /**
//  //   * Sends data that is being streamed from the given source.
//  //   * @param data The input stream delivering data to send.
//  //   * @param endpoint The data receiver's endpoint.
//  //   */
//  //  virtual void SendStream(const std::istream &data,
//  //                          const Endpoint &endpoint) = 0;
//  //
//  // private:
//  //
//  //};
//  //
//  //}  // namespace transport
//  //
//  //#endif  // MAIDSAFE_TRANSPORT_TcpTransport2_H_
