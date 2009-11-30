

#include "kademlia/datastore.h"

#include <exception>
#include "base/config.h"
#include "maidsafe/maidsafe-dht_config.h"

namespace kad {

DataStore::DataStore(const boost::uint32_t &t_refresh): datastore_(),
    t_refresh_(0), mutex_() {
  t_refresh_ = t_refresh + (base::random_32bit_uinteger() % 5);
}

DataStore::~DataStore() {
  datastore_.clear();
}

bool DataStore::Keys(std::set<std::string> *keys) {
  keys->clear();
  boost::mutex::scoped_lock guard(mutex_);
  for (datastore::iterator it = datastore_.begin();
       it !=  datastore_.end(); it++)
    keys->insert(it->key_);
  return true;
}

bool DataStore::StoreItem(const std::string &key,
      const std::string &value, const boost::uint32_t &time_to_live,
      const bool &hashable) {
  if (key == "" || value == "" || time_to_live <= 0)
    return false;

  boost::uint32_t time_stamp = base::get_epoch_time();
  key_value_tuple tuple(key, value, time_stamp,
      time_to_live+time_stamp, time_to_live, hashable);
  boost::mutex::scoped_lock guard(mutex_);
  std::pair<datastore::iterator, bool> p = datastore_.insert(tuple);

  if (!p.second) {
    datastore_.replace(p.first, tuple);
  }
  return true;
}

bool DataStore::LoadItem(const std::string &key,
    std::vector<std::string> *values) {
  values->clear();
  boost::mutex::scoped_lock guard(mutex_);
  std::pair<datastore::iterator, datastore::iterator> p =
      datastore_.equal_range(boost::make_tuple(key));
  if (p.first == p.second)
    return false;
  boost::uint32_t now = base::get_epoch_time();
  while (p.first != p.second) {
    boost::int32_t ttl_remaining = p.first->expire_time_ - now;
    if (ttl_remaining > 0)
      values->push_back(p.first->value_);
    p.first++;
  }
  if (values->empty())
    return false;
  return true;
}

bool DataStore::DeleteItem(const std::string &key,
    const std::string &value) {
  datastore::iterator it = datastore_.find(boost::make_tuple(key, value));
  boost::mutex::scoped_lock guard(mutex_);
  if (it == datastore_.end())
    return false;
  datastore_.erase(it);
  return true;
}

bool DataStore::DeleteKey(const std::string &key) {
  boost::mutex::scoped_lock guard(mutex_);
  std::pair<datastore::iterator, datastore::iterator> p =
      datastore_.equal_range(boost::make_tuple(key));
  if (p.first == p.second)
    return false;
  datastore_.erase(p.first, p.second);
  return true;
}

boost::uint32_t DataStore::LastRefreshTime(const std::string &key,
      const std::string &value) {
  boost::mutex::scoped_lock guard(mutex_);
  datastore::iterator it = datastore_.find(boost::make_tuple(key, value));
  if (it == datastore_.end())
    return 0;
  return it->last_refresh_time_;
}

boost::uint32_t DataStore::ExpireTime(const std::string &key,
      const std::string &value) {
  boost::mutex::scoped_lock guard(mutex_);
  datastore::iterator it = datastore_.find(boost::make_tuple(key, value));
  if (it == datastore_.end())
    return 0;
  return it->expire_time_;
}

std::vector<refresh_value> DataStore::ValuesToRefresh() {
  std::vector<refresh_value> values;
  datastore::index<kad::t_last_refresh_time>::type::iterator it, up_limit;
  boost::mutex::scoped_lock guard(mutex_);
  datastore::index<kad::t_last_refresh_time>::type& indx =
      datastore_.get<kad::t_last_refresh_time>();
  boost::uint32_t now = base::get_epoch_time();
  boost::uint32_t time_limit = now - t_refresh_;
  up_limit = indx.upper_bound(time_limit);
  for (it = indx.begin();
       it != up_limit; it++) {
    boost::int32_t ttl_remaining = it->expire_time_ - now;
    if (ttl_remaining > 0)
      values.push_back(refresh_value(it->key_, it->value_, ttl_remaining));
  }
  return values;
}

void DataStore::DeleteExpiredValues() {
  datastore::index<kad::t_expire_time>::type::iterator up_limit, it;
  boost::mutex::scoped_lock guard(mutex_);
  datastore::index<kad::t_expire_time>::type& indx =
      datastore_.get<kad::t_expire_time>();
  boost::uint32_t now = base::get_epoch_time();
  up_limit = indx.lower_bound(now);
  indx.erase(indx.begin(), up_limit);
}

void DataStore::Clear() {
  boost::mutex::scoped_lock guard(mutex_);
  datastore_.clear();
}

boost::uint32_t DataStore::TimeToLive(const std::string &key,
      const std::string &value) {
  boost::mutex::scoped_lock guard(mutex_);
  datastore::iterator it = datastore_.find(boost::make_tuple(key, value));
  if (it == datastore_.end())
    return 0;
  return it->ttl_;
}

boost::uint32_t DataStore::t_refresh() const {
  return t_refresh_;
}

std::vector< std::pair<std::string, bool> > DataStore::LoadKeyAppendableAttr(
    const std::string &key) {
  std::vector< std::pair<std::string, bool> > result;
  boost::mutex::scoped_lock guard(mutex_);
  std::pair<datastore::iterator, datastore::iterator> p =
      datastore_.equal_range(boost::make_tuple(key));
  while (p.first != p.second) {
    result.push_back(std::pair<std::string, bool>(p.first->value_,
        p.first->appendable_key_));
    p.first++;
  }
  return result;
}

bool DataStore::RefreshItem(const std::string &key, const std::string &value) {
  boost::mutex::scoped_lock guard(mutex_);
  datastore::iterator it = datastore_.find(boost::make_tuple(key, value));
  if (it == datastore_.end())
    return false;
  boost::uint32_t time_stamp = base::get_epoch_time();
  key_value_tuple tuple(key, value, time_stamp);
  tuple.ttl_ = it->ttl_;
  tuple.expire_time_ = it->expire_time_;
  tuple.appendable_key_ = it->appendable_key_;
  datastore_.replace(it, tuple);
  return true;
}
}  // namespace kad