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

#include "maidsafe/base/utils.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_array.hpp>
#include <ctype.h>
#include <maidsafe/cryptopp/integer.h>
#include <maidsafe/cryptopp/osrng.h>
#include <maidsafe/cryptopp/hex.h>
#include <algorithm>
#include <limits>
#include <string>
#include "maidsafe/base/log.h"
#include "maidsafe/base/network_interface.h"

namespace base {

boost::int32_t RandomInt32() {
  boost::int32_t result(0);
  bool success = false;
  while (!success) {
    try {
      CryptoPP::AutoSeededRandomPool rng;
      CryptoPP::Integer rand_num(rng, 32);
      if (rand_num.IsConvertableToLong()) {
        result =  static_cast<boost::int32_t>(
            rand_num.AbsoluteValue().ConvertToLong());
        success = true;
      }
    }
    catch(...) {}
  }
  return result;
}

boost::uint32_t RandomUint32() {
  boost::uint32_t result(0);
  bool success = false;
  while (!success) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::Integer rand_num(rng, 32);
//     CryptoPP::LC_RNG(GetEpochNanoseconds()) rng;
    if (rand_num.IsConvertableToLong()) {
      result = static_cast<boost::uint32_t>(
          rand_num.AbsoluteValue().ConvertToLong());
      success = true;
    }
    catch(...) {}
  }
  return result;
}

std::string IntToString(const int &value) {
  std::string str_value(boost::lexical_cast<std::string>(value));
  return str_value;
}

std::string RandomString(const boost::uint32_t &length) {
  std::string random_string;
  random_string.reserve(length);
  try {
    CryptoPP::AutoSeededRandomPool random_number_generator;
    while (random_string.size() < length) {
      boost::uint32_t iter_length =
        std::min(static_cast<boost::uint32_t>(length - random_string.size()),
                 boost::uint32_t(65536));
      boost::scoped_array<byte> random_bytes(new byte[iter_length]);
      random_number_generator.GenerateBlock(random_bytes.get(), iter_length);
      std::string random_substring(random_bytes.get(),
                                   random_bytes.get() + iter_length);
      for (boost::uint32_t i = 0; i < iter_length; ++i) {
        boost::uint8_t *random_char =
            reinterpret_cast<boost::uint8_t*>(&random_substring.at(i));
        *random_char = *random_char % 122;
        if (48 > *random_char)
          *random_char += 48;
        if ((57 < *random_char) && (65 > *random_char))
          *random_char += 7;
        if ((90 < *random_char) && (97 > *random_char))
          *random_char += 6;
      }
      random_string += random_substring;
    }
  }
  catch(...) {}

  return random_string;
}

std::string EncodeToHex(const std::string &non_hex_input) {
  std::string hex_output;
  CryptoPP::StringSource(non_hex_input, true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(hex_output), false));
  return hex_output;
}

std::string DecodeFromHex(const std::string &hex_input) {
  std::string non_hex_output;
  CryptoPP::StringSource(hex_input, true,
      new CryptoPP::HexDecoder(new CryptoPP::StringSink(non_hex_output)));
  return non_hex_output;
}

boost::uint32_t GetEpochTime() {
  boost::posix_time::ptime
      t(boost::posix_time::microsec_clock::universal_time());
  boost::posix_time::ptime start(boost::gregorian::date(2000, 1, 1));
  return static_cast<boost::uint32_t>((t-start).total_seconds());
}

boost::uint64_t GetEpochMilliseconds() {
  boost::posix_time::ptime
      t(boost::posix_time::microsec_clock::universal_time());
  boost::posix_time::ptime start(boost::gregorian::date(2000, 1, 1));
  return static_cast<boost::uint64_t>((t - start).total_milliseconds());
}

boost::uint64_t GetEpochNanoseconds() {
  boost::posix_time::ptime
      t(boost::posix_time::microsec_clock::universal_time());
  boost::posix_time::ptime start(boost::gregorian::date(2000, 1, 1));
  return static_cast<boost::uint64_t>((t - start).total_nanoseconds());
}

boost::uint32_t GenerateNextTransactionId(const boost::uint32_t &id) {
  boost::uint32_t next_id;
  boost::uint32_t max_id = 2147483646;
  if (id == 0) {
    next_id = (RandomInt32() + GetEpochTime() % 10000) % max_id;
    if (next_id == 0)
      next_id = 1;
  } else {
    next_id = (id + 1) % max_id;
    if (next_id == 0)
      next_id = 1;
  }
  return next_id;
}

std::string IpAsciiToBytes(const std::string &decimal_ip) {
  try {
    boost::asio::ip::address host_ip =
        boost::asio::ip::address::from_string(decimal_ip);
    if (host_ip.is_v4()) {
      boost::asio::ip::address_v4::bytes_type addr = host_ip.to_v4().to_bytes();
      std::string result(addr.begin(), addr.end());
      return result;
    } else if (host_ip.is_v6()) {
      boost::asio::ip::address_v6::bytes_type addr = host_ip.to_v6().to_bytes();
      std::string result(addr.begin(), addr.end());
      return result;
    }
  }
  catch(const std::exception &e) {
    DLOG(ERROR) << e.what() << std::endl;
  }
  return "";
}

std::string IpBytesToAscii(const std::string &bytes_ip) {
  try {
    if (bytes_ip.size() == 4) {
      boost::asio::ip::address_v4::bytes_type bytes_type_ip;
      for (int i = 0; i < 4; ++i)
        bytes_type_ip[i] = bytes_ip.at(i);
      boost::asio::ip::address_v4 address(bytes_type_ip);
      return address.to_string();
    } else if (bytes_ip.size() == 16) {
      boost::asio::ip::address_v6::bytes_type bytes_type_ip;
      for (int i = 0; i < 16; ++i)
        bytes_type_ip[i] = bytes_ip.at(i);
      *bytes_type_ip.c_array() = *bytes_ip.c_str();
      boost::asio::ip::address_v6 address(bytes_type_ip);
      return address.to_string();
    }
  }
  catch(const std::exception &e) {
     DLOG(ERROR) << e.what() << std::endl;
  }
  return "";
}

void IpNetToAscii(boost::uint32_t address, char *ip_buffer) {
  // TODO(dan): warning thrown on 64-bit machine
  const int sizer = 15;
  #ifdef __MSVC__
    _snprintf(ip_buffer, sizer, "%u.%u.%u.%u", (address>>24)&0xFF,
        (address>>16)&0xFF, (address>>8)&0xFF, (address>>0)&0xFF);
  #else
    snprintf(ip_buffer, sizer, "%u.%u.%u.%u", (address>>24)&0xFF,
        (address>>16)&0xFF, (address>>8)&0xFF, (address>>0)&0xFF);
  #endif
}

boost::uint32_t IpAsciiToNet(const char *buffer) {
  // net_server inexplicably doesn't have this function; so I'll just fake it
  boost::uint32_t ret = 0;
  int shift = 24;  //  fill out the MSB first
  bool startQuad = true;
  while ((shift >= 0) && (*buffer)) {
    if (startQuad) {
      unsigned char quad = (unsigned char) atoi(buffer);
      ret |= (((boost::uint32_t)quad) << shift);
      shift -= 8;
    }
    startQuad = (*buffer == '.');
    ++buffer;
  }
  return ret;
}

// POSIX and APPLE Socket implementation
#if defined(MAIDSAFE_POSIX) || defined (MAIDSAFE_APPLE)
// || defined (__MINGW__)
static boost::uint32_t SockAddrToUint32(struct sockaddr * a) {
  return ((a)&&(a->sa_family == AF_INET)) ?
         ntohl(((struct sockaddr_in *)a)->sin_addr.s_addr) : 0;
}
#endif

void GetNetInterfaces(std::vector<struct DeviceStruct> *alldevices) {
  alldevices->clear();
  boost::system::error_code ec;
  std::vector<NetworkInterface> net_interfaces;
  net_interfaces = NetworkInterface::LocalList(ec);
  if (ec)
    return;
  for (std::vector<NetworkInterface>::iterator it = net_interfaces.begin();
       it != net_interfaces.end(); ++it) {
    DeviceStruct device;
    device.device_interface = std::string(it->name);
    device.ip_address = it->destination;
    alldevices->push_back(device);
  }
}

bool GetLocalAddress(boost::asio::ip::address *local_address) {
  *local_address = NetworkInterface::LocalAddress();
  if (NetworkInterface::IsAny(*local_address))
    return false;
  return true;
}

std::vector<std::string> GetLocalAddresses() {
  // get all network interfaces
  std::vector<std::string> addresses;
  std::vector<struct DeviceStruct> alldevices;
  GetNetInterfaces(&alldevices);
  for (std::vector<struct DeviceStruct>::iterator it = alldevices.begin();
       it != alldevices.end(); ++it) {
    if (!NetworkInterface::IsLoopback(it->ip_address) &&
        !NetworkInterface::IsMulticast(it->ip_address) &&
        !NetworkInterface::IsAny(it->ip_address)) {
      addresses.push_back(it->ip_address.to_string());
    }
  }
  return addresses;
}

}  // namespace base