// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ping.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ping_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ping_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ping_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ping_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ping_2eproto;
namespace ping {
class Ping;
struct PingDefaultTypeInternal;
extern PingDefaultTypeInternal _Ping_default_instance_;
class Pong;
struct PongDefaultTypeInternal;
extern PongDefaultTypeInternal _Pong_default_instance_;
}  // namespace ping
PROTOBUF_NAMESPACE_OPEN
template<> ::ping::Ping* Arena::CreateMaybeMessage<::ping::Ping>(Arena*);
template<> ::ping::Pong* Arena::CreateMaybeMessage<::ping::Pong>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ping {

// ===================================================================

class Ping final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ping.Ping) */ {
 public:
  inline Ping() : Ping(nullptr) {}
  ~Ping() override;
  explicit PROTOBUF_CONSTEXPR Ping(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Ping(const Ping& from);
  Ping(Ping&& from) noexcept
    : Ping() {
    *this = ::std::move(from);
  }

  inline Ping& operator=(const Ping& from) {
    CopyFrom(from);
    return *this;
  }
  inline Ping& operator=(Ping&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Ping& default_instance() {
    return *internal_default_instance();
  }
  static inline const Ping* internal_default_instance() {
    return reinterpret_cast<const Ping*>(
               &_Ping_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Ping& a, Ping& b) {
    a.Swap(&b);
  }
  inline void Swap(Ping* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Ping* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Ping* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Ping>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Ping& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Ping& from) {
    Ping::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Ping* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ping.Ping";
  }
  protected:
  explicit Ping(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNumFieldNumber = 3,
    kNameFieldNumber = 2,
    kIdFieldNumber = 1,
  };
  // repeated int32 num = 3;
  int num_size() const;
  private:
  int _internal_num_size() const;
  public:
  void clear_num();
  private:
  int32_t _internal_num(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_num() const;
  void _internal_add_num(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_num();
  public:
  int32_t num(int index) const;
  void set_num(int index, int32_t value);
  void add_num(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      num() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_num();

  // string name = 2;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // int32 id = 1;
  void clear_id();
  int32_t id() const;
  void set_id(int32_t value);
  private:
  int32_t _internal_id() const;
  void _internal_set_id(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:ping.Ping)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > num_;
    mutable std::atomic<int> _num_cached_byte_size_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    int32_t id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_ping_2eproto;
};
// -------------------------------------------------------------------

class Pong final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ping.Pong) */ {
 public:
  inline Pong() : Pong(nullptr) {}
  ~Pong() override;
  explicit PROTOBUF_CONSTEXPR Pong(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Pong(const Pong& from);
  Pong(Pong&& from) noexcept
    : Pong() {
    *this = ::std::move(from);
  }

  inline Pong& operator=(const Pong& from) {
    CopyFrom(from);
    return *this;
  }
  inline Pong& operator=(Pong&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Pong& default_instance() {
    return *internal_default_instance();
  }
  static inline const Pong* internal_default_instance() {
    return reinterpret_cast<const Pong*>(
               &_Pong_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Pong& a, Pong& b) {
    a.Swap(&b);
  }
  inline void Swap(Pong* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Pong* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Pong* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Pong>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Pong& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Pong& from) {
    Pong::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Pong* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ping.Pong";
  }
  protected:
  explicit Pong(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 2,
    kIdFieldNumber = 1,
    kSumFieldNumber = 3,
  };
  // string name = 2;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // int32 id = 1;
  void clear_id();
  int32_t id() const;
  void set_id(int32_t value);
  private:
  int32_t _internal_id() const;
  void _internal_set_id(int32_t value);
  public:

  // int32 sum = 3;
  void clear_sum();
  int32_t sum() const;
  void set_sum(int32_t value);
  private:
  int32_t _internal_sum() const;
  void _internal_set_sum(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:ping.Pong)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    int32_t id_;
    int32_t sum_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_ping_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Ping

// int32 id = 1;
inline void Ping::clear_id() {
  _impl_.id_ = 0;
}
inline int32_t Ping::_internal_id() const {
  return _impl_.id_;
}
inline int32_t Ping::id() const {
  // @@protoc_insertion_point(field_get:ping.Ping.id)
  return _internal_id();
}
inline void Ping::_internal_set_id(int32_t value) {
  
  _impl_.id_ = value;
}
inline void Ping::set_id(int32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:ping.Ping.id)
}

// string name = 2;
inline void Ping::clear_name() {
  _impl_.name_.ClearToEmpty();
}
inline const std::string& Ping::name() const {
  // @@protoc_insertion_point(field_get:ping.Ping.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Ping::set_name(ArgT0&& arg0, ArgT... args) {
 
 _impl_.name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:ping.Ping.name)
}
inline std::string* Ping::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:ping.Ping.name)
  return _s;
}
inline const std::string& Ping::_internal_name() const {
  return _impl_.name_.Get();
}
inline void Ping::_internal_set_name(const std::string& value) {
  
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* Ping::_internal_mutable_name() {
  
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* Ping::release_name() {
  // @@protoc_insertion_point(field_release:ping.Ping.name)
  return _impl_.name_.Release();
}
inline void Ping::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  _impl_.name_.SetAllocated(name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ping.Ping.name)
}

// repeated int32 num = 3;
inline int Ping::_internal_num_size() const {
  return _impl_.num_.size();
}
inline int Ping::num_size() const {
  return _internal_num_size();
}
inline void Ping::clear_num() {
  _impl_.num_.Clear();
}
inline int32_t Ping::_internal_num(int index) const {
  return _impl_.num_.Get(index);
}
inline int32_t Ping::num(int index) const {
  // @@protoc_insertion_point(field_get:ping.Ping.num)
  return _internal_num(index);
}
inline void Ping::set_num(int index, int32_t value) {
  _impl_.num_.Set(index, value);
  // @@protoc_insertion_point(field_set:ping.Ping.num)
}
inline void Ping::_internal_add_num(int32_t value) {
  _impl_.num_.Add(value);
}
inline void Ping::add_num(int32_t value) {
  _internal_add_num(value);
  // @@protoc_insertion_point(field_add:ping.Ping.num)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
Ping::_internal_num() const {
  return _impl_.num_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
Ping::num() const {
  // @@protoc_insertion_point(field_list:ping.Ping.num)
  return _internal_num();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
Ping::_internal_mutable_num() {
  return &_impl_.num_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
Ping::mutable_num() {
  // @@protoc_insertion_point(field_mutable_list:ping.Ping.num)
  return _internal_mutable_num();
}

// -------------------------------------------------------------------

// Pong

// int32 id = 1;
inline void Pong::clear_id() {
  _impl_.id_ = 0;
}
inline int32_t Pong::_internal_id() const {
  return _impl_.id_;
}
inline int32_t Pong::id() const {
  // @@protoc_insertion_point(field_get:ping.Pong.id)
  return _internal_id();
}
inline void Pong::_internal_set_id(int32_t value) {
  
  _impl_.id_ = value;
}
inline void Pong::set_id(int32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:ping.Pong.id)
}

// string name = 2;
inline void Pong::clear_name() {
  _impl_.name_.ClearToEmpty();
}
inline const std::string& Pong::name() const {
  // @@protoc_insertion_point(field_get:ping.Pong.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Pong::set_name(ArgT0&& arg0, ArgT... args) {
 
 _impl_.name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:ping.Pong.name)
}
inline std::string* Pong::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:ping.Pong.name)
  return _s;
}
inline const std::string& Pong::_internal_name() const {
  return _impl_.name_.Get();
}
inline void Pong::_internal_set_name(const std::string& value) {
  
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* Pong::_internal_mutable_name() {
  
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* Pong::release_name() {
  // @@protoc_insertion_point(field_release:ping.Pong.name)
  return _impl_.name_.Release();
}
inline void Pong::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  _impl_.name_.SetAllocated(name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ping.Pong.name)
}

// int32 sum = 3;
inline void Pong::clear_sum() {
  _impl_.sum_ = 0;
}
inline int32_t Pong::_internal_sum() const {
  return _impl_.sum_;
}
inline int32_t Pong::sum() const {
  // @@protoc_insertion_point(field_get:ping.Pong.sum)
  return _internal_sum();
}
inline void Pong::_internal_set_sum(int32_t value) {
  
  _impl_.sum_ = value;
}
inline void Pong::set_sum(int32_t value) {
  _internal_set_sum(value);
  // @@protoc_insertion_point(field_set:ping.Pong.sum)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace ping

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ping_2eproto
