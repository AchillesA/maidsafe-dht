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

#ifndef MAIDSAFE_ONLINE_H_
#define MAIDSAFE_ONLINE_H_

#include <boost/function.hpp>
#include <map>
#include "maidsafe/maidsafe-dht_config.h"

namespace base {

class OnlineController  {
  typedef boost::function<void(const bool&)> Observer;
  typedef std::pair<boost::uint16_t, Observer> GroupedObserver;
 public:
  static OnlineController* instance();
  boost::uint16_t RegisterObserver(const boost::uint16_t &group,
                                   const Observer &ob);
  bool UnregisterObserver(boost::uint16_t id);
  void UnregisterGroup(const boost::uint16_t &group);
  void UnregisterAll();
  void SetOnline(const boost::uint16_t &group, const bool &b);
  void SetAllOnline(const bool &b);
  bool Online(const boost::uint16_t &group);
  boost::uint16_t ObserversCount();
  boost::uint16_t ObserversInGroupCount(const boost::uint16_t &group);
  void Reset();

 private:
  OnlineController();
  ~OnlineController() {}
  std::map<boost::uint16_t, bool> online_;
  boost::mutex ol_mutex_;
  std::map<boost::uint16_t, GroupedObserver> observers_;
};

}  // namespace base

#endif  // MAIDSAFE_ONLINE_H_
