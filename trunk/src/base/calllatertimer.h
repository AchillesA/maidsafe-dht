/*Copyright (c) 2009 maidsafe.net limited
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the name of the maidsafe.net limited nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef BASE_CALLLATERTIMER_H_
#define BASE_CALLLATERTIMER_H_
#include <boost/thread/thread.hpp>
#include <boost/cstdint.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <list>
#include "base/utils.h"

namespace base {

typedef boost::function<void()> calllater_func;

struct CallLaterMap {
  CallLaterMap() : time_to_execute(0), cb(), calllater_id(0) {}
  boost::uint64_t time_to_execute;
  calllater_func cb;
  int calllater_id;
};

class CallLaterTimer {
  public:
    explicit CallLaterTimer(boost::recursive_mutex *mutex);
    explicit CallLaterTimer(const CallLaterTimer&);
    CallLaterTimer& operator=(const CallLaterTimer&);
    ~CallLaterTimer();
    // execute the expired calls
    void TryExecute();
    bool IsStarted();
    void CancelAll();
    bool CancelOne(int calllater_id);
    // Delay msecs milliseconds to call the function specified by cb
    int AddCallLater(boost::uint64_t msecs, calllater_func cb);

  private:
    boost::recursive_mutex *mutex_;
    int calllater_id_;
    bool is_started_;
    boost::thread *blocking_routine;
    std::list<CallLaterMap> calllaters_;
};

}  // namespace
#endif  // BASE_CALLLATERTIMER_H_