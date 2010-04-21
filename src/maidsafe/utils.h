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
 * This file may be included with the library, but is not required.  It        *
 * provides additional utilities over and above those in maidsafe_dht.config.h *
 * namespace base that may be useful to projects using the library.            *
 *                                                                             *
 * NOTE: These settings and functions WILL be amended or deleted in future     *
 * releases until this notice is removed.                                      *
 ******************************************************************************/

#ifndef MAIDSAFE_UTILS_H_
#define MAIDSAFE_UTILS_H_

#include <boost/cstdint.hpp>
#include <string>
#include <vector>

// Forward declaration
namespace kad {
class Contact;
}  // namespace kad

namespace base {

/**
* @class Stats
* A simple class to determine statistical properties of a data set, computed
* without storing the values. Data type must be numerical.
*/
template <typename T>
class Stats {
 public:
  Stats() : size_(0), min_(0), max_(0), sum_(0) {}
  /**
  * Add a datum to the data set.
  * @param value The data value.
  */
  void Add(const T &value) {
    sum_ += value;
    ++size_;
    if (size_ == 1) {
      min_ = value;
      max_ = value;
    } else {
      if (value < min_)
        min_ = value;
      if (value > max_)
        max_ = value;
    }
  }
  /**
  * Get the size of the data set.
  * @return number of elements
  */
  boost::uint64_t Size() const { return size_; }
  /**
  * Get the smallest value in the set.
  * @return minimum
  */
  T Min() const { return min_; }
  /**
  * Get the biggest value in the set.
  * @return maximum
  */
  T Max() const { return max_; }
  /**
  * Get the sum of values in the set.
  * @return sum
  */
  T Sum() const { return sum_; }
  /**
  * Get the average of values in the set.
  * @return arithmetic mean
  */
  T Mean() const { return size_ > 0 ? sum_ / size_ : 0; }
 private:
  boost::uint64_t size_;
  T min_;
  T max_;
  T sum_;
};

// Remove leading and trailing slashes from path unless path is "/".
std::string TidyPath(const std::string &original_path_);

// Convert from boost::uint64_t to string.
std::string itos_ull(boost::uint64_t value);

// Convert from string to boost::uint64_t.
boost::uint64_t stoi_ull(std::string value);

// Convert from boost::uint32_t to string.
std::string itos_ul(boost::uint32_t value);

// Convert from string to boost::uint32_t.
boost::uint32_t stoi_ul(std::string value);

// Convert from boost::int32_t to string.
std::string itos_l(boost::int32_t value);

// Convert from string to boost::int32_t.
boost::int32_t stoi_l(std::string value);

// Convert from string to wstring.
std::wstring StrToWStr(const std::string &string_);

// Convert from wstring to string.
std::string WStrToStr(const std::wstring &wstring_);

// Convert string to all lowercase.
std::string StrToLwr(const std::string &string_);

// Check for disallowed characters for filenames.
bool ValidateName(const std::string &str);

// Add a kad Contact to the vector & sort ascending by kademlia distance to key.
void InsertKadContact(const std::string &key,
                      const kad::Contact &new_contact,
                      std::vector<kad::Contact> *contacts);
}  // namespace base

#endif  // MAIDSAFE_UTILS_H_
