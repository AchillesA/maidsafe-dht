// Generated by the protocol buffer compiler.  DO NOT EDIT!

#ifndef PROTOBUF_testservices_2eproto__INCLUDED
#define PROTOBUF_testservices_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2000003
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2000003 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/service.h>

namespace tests {

// Internal implementation detail -- do not call these.
void  protobuf_BuildDesc_testservices_2eproto();
void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
    ::google::protobuf::FileDescriptor* file);

class PingRequest;
class PingResponse;
class BinaryOpRequest;
class BinaryOpResponse;
class StringMirrorRequest;
class StringMirrorResponse;

// ===================================================================

class PingRequest : public ::google::protobuf::Message {
 public:
  PingRequest();
  virtual ~PingRequest();
  
  PingRequest(const PingRequest& from);
  
  inline PingRequest& operator=(const PingRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const PingRequest& default_instance();
  void Swap(PingRequest* other);
  
  // implements Message ----------------------------------------------
  
  PingRequest* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bytes ping = 1;
  inline bool has_ping() const;
  inline void clear_ping();
  inline const ::std::string& ping() const;
  inline void set_ping(const ::std::string& value);
  inline void set_ping(const char* value);
  inline void set_ping(const void* value, size_t size);
  inline ::std::string* mutable_ping();
  
  // required bytes ip = 2;
  inline bool has_ip() const;
  inline void clear_ip();
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const void* value, size_t size);
  inline ::std::string* mutable_ip();
  
  // required int32 port = 3;
  inline bool has_port() const;
  inline void clear_port();
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* ping_;
  static const ::std::string _default_ping_;
  ::std::string* ip_;
  static const ::std::string _default_ip_;
  ::google::protobuf::int32 port_;
  friend void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static PingRequest* default_instance_;
};
// -------------------------------------------------------------------

class PingResponse : public ::google::protobuf::Message {
 public:
  PingResponse();
  virtual ~PingResponse();
  
  PingResponse(const PingResponse& from);
  
  inline PingResponse& operator=(const PingResponse& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const PingResponse& default_instance();
  void Swap(PingResponse* other);
  
  // implements Message ----------------------------------------------
  
  PingResponse* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bytes result = 1;
  inline bool has_result() const;
  inline void clear_result();
  inline const ::std::string& result() const;
  inline void set_result(const ::std::string& value);
  inline void set_result(const char* value);
  inline void set_result(const void* value, size_t size);
  inline ::std::string* mutable_result();
  
  // required bytes pong = 2;
  inline bool has_pong() const;
  inline void clear_pong();
  inline const ::std::string& pong() const;
  inline void set_pong(const ::std::string& value);
  inline void set_pong(const char* value);
  inline void set_pong(const void* value, size_t size);
  inline ::std::string* mutable_pong();
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* result_;
  static const ::std::string _default_result_;
  ::std::string* pong_;
  static const ::std::string _default_pong_;
  friend void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static PingResponse* default_instance_;
};
// -------------------------------------------------------------------

class BinaryOpRequest : public ::google::protobuf::Message {
 public:
  BinaryOpRequest();
  virtual ~BinaryOpRequest();
  
  BinaryOpRequest(const BinaryOpRequest& from);
  
  inline BinaryOpRequest& operator=(const BinaryOpRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const BinaryOpRequest& default_instance();
  void Swap(BinaryOpRequest* other);
  
  // implements Message ----------------------------------------------
  
  BinaryOpRequest* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 first = 1;
  inline bool has_first() const;
  inline void clear_first();
  inline ::google::protobuf::int32 first() const;
  inline void set_first(::google::protobuf::int32 value);
  
  // required int32 second = 2;
  inline bool has_second() const;
  inline void clear_second();
  inline ::google::protobuf::int32 second() const;
  inline void set_second(::google::protobuf::int32 value);
  
  // required bytes ip = 3;
  inline bool has_ip() const;
  inline void clear_ip();
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const void* value, size_t size);
  inline ::std::string* mutable_ip();
  
  // required int32 port = 4;
  inline bool has_port() const;
  inline void clear_port();
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::int32 first_;
  ::google::protobuf::int32 second_;
  ::std::string* ip_;
  static const ::std::string _default_ip_;
  ::google::protobuf::int32 port_;
  friend void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static BinaryOpRequest* default_instance_;
};
// -------------------------------------------------------------------

class BinaryOpResponse : public ::google::protobuf::Message {
 public:
  BinaryOpResponse();
  virtual ~BinaryOpResponse();
  
  BinaryOpResponse(const BinaryOpResponse& from);
  
  inline BinaryOpResponse& operator=(const BinaryOpResponse& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const BinaryOpResponse& default_instance();
  void Swap(BinaryOpResponse* other);
  
  // implements Message ----------------------------------------------
  
  BinaryOpResponse* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 result = 1;
  inline bool has_result() const;
  inline void clear_result();
  inline ::google::protobuf::int32 result() const;
  inline void set_result(::google::protobuf::int32 value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::int32 result_;
  friend void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static BinaryOpResponse* default_instance_;
};
// -------------------------------------------------------------------

class StringMirrorRequest : public ::google::protobuf::Message {
 public:
  StringMirrorRequest();
  virtual ~StringMirrorRequest();
  
  StringMirrorRequest(const StringMirrorRequest& from);
  
  inline StringMirrorRequest& operator=(const StringMirrorRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const StringMirrorRequest& default_instance();
  void Swap(StringMirrorRequest* other);
  
  // implements Message ----------------------------------------------
  
  StringMirrorRequest* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bytes message = 1;
  inline bool has_message() const;
  inline void clear_message();
  inline const ::std::string& message() const;
  inline void set_message(const ::std::string& value);
  inline void set_message(const char* value);
  inline void set_message(const void* value, size_t size);
  inline ::std::string* mutable_message();
  
  // required bytes ip = 2;
  inline bool has_ip() const;
  inline void clear_ip();
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const void* value, size_t size);
  inline ::std::string* mutable_ip();
  
  // required int32 port = 3;
  inline bool has_port() const;
  inline void clear_port();
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* message_;
  static const ::std::string _default_message_;
  ::std::string* ip_;
  static const ::std::string _default_ip_;
  ::google::protobuf::int32 port_;
  friend void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static StringMirrorRequest* default_instance_;
};
// -------------------------------------------------------------------

class StringMirrorResponse : public ::google::protobuf::Message {
 public:
  StringMirrorResponse();
  virtual ~StringMirrorResponse();
  
  StringMirrorResponse(const StringMirrorResponse& from);
  
  inline StringMirrorResponse& operator=(const StringMirrorResponse& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const StringMirrorResponse& default_instance();
  void Swap(StringMirrorResponse* other);
  
  // implements Message ----------------------------------------------
  
  StringMirrorResponse* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bytes mirrored_string = 1;
  inline bool has_mirrored_string() const;
  inline void clear_mirrored_string();
  inline const ::std::string& mirrored_string() const;
  inline void set_mirrored_string(const ::std::string& value);
  inline void set_mirrored_string(const char* value);
  inline void set_mirrored_string(const void* value, size_t size);
  inline ::std::string* mutable_mirrored_string();
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* mirrored_string_;
  static const ::std::string _default_mirrored_string_;
  friend void protobuf_BuildDesc_testservices_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static StringMirrorResponse* default_instance_;
};
// ===================================================================

class PingTest_Stub;

class PingTest : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline PingTest() {};
 public:
  virtual ~PingTest();
  
  typedef PingTest_Stub Stub;
  
  static const ::google::protobuf::ServiceDescriptor* descriptor();
  
  virtual void Ping(::google::protobuf::RpcController* controller,
                       const ::tests::PingRequest* request,
                       ::tests::PingResponse* response,
                       ::google::protobuf::Closure* done);
  
  // implements Service ----------------------------------------------
  
  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PingTest);
};

class PingTest_Stub : public PingTest {
 public:
  PingTest_Stub(::google::protobuf::RpcChannel* channel);
  PingTest_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~PingTest_Stub();
  
  inline ::google::protobuf::RpcChannel* channel() { return channel_; }
  
  // implements PingTest ------------------------------------------
  
  void Ping(::google::protobuf::RpcController* controller,
                       const ::tests::PingRequest* request,
                       ::tests::PingResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PingTest_Stub);
};


// -------------------------------------------------------------------

class TestOp_Stub;

class TestOp : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline TestOp() {};
 public:
  virtual ~TestOp();
  
  typedef TestOp_Stub Stub;
  
  static const ::google::protobuf::ServiceDescriptor* descriptor();
  
  virtual void Add(::google::protobuf::RpcController* controller,
                       const ::tests::BinaryOpRequest* request,
                       ::tests::BinaryOpResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void Multiplyl(::google::protobuf::RpcController* controller,
                       const ::tests::BinaryOpRequest* request,
                       ::tests::BinaryOpResponse* response,
                       ::google::protobuf::Closure* done);
  
  // implements Service ----------------------------------------------
  
  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TestOp);
};

class TestOp_Stub : public TestOp {
 public:
  TestOp_Stub(::google::protobuf::RpcChannel* channel);
  TestOp_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~TestOp_Stub();
  
  inline ::google::protobuf::RpcChannel* channel() { return channel_; }
  
  // implements TestOp ------------------------------------------
  
  void Add(::google::protobuf::RpcController* controller,
                       const ::tests::BinaryOpRequest* request,
                       ::tests::BinaryOpResponse* response,
                       ::google::protobuf::Closure* done);
  void Multiplyl(::google::protobuf::RpcController* controller,
                       const ::tests::BinaryOpRequest* request,
                       ::tests::BinaryOpResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TestOp_Stub);
};


// -------------------------------------------------------------------

class MirrorTest_Stub;

class MirrorTest : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline MirrorTest() {};
 public:
  virtual ~MirrorTest();
  
  typedef MirrorTest_Stub Stub;
  
  static const ::google::protobuf::ServiceDescriptor* descriptor();
  
  virtual void Mirror(::google::protobuf::RpcController* controller,
                       const ::tests::StringMirrorRequest* request,
                       ::tests::StringMirrorResponse* response,
                       ::google::protobuf::Closure* done);
  
  // implements Service ----------------------------------------------
  
  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MirrorTest);
};

class MirrorTest_Stub : public MirrorTest {
 public:
  MirrorTest_Stub(::google::protobuf::RpcChannel* channel);
  MirrorTest_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~MirrorTest_Stub();
  
  inline ::google::protobuf::RpcChannel* channel() { return channel_; }
  
  // implements MirrorTest ------------------------------------------
  
  void Mirror(::google::protobuf::RpcController* controller,
                       const ::tests::StringMirrorRequest* request,
                       ::tests::StringMirrorResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MirrorTest_Stub);
};


// ===================================================================


// ===================================================================

// PingRequest

// required bytes ping = 1;
inline bool PingRequest::has_ping() const {
  return _has_bit(0);
}
inline void PingRequest::clear_ping() {
  if (ping_ != &_default_ping_) {
    ping_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& PingRequest::ping() const {
  return *ping_;
}
inline void PingRequest::set_ping(const ::std::string& value) {
  _set_bit(0);
  if (ping_ == &_default_ping_) {
    ping_ = new ::std::string;
  }
  ping_->assign(value);
}
inline void PingRequest::set_ping(const char* value) {
  _set_bit(0);
  if (ping_ == &_default_ping_) {
    ping_ = new ::std::string;
  }
  ping_->assign(value);
}
inline void PingRequest::set_ping(const void* value, size_t size) {
  _set_bit(0);
  if (ping_ == &_default_ping_) {
    ping_ = new ::std::string;
  }
  ping_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PingRequest::mutable_ping() {
  _set_bit(0);
  if (ping_ == &_default_ping_) {
    ping_ = new ::std::string;
  }
  return ping_;
}

// required bytes ip = 2;
inline bool PingRequest::has_ip() const {
  return _has_bit(1);
}
inline void PingRequest::clear_ip() {
  if (ip_ != &_default_ip_) {
    ip_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& PingRequest::ip() const {
  return *ip_;
}
inline void PingRequest::set_ip(const ::std::string& value) {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void PingRequest::set_ip(const char* value) {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void PingRequest::set_ip(const void* value, size_t size) {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PingRequest::mutable_ip() {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  return ip_;
}

// required int32 port = 3;
inline bool PingRequest::has_port() const {
  return _has_bit(2);
}
inline void PingRequest::clear_port() {
  port_ = 0;
  _clear_bit(2);
}
inline ::google::protobuf::int32 PingRequest::port() const {
  return port_;
}
inline void PingRequest::set_port(::google::protobuf::int32 value) {
  _set_bit(2);
  port_ = value;
}

// -------------------------------------------------------------------

// PingResponse

// required bytes result = 1;
inline bool PingResponse::has_result() const {
  return _has_bit(0);
}
inline void PingResponse::clear_result() {
  if (result_ != &_default_result_) {
    result_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& PingResponse::result() const {
  return *result_;
}
inline void PingResponse::set_result(const ::std::string& value) {
  _set_bit(0);
  if (result_ == &_default_result_) {
    result_ = new ::std::string;
  }
  result_->assign(value);
}
inline void PingResponse::set_result(const char* value) {
  _set_bit(0);
  if (result_ == &_default_result_) {
    result_ = new ::std::string;
  }
  result_->assign(value);
}
inline void PingResponse::set_result(const void* value, size_t size) {
  _set_bit(0);
  if (result_ == &_default_result_) {
    result_ = new ::std::string;
  }
  result_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PingResponse::mutable_result() {
  _set_bit(0);
  if (result_ == &_default_result_) {
    result_ = new ::std::string;
  }
  return result_;
}

// required bytes pong = 2;
inline bool PingResponse::has_pong() const {
  return _has_bit(1);
}
inline void PingResponse::clear_pong() {
  if (pong_ != &_default_pong_) {
    pong_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& PingResponse::pong() const {
  return *pong_;
}
inline void PingResponse::set_pong(const ::std::string& value) {
  _set_bit(1);
  if (pong_ == &_default_pong_) {
    pong_ = new ::std::string;
  }
  pong_->assign(value);
}
inline void PingResponse::set_pong(const char* value) {
  _set_bit(1);
  if (pong_ == &_default_pong_) {
    pong_ = new ::std::string;
  }
  pong_->assign(value);
}
inline void PingResponse::set_pong(const void* value, size_t size) {
  _set_bit(1);
  if (pong_ == &_default_pong_) {
    pong_ = new ::std::string;
  }
  pong_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PingResponse::mutable_pong() {
  _set_bit(1);
  if (pong_ == &_default_pong_) {
    pong_ = new ::std::string;
  }
  return pong_;
}

// -------------------------------------------------------------------

// BinaryOpRequest

// required int32 first = 1;
inline bool BinaryOpRequest::has_first() const {
  return _has_bit(0);
}
inline void BinaryOpRequest::clear_first() {
  first_ = 0;
  _clear_bit(0);
}
inline ::google::protobuf::int32 BinaryOpRequest::first() const {
  return first_;
}
inline void BinaryOpRequest::set_first(::google::protobuf::int32 value) {
  _set_bit(0);
  first_ = value;
}

// required int32 second = 2;
inline bool BinaryOpRequest::has_second() const {
  return _has_bit(1);
}
inline void BinaryOpRequest::clear_second() {
  second_ = 0;
  _clear_bit(1);
}
inline ::google::protobuf::int32 BinaryOpRequest::second() const {
  return second_;
}
inline void BinaryOpRequest::set_second(::google::protobuf::int32 value) {
  _set_bit(1);
  second_ = value;
}

// required bytes ip = 3;
inline bool BinaryOpRequest::has_ip() const {
  return _has_bit(2);
}
inline void BinaryOpRequest::clear_ip() {
  if (ip_ != &_default_ip_) {
    ip_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& BinaryOpRequest::ip() const {
  return *ip_;
}
inline void BinaryOpRequest::set_ip(const ::std::string& value) {
  _set_bit(2);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void BinaryOpRequest::set_ip(const char* value) {
  _set_bit(2);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void BinaryOpRequest::set_ip(const void* value, size_t size) {
  _set_bit(2);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BinaryOpRequest::mutable_ip() {
  _set_bit(2);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  return ip_;
}

// required int32 port = 4;
inline bool BinaryOpRequest::has_port() const {
  return _has_bit(3);
}
inline void BinaryOpRequest::clear_port() {
  port_ = 0;
  _clear_bit(3);
}
inline ::google::protobuf::int32 BinaryOpRequest::port() const {
  return port_;
}
inline void BinaryOpRequest::set_port(::google::protobuf::int32 value) {
  _set_bit(3);
  port_ = value;
}

// -------------------------------------------------------------------

// BinaryOpResponse

// required int32 result = 1;
inline bool BinaryOpResponse::has_result() const {
  return _has_bit(0);
}
inline void BinaryOpResponse::clear_result() {
  result_ = 0;
  _clear_bit(0);
}
inline ::google::protobuf::int32 BinaryOpResponse::result() const {
  return result_;
}
inline void BinaryOpResponse::set_result(::google::protobuf::int32 value) {
  _set_bit(0);
  result_ = value;
}

// -------------------------------------------------------------------

// StringMirrorRequest

// required bytes message = 1;
inline bool StringMirrorRequest::has_message() const {
  return _has_bit(0);
}
inline void StringMirrorRequest::clear_message() {
  if (message_ != &_default_message_) {
    message_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& StringMirrorRequest::message() const {
  return *message_;
}
inline void StringMirrorRequest::set_message(const ::std::string& value) {
  _set_bit(0);
  if (message_ == &_default_message_) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void StringMirrorRequest::set_message(const char* value) {
  _set_bit(0);
  if (message_ == &_default_message_) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void StringMirrorRequest::set_message(const void* value, size_t size) {
  _set_bit(0);
  if (message_ == &_default_message_) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* StringMirrorRequest::mutable_message() {
  _set_bit(0);
  if (message_ == &_default_message_) {
    message_ = new ::std::string;
  }
  return message_;
}

// required bytes ip = 2;
inline bool StringMirrorRequest::has_ip() const {
  return _has_bit(1);
}
inline void StringMirrorRequest::clear_ip() {
  if (ip_ != &_default_ip_) {
    ip_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& StringMirrorRequest::ip() const {
  return *ip_;
}
inline void StringMirrorRequest::set_ip(const ::std::string& value) {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void StringMirrorRequest::set_ip(const char* value) {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void StringMirrorRequest::set_ip(const void* value, size_t size) {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* StringMirrorRequest::mutable_ip() {
  _set_bit(1);
  if (ip_ == &_default_ip_) {
    ip_ = new ::std::string;
  }
  return ip_;
}

// required int32 port = 3;
inline bool StringMirrorRequest::has_port() const {
  return _has_bit(2);
}
inline void StringMirrorRequest::clear_port() {
  port_ = 0;
  _clear_bit(2);
}
inline ::google::protobuf::int32 StringMirrorRequest::port() const {
  return port_;
}
inline void StringMirrorRequest::set_port(::google::protobuf::int32 value) {
  _set_bit(2);
  port_ = value;
}

// -------------------------------------------------------------------

// StringMirrorResponse

// required bytes mirrored_string = 1;
inline bool StringMirrorResponse::has_mirrored_string() const {
  return _has_bit(0);
}
inline void StringMirrorResponse::clear_mirrored_string() {
  if (mirrored_string_ != &_default_mirrored_string_) {
    mirrored_string_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& StringMirrorResponse::mirrored_string() const {
  return *mirrored_string_;
}
inline void StringMirrorResponse::set_mirrored_string(const ::std::string& value) {
  _set_bit(0);
  if (mirrored_string_ == &_default_mirrored_string_) {
    mirrored_string_ = new ::std::string;
  }
  mirrored_string_->assign(value);
}
inline void StringMirrorResponse::set_mirrored_string(const char* value) {
  _set_bit(0);
  if (mirrored_string_ == &_default_mirrored_string_) {
    mirrored_string_ = new ::std::string;
  }
  mirrored_string_->assign(value);
}
inline void StringMirrorResponse::set_mirrored_string(const void* value, size_t size) {
  _set_bit(0);
  if (mirrored_string_ == &_default_mirrored_string_) {
    mirrored_string_ = new ::std::string;
  }
  mirrored_string_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* StringMirrorResponse::mutable_mirrored_string() {
  _set_bit(0);
  if (mirrored_string_ == &_default_mirrored_string_) {
    mirrored_string_ = new ::std::string;
  }
  return mirrored_string_;
}


}  // namespace tests
#endif  // PROTOBUF_testservices_2eproto__INCLUDED