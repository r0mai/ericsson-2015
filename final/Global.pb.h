// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Global.proto

#ifndef PROTOBUF_Global_2eproto__INCLUDED
#define PROTOBUF_Global_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "Elements.pb.h"
// @@protoc_insertion_point(includes)

namespace protocol {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Global_2eproto();
void protobuf_AssignDesc_Global_2eproto();
void protobuf_ShutdownFile_Global_2eproto();

class Global;
class Field;
class Field_ElementInfo;

enum Global_Error {
  Global_Error_NOTSETDIRECTION = 1,
  Global_Error_WRONGDIRECTION = 2,
  Global_Error_WRONGMOVE = 3,
  Global_Error_NOTSETFLUXCAPATITORID = 4,
  Global_Error_NOTSETFLUXCAPATITORTIME = 5,
  Global_Error_WRONGFLUXCAPATITORID = 6,
  Global_Error_WRONGFLUXCAPATITORTIME = 7,
  Global_Error_NOTSETCAPABILITY = 8,
  Global_Error_WRONGCAPABILITY = 9,
  Global_Error_WRONGUSECAPABILITY = 10,
  Global_Error_COMMANDCOLLOSION = 11,
  Global_Error_YOURDOCTRAVELLINGINTIME = 12
};
bool Global_Error_IsValid(int value);
const Global_Error Global_Error_Error_MIN = Global_Error_NOTSETDIRECTION;
const Global_Error Global_Error_Error_MAX = Global_Error_YOURDOCTRAVELLINGINTIME;
const int Global_Error_Error_ARRAYSIZE = Global_Error_Error_MAX + 1;

const ::google::protobuf::EnumDescriptor* Global_Error_descriptor();
inline const ::std::string& Global_Error_Name(Global_Error value) {
  return ::google::protobuf::internal::NameOfEnum(
    Global_Error_descriptor(), value);
}
inline bool Global_Error_Parse(
    const ::std::string& name, Global_Error* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Global_Error>(
    Global_Error_descriptor(), name, value);
}
enum Field_ElementType {
  Field_ElementType_FLUXCAPATITOR = 1,
  Field_ElementType_DOC = 2,
  Field_ElementType_WALL = 4,
  Field_ElementType_CHEST = 5,
  Field_ElementType_DELOREAN = 6,
  Field_ElementType_CAPABILITY = 7
};
bool Field_ElementType_IsValid(int value);
const Field_ElementType Field_ElementType_ElementType_MIN = Field_ElementType_FLUXCAPATITOR;
const Field_ElementType Field_ElementType_ElementType_MAX = Field_ElementType_CAPABILITY;
const int Field_ElementType_ElementType_ARRAYSIZE = Field_ElementType_ElementType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Field_ElementType_descriptor();
inline const ::std::string& Field_ElementType_Name(Field_ElementType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Field_ElementType_descriptor(), value);
}
inline bool Field_ElementType_Parse(
    const ::std::string& name, Field_ElementType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Field_ElementType>(
    Field_ElementType_descriptor(), name, value);
}
// ===================================================================

class Global : public ::google::protobuf::Message {
 public:
  Global();
  virtual ~Global();

  Global(const Global& from);

  inline Global& operator=(const Global& from) {
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
  static const Global& default_instance();

  void Swap(Global* other);

  // implements Message ----------------------------------------------

  Global* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Global& from);
  void MergeFrom(const Global& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Global_Error Error;
  static const Error NOTSETDIRECTION = Global_Error_NOTSETDIRECTION;
  static const Error WRONGDIRECTION = Global_Error_WRONGDIRECTION;
  static const Error WRONGMOVE = Global_Error_WRONGMOVE;
  static const Error NOTSETFLUXCAPATITORID = Global_Error_NOTSETFLUXCAPATITORID;
  static const Error NOTSETFLUXCAPATITORTIME = Global_Error_NOTSETFLUXCAPATITORTIME;
  static const Error WRONGFLUXCAPATITORID = Global_Error_WRONGFLUXCAPATITORID;
  static const Error WRONGFLUXCAPATITORTIME = Global_Error_WRONGFLUXCAPATITORTIME;
  static const Error NOTSETCAPABILITY = Global_Error_NOTSETCAPABILITY;
  static const Error WRONGCAPABILITY = Global_Error_WRONGCAPABILITY;
  static const Error WRONGUSECAPABILITY = Global_Error_WRONGUSECAPABILITY;
  static const Error COMMANDCOLLOSION = Global_Error_COMMANDCOLLOSION;
  static const Error YOURDOCTRAVELLINGINTIME = Global_Error_YOURDOCTRAVELLINGINTIME;
  static inline bool Error_IsValid(int value) {
    return Global_Error_IsValid(value);
  }
  static const Error Error_MIN =
    Global_Error_Error_MIN;
  static const Error Error_MAX =
    Global_Error_Error_MAX;
  static const int Error_ARRAYSIZE =
    Global_Error_Error_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Error_descriptor() {
    return Global_Error_descriptor();
  }
  static inline const ::std::string& Error_Name(Error value) {
    return Global_Error_Name(value);
  }
  static inline bool Error_Parse(const ::std::string& name,
      Error* value) {
    return Global_Error_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required uint32 width = 1;
  inline bool has_width() const;
  inline void clear_width();
  static const int kWidthFieldNumber = 1;
  inline ::google::protobuf::uint32 width() const;
  inline void set_width(::google::protobuf::uint32 value);

  // required uint32 height = 2;
  inline bool has_height() const;
  inline void clear_height();
  static const int kHeightFieldNumber = 2;
  inline ::google::protobuf::uint32 height() const;
  inline void set_height(::google::protobuf::uint32 value);

  // repeated .protocol.Field fields = 3;
  inline int fields_size() const;
  inline void clear_fields();
  static const int kFieldsFieldNumber = 3;
  inline const ::protocol::Field& fields(int index) const;
  inline ::protocol::Field* mutable_fields(int index);
  inline ::protocol::Field* add_fields();
  inline const ::google::protobuf::RepeatedPtrField< ::protocol::Field >&
      fields() const;
  inline ::google::protobuf::RepeatedPtrField< ::protocol::Field >*
      mutable_fields();

  // required uint32 tick = 4;
  inline bool has_tick() const;
  inline void clear_tick();
  static const int kTickFieldNumber = 4;
  inline ::google::protobuf::uint32 tick() const;
  inline void set_tick(::google::protobuf::uint32 value);

  // optional .protocol.Global.Error error = 5;
  inline bool has_error() const;
  inline void clear_error();
  static const int kErrorFieldNumber = 5;
  inline ::protocol::Global_Error error() const;
  inline void set_error(::protocol::Global_Error value);

  // required uint32 your_doc_id = 6;
  inline bool has_your_doc_id() const;
  inline void clear_your_doc_id();
  static const int kYourDocIdFieldNumber = 6;
  inline ::google::protobuf::uint32 your_doc_id() const;
  inline void set_your_doc_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:protocol.Global)
 private:
  inline void set_has_width();
  inline void clear_has_width();
  inline void set_has_height();
  inline void clear_has_height();
  inline void set_has_tick();
  inline void clear_has_tick();
  inline void set_has_error();
  inline void clear_has_error();
  inline void set_has_your_doc_id();
  inline void clear_has_your_doc_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 width_;
  ::google::protobuf::uint32 height_;
  ::google::protobuf::RepeatedPtrField< ::protocol::Field > fields_;
  ::google::protobuf::uint32 tick_;
  int error_;
  ::google::protobuf::uint32 your_doc_id_;
  friend void  protobuf_AddDesc_Global_2eproto();
  friend void protobuf_AssignDesc_Global_2eproto();
  friend void protobuf_ShutdownFile_Global_2eproto();

  void InitAsDefaultInstance();
  static Global* default_instance_;
};
// -------------------------------------------------------------------

class Field_ElementInfo : public ::google::protobuf::Message {
 public:
  Field_ElementInfo();
  virtual ~Field_ElementInfo();

  Field_ElementInfo(const Field_ElementInfo& from);

  inline Field_ElementInfo& operator=(const Field_ElementInfo& from) {
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
  static const Field_ElementInfo& default_instance();

  void Swap(Field_ElementInfo* other);

  // implements Message ----------------------------------------------

  Field_ElementInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Field_ElementInfo& from);
  void MergeFrom(const Field_ElementInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .protocol.Field.ElementType type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::protocol::Field_ElementType type() const;
  inline void set_type(::protocol::Field_ElementType value);

  // optional .protocol.Doc doc = 2;
  inline bool has_doc() const;
  inline void clear_doc();
  static const int kDocFieldNumber = 2;
  inline const ::protocol::Doc& doc() const;
  inline ::protocol::Doc* mutable_doc();
  inline ::protocol::Doc* release_doc();
  inline void set_allocated_doc(::protocol::Doc* doc);

  // optional .protocol.FluxCapatitor flux_capatitor = 4;
  inline bool has_flux_capatitor() const;
  inline void clear_flux_capatitor();
  static const int kFluxCapatitorFieldNumber = 4;
  inline const ::protocol::FluxCapatitor& flux_capatitor() const;
  inline ::protocol::FluxCapatitor* mutable_flux_capatitor();
  inline ::protocol::FluxCapatitor* release_flux_capatitor();
  inline void set_allocated_flux_capatitor(::protocol::FluxCapatitor* flux_capatitor);

  // optional .protocol.Chest chest = 5;
  inline bool has_chest() const;
  inline void clear_chest();
  static const int kChestFieldNumber = 5;
  inline const ::protocol::Chest& chest() const;
  inline ::protocol::Chest* mutable_chest();
  inline ::protocol::Chest* release_chest();
  inline void set_allocated_chest(::protocol::Chest* chest);

  // optional .protocol.DeLorean delorean = 6;
  inline bool has_delorean() const;
  inline void clear_delorean();
  static const int kDeloreanFieldNumber = 6;
  inline const ::protocol::DeLorean& delorean() const;
  inline ::protocol::DeLorean* mutable_delorean();
  inline ::protocol::DeLorean* release_delorean();
  inline void set_allocated_delorean(::protocol::DeLorean* delorean);

  // optional .protocol.Capability capability = 7;
  inline bool has_capability() const;
  inline void clear_capability();
  static const int kCapabilityFieldNumber = 7;
  inline ::protocol::Capability capability() const;
  inline void set_capability(::protocol::Capability value);

  // @@protoc_insertion_point(class_scope:protocol.Field.ElementInfo)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_doc();
  inline void clear_has_doc();
  inline void set_has_flux_capatitor();
  inline void clear_has_flux_capatitor();
  inline void set_has_chest();
  inline void clear_has_chest();
  inline void set_has_delorean();
  inline void clear_has_delorean();
  inline void set_has_capability();
  inline void clear_has_capability();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::protocol::Doc* doc_;
  ::protocol::FluxCapatitor* flux_capatitor_;
  int type_;
  int capability_;
  ::protocol::Chest* chest_;
  ::protocol::DeLorean* delorean_;
  friend void  protobuf_AddDesc_Global_2eproto();
  friend void protobuf_AssignDesc_Global_2eproto();
  friend void protobuf_ShutdownFile_Global_2eproto();

  void InitAsDefaultInstance();
  static Field_ElementInfo* default_instance_;
};
// -------------------------------------------------------------------

class Field : public ::google::protobuf::Message {
 public:
  Field();
  virtual ~Field();

  Field(const Field& from);

  inline Field& operator=(const Field& from) {
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
  static const Field& default_instance();

  void Swap(Field* other);

  // implements Message ----------------------------------------------

  Field* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Field& from);
  void MergeFrom(const Field& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Field_ElementInfo ElementInfo;

  typedef Field_ElementType ElementType;
  static const ElementType FLUXCAPATITOR = Field_ElementType_FLUXCAPATITOR;
  static const ElementType DOC = Field_ElementType_DOC;
  static const ElementType WALL = Field_ElementType_WALL;
  static const ElementType CHEST = Field_ElementType_CHEST;
  static const ElementType DELOREAN = Field_ElementType_DELOREAN;
  static const ElementType CAPABILITY = Field_ElementType_CAPABILITY;
  static inline bool ElementType_IsValid(int value) {
    return Field_ElementType_IsValid(value);
  }
  static const ElementType ElementType_MIN =
    Field_ElementType_ElementType_MIN;
  static const ElementType ElementType_MAX =
    Field_ElementType_ElementType_MAX;
  static const int ElementType_ARRAYSIZE =
    Field_ElementType_ElementType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  ElementType_descriptor() {
    return Field_ElementType_descriptor();
  }
  static inline const ::std::string& ElementType_Name(ElementType value) {
    return Field_ElementType_Name(value);
  }
  static inline bool ElementType_Parse(const ::std::string& name,
      ElementType* value) {
    return Field_ElementType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional .protocol.Field.ElementInfo element = 1;
  inline bool has_element() const;
  inline void clear_element();
  static const int kElementFieldNumber = 1;
  inline const ::protocol::Field_ElementInfo& element() const;
  inline ::protocol::Field_ElementInfo* mutable_element();
  inline ::protocol::Field_ElementInfo* release_element();
  inline void set_allocated_element(::protocol::Field_ElementInfo* element);

  // optional .protocol.Field.ElementType next_tick_arrives = 2;
  inline bool has_next_tick_arrives() const;
  inline void clear_next_tick_arrives();
  static const int kNextTickArrivesFieldNumber = 2;
  inline ::protocol::Field_ElementType next_tick_arrives() const;
  inline void set_next_tick_arrives(::protocol::Field_ElementType value);

  // @@protoc_insertion_point(class_scope:protocol.Field)
 private:
  inline void set_has_element();
  inline void clear_has_element();
  inline void set_has_next_tick_arrives();
  inline void clear_has_next_tick_arrives();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::protocol::Field_ElementInfo* element_;
  int next_tick_arrives_;
  friend void  protobuf_AddDesc_Global_2eproto();
  friend void protobuf_AssignDesc_Global_2eproto();
  friend void protobuf_ShutdownFile_Global_2eproto();

  void InitAsDefaultInstance();
  static Field* default_instance_;
};
// ===================================================================


// ===================================================================

// Global

// required uint32 width = 1;
inline bool Global::has_width() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Global::set_has_width() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Global::clear_has_width() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Global::clear_width() {
  width_ = 0u;
  clear_has_width();
}
inline ::google::protobuf::uint32 Global::width() const {
  // @@protoc_insertion_point(field_get:protocol.Global.width)
  return width_;
}
inline void Global::set_width(::google::protobuf::uint32 value) {
  set_has_width();
  width_ = value;
  // @@protoc_insertion_point(field_set:protocol.Global.width)
}

// required uint32 height = 2;
inline bool Global::has_height() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Global::set_has_height() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Global::clear_has_height() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Global::clear_height() {
  height_ = 0u;
  clear_has_height();
}
inline ::google::protobuf::uint32 Global::height() const {
  // @@protoc_insertion_point(field_get:protocol.Global.height)
  return height_;
}
inline void Global::set_height(::google::protobuf::uint32 value) {
  set_has_height();
  height_ = value;
  // @@protoc_insertion_point(field_set:protocol.Global.height)
}

// repeated .protocol.Field fields = 3;
inline int Global::fields_size() const {
  return fields_.size();
}
inline void Global::clear_fields() {
  fields_.Clear();
}
inline const ::protocol::Field& Global::fields(int index) const {
  // @@protoc_insertion_point(field_get:protocol.Global.fields)
  return fields_.Get(index);
}
inline ::protocol::Field* Global::mutable_fields(int index) {
  // @@protoc_insertion_point(field_mutable:protocol.Global.fields)
  return fields_.Mutable(index);
}
inline ::protocol::Field* Global::add_fields() {
  // @@protoc_insertion_point(field_add:protocol.Global.fields)
  return fields_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::protocol::Field >&
Global::fields() const {
  // @@protoc_insertion_point(field_list:protocol.Global.fields)
  return fields_;
}
inline ::google::protobuf::RepeatedPtrField< ::protocol::Field >*
Global::mutable_fields() {
  // @@protoc_insertion_point(field_mutable_list:protocol.Global.fields)
  return &fields_;
}

// required uint32 tick = 4;
inline bool Global::has_tick() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Global::set_has_tick() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Global::clear_has_tick() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Global::clear_tick() {
  tick_ = 0u;
  clear_has_tick();
}
inline ::google::protobuf::uint32 Global::tick() const {
  // @@protoc_insertion_point(field_get:protocol.Global.tick)
  return tick_;
}
inline void Global::set_tick(::google::protobuf::uint32 value) {
  set_has_tick();
  tick_ = value;
  // @@protoc_insertion_point(field_set:protocol.Global.tick)
}

// optional .protocol.Global.Error error = 5;
inline bool Global::has_error() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Global::set_has_error() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Global::clear_has_error() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Global::clear_error() {
  error_ = 1;
  clear_has_error();
}
inline ::protocol::Global_Error Global::error() const {
  // @@protoc_insertion_point(field_get:protocol.Global.error)
  return static_cast< ::protocol::Global_Error >(error_);
}
inline void Global::set_error(::protocol::Global_Error value) {
  assert(::protocol::Global_Error_IsValid(value));
  set_has_error();
  error_ = value;
  // @@protoc_insertion_point(field_set:protocol.Global.error)
}

// required uint32 your_doc_id = 6;
inline bool Global::has_your_doc_id() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Global::set_has_your_doc_id() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Global::clear_has_your_doc_id() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Global::clear_your_doc_id() {
  your_doc_id_ = 0u;
  clear_has_your_doc_id();
}
inline ::google::protobuf::uint32 Global::your_doc_id() const {
  // @@protoc_insertion_point(field_get:protocol.Global.your_doc_id)
  return your_doc_id_;
}
inline void Global::set_your_doc_id(::google::protobuf::uint32 value) {
  set_has_your_doc_id();
  your_doc_id_ = value;
  // @@protoc_insertion_point(field_set:protocol.Global.your_doc_id)
}

// -------------------------------------------------------------------

// Field_ElementInfo

// required .protocol.Field.ElementType type = 1;
inline bool Field_ElementInfo::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Field_ElementInfo::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Field_ElementInfo::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Field_ElementInfo::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::protocol::Field_ElementType Field_ElementInfo::type() const {
  // @@protoc_insertion_point(field_get:protocol.Field.ElementInfo.type)
  return static_cast< ::protocol::Field_ElementType >(type_);
}
inline void Field_ElementInfo::set_type(::protocol::Field_ElementType value) {
  assert(::protocol::Field_ElementType_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:protocol.Field.ElementInfo.type)
}

// optional .protocol.Doc doc = 2;
inline bool Field_ElementInfo::has_doc() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Field_ElementInfo::set_has_doc() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Field_ElementInfo::clear_has_doc() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Field_ElementInfo::clear_doc() {
  if (doc_ != NULL) doc_->::protocol::Doc::Clear();
  clear_has_doc();
}
inline const ::protocol::Doc& Field_ElementInfo::doc() const {
  // @@protoc_insertion_point(field_get:protocol.Field.ElementInfo.doc)
  return doc_ != NULL ? *doc_ : *default_instance_->doc_;
}
inline ::protocol::Doc* Field_ElementInfo::mutable_doc() {
  set_has_doc();
  if (doc_ == NULL) doc_ = new ::protocol::Doc;
  // @@protoc_insertion_point(field_mutable:protocol.Field.ElementInfo.doc)
  return doc_;
}
inline ::protocol::Doc* Field_ElementInfo::release_doc() {
  clear_has_doc();
  ::protocol::Doc* temp = doc_;
  doc_ = NULL;
  return temp;
}
inline void Field_ElementInfo::set_allocated_doc(::protocol::Doc* doc) {
  delete doc_;
  doc_ = doc;
  if (doc) {
    set_has_doc();
  } else {
    clear_has_doc();
  }
  // @@protoc_insertion_point(field_set_allocated:protocol.Field.ElementInfo.doc)
}

// optional .protocol.FluxCapatitor flux_capatitor = 4;
inline bool Field_ElementInfo::has_flux_capatitor() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Field_ElementInfo::set_has_flux_capatitor() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Field_ElementInfo::clear_has_flux_capatitor() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Field_ElementInfo::clear_flux_capatitor() {
  if (flux_capatitor_ != NULL) flux_capatitor_->::protocol::FluxCapatitor::Clear();
  clear_has_flux_capatitor();
}
inline const ::protocol::FluxCapatitor& Field_ElementInfo::flux_capatitor() const {
  // @@protoc_insertion_point(field_get:protocol.Field.ElementInfo.flux_capatitor)
  return flux_capatitor_ != NULL ? *flux_capatitor_ : *default_instance_->flux_capatitor_;
}
inline ::protocol::FluxCapatitor* Field_ElementInfo::mutable_flux_capatitor() {
  set_has_flux_capatitor();
  if (flux_capatitor_ == NULL) flux_capatitor_ = new ::protocol::FluxCapatitor;
  // @@protoc_insertion_point(field_mutable:protocol.Field.ElementInfo.flux_capatitor)
  return flux_capatitor_;
}
inline ::protocol::FluxCapatitor* Field_ElementInfo::release_flux_capatitor() {
  clear_has_flux_capatitor();
  ::protocol::FluxCapatitor* temp = flux_capatitor_;
  flux_capatitor_ = NULL;
  return temp;
}
inline void Field_ElementInfo::set_allocated_flux_capatitor(::protocol::FluxCapatitor* flux_capatitor) {
  delete flux_capatitor_;
  flux_capatitor_ = flux_capatitor;
  if (flux_capatitor) {
    set_has_flux_capatitor();
  } else {
    clear_has_flux_capatitor();
  }
  // @@protoc_insertion_point(field_set_allocated:protocol.Field.ElementInfo.flux_capatitor)
}

// optional .protocol.Chest chest = 5;
inline bool Field_ElementInfo::has_chest() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Field_ElementInfo::set_has_chest() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Field_ElementInfo::clear_has_chest() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Field_ElementInfo::clear_chest() {
  if (chest_ != NULL) chest_->::protocol::Chest::Clear();
  clear_has_chest();
}
inline const ::protocol::Chest& Field_ElementInfo::chest() const {
  // @@protoc_insertion_point(field_get:protocol.Field.ElementInfo.chest)
  return chest_ != NULL ? *chest_ : *default_instance_->chest_;
}
inline ::protocol::Chest* Field_ElementInfo::mutable_chest() {
  set_has_chest();
  if (chest_ == NULL) chest_ = new ::protocol::Chest;
  // @@protoc_insertion_point(field_mutable:protocol.Field.ElementInfo.chest)
  return chest_;
}
inline ::protocol::Chest* Field_ElementInfo::release_chest() {
  clear_has_chest();
  ::protocol::Chest* temp = chest_;
  chest_ = NULL;
  return temp;
}
inline void Field_ElementInfo::set_allocated_chest(::protocol::Chest* chest) {
  delete chest_;
  chest_ = chest;
  if (chest) {
    set_has_chest();
  } else {
    clear_has_chest();
  }
  // @@protoc_insertion_point(field_set_allocated:protocol.Field.ElementInfo.chest)
}

// optional .protocol.DeLorean delorean = 6;
inline bool Field_ElementInfo::has_delorean() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Field_ElementInfo::set_has_delorean() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Field_ElementInfo::clear_has_delorean() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Field_ElementInfo::clear_delorean() {
  if (delorean_ != NULL) delorean_->::protocol::DeLorean::Clear();
  clear_has_delorean();
}
inline const ::protocol::DeLorean& Field_ElementInfo::delorean() const {
  // @@protoc_insertion_point(field_get:protocol.Field.ElementInfo.delorean)
  return delorean_ != NULL ? *delorean_ : *default_instance_->delorean_;
}
inline ::protocol::DeLorean* Field_ElementInfo::mutable_delorean() {
  set_has_delorean();
  if (delorean_ == NULL) delorean_ = new ::protocol::DeLorean;
  // @@protoc_insertion_point(field_mutable:protocol.Field.ElementInfo.delorean)
  return delorean_;
}
inline ::protocol::DeLorean* Field_ElementInfo::release_delorean() {
  clear_has_delorean();
  ::protocol::DeLorean* temp = delorean_;
  delorean_ = NULL;
  return temp;
}
inline void Field_ElementInfo::set_allocated_delorean(::protocol::DeLorean* delorean) {
  delete delorean_;
  delorean_ = delorean;
  if (delorean) {
    set_has_delorean();
  } else {
    clear_has_delorean();
  }
  // @@protoc_insertion_point(field_set_allocated:protocol.Field.ElementInfo.delorean)
}

// optional .protocol.Capability capability = 7;
inline bool Field_ElementInfo::has_capability() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Field_ElementInfo::set_has_capability() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Field_ElementInfo::clear_has_capability() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Field_ElementInfo::clear_capability() {
  capability_ = 1;
  clear_has_capability();
}
inline ::protocol::Capability Field_ElementInfo::capability() const {
  // @@protoc_insertion_point(field_get:protocol.Field.ElementInfo.capability)
  return static_cast< ::protocol::Capability >(capability_);
}
inline void Field_ElementInfo::set_capability(::protocol::Capability value) {
  assert(::protocol::Capability_IsValid(value));
  set_has_capability();
  capability_ = value;
  // @@protoc_insertion_point(field_set:protocol.Field.ElementInfo.capability)
}

// -------------------------------------------------------------------

// Field

// optional .protocol.Field.ElementInfo element = 1;
inline bool Field::has_element() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Field::set_has_element() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Field::clear_has_element() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Field::clear_element() {
  if (element_ != NULL) element_->::protocol::Field_ElementInfo::Clear();
  clear_has_element();
}
inline const ::protocol::Field_ElementInfo& Field::element() const {
  // @@protoc_insertion_point(field_get:protocol.Field.element)
  return element_ != NULL ? *element_ : *default_instance_->element_;
}
inline ::protocol::Field_ElementInfo* Field::mutable_element() {
  set_has_element();
  if (element_ == NULL) element_ = new ::protocol::Field_ElementInfo;
  // @@protoc_insertion_point(field_mutable:protocol.Field.element)
  return element_;
}
inline ::protocol::Field_ElementInfo* Field::release_element() {
  clear_has_element();
  ::protocol::Field_ElementInfo* temp = element_;
  element_ = NULL;
  return temp;
}
inline void Field::set_allocated_element(::protocol::Field_ElementInfo* element) {
  delete element_;
  element_ = element;
  if (element) {
    set_has_element();
  } else {
    clear_has_element();
  }
  // @@protoc_insertion_point(field_set_allocated:protocol.Field.element)
}

// optional .protocol.Field.ElementType next_tick_arrives = 2;
inline bool Field::has_next_tick_arrives() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Field::set_has_next_tick_arrives() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Field::clear_has_next_tick_arrives() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Field::clear_next_tick_arrives() {
  next_tick_arrives_ = 1;
  clear_has_next_tick_arrives();
}
inline ::protocol::Field_ElementType Field::next_tick_arrives() const {
  // @@protoc_insertion_point(field_get:protocol.Field.next_tick_arrives)
  return static_cast< ::protocol::Field_ElementType >(next_tick_arrives_);
}
inline void Field::set_next_tick_arrives(::protocol::Field_ElementType value) {
  assert(::protocol::Field_ElementType_IsValid(value));
  set_has_next_tick_arrives();
  next_tick_arrives_ = value;
  // @@protoc_insertion_point(field_set:protocol.Field.next_tick_arrives)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protocol

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::protocol::Global_Error> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::protocol::Global_Error>() {
  return ::protocol::Global_Error_descriptor();
}
template <> struct is_proto_enum< ::protocol::Field_ElementType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::protocol::Field_ElementType>() {
  return ::protocol::Field_ElementType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Global_2eproto__INCLUDED
