
/////////////////////////////////////////////////////////////////////////////
//
// base_macro.h - macro header
// --------------------------------------------------------------------------
//
// BASE
//
// MACRO
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_MACRO
#define _BASE_MACRO

#include "base_platform.h"

/////////////////////////////////////////////////////////////////////////////
// member definition and access

#define MEMBER_DEFINITION(type, member) \
  protected: \
    type m_ ## member; \

#define MEMBER_GET_METHOD(type, member) \
  public: \
    inline type Get ## member() const { \
      return (m_ ## member); \
    };

#define MEMBER_GETP_METHOD(type, member) \
  public: \
    inline type * Get ## member() { \
      return (m_ ## member); \
    };

#define MEMBER_GETR_METHOD(type, member) \
  public: \
    inline type & Get ## member() { \
      return (m_ ## member); \
    };

#define MEMBER_SET_METHOD(type, member) \
  public: \
    inline void Set ## member(const type & value) { \
      m_ ## member = value; \
    };

#define MEMBER_SETP_METHOD(type, member) \
  public: \
    inline void Set ## member(const type * value) { \
      m_ ## member = value; \
    };

#define MEMBER(type, member) \
  MEMBER_DEFINITION(type, member)

#define MEMBER__REFERENCE(type, member) \
  MEMBER_DEFINITION(REFERENCE<type >, member)

#define MEMBER_GET_SET(type, member) \
  MEMBER_DEFINITION(type, member) \
  MEMBER_GET_METHOD(type, member) \
  MEMBER_SET_METHOD(type, member)

#define MEMBER_GETR_SET(type, member) \
  MEMBER_DEFINITION(type, member) \
  MEMBER_GETR_METHOD(type, member) \
  MEMBER_SET_METHOD(type, member)

#define MEMBER_GET_SET__REFERENCE(type, member) \
  MEMBER_DEFINITION(REFERENCE<type >, member) \
  MEMBER_GETP_METHOD(type, member) \
  MEMBER_SETP_METHOD(type, member)

#define MEMBER_GET(type, member) \
  MEMBER_DEFINITION(type, member) \
  MEMBER_GET_METHOD(type, member)

#define MEMBER_GETR(type, member) \
  MEMBER_DEFINITION(type, member) \
  MEMBER_GETR_METHOD(type, member)

#define MEMBER_GET__REFERENCE(type, member) \
  MEMBER_DEFINITION(REFERENCE<type >, member) \
  MEMBER_GETP_METHOD(type, member)

#define MEMBER_SET(type, member) \
  MEMBER_DEFINITION(type, member) \
  MEMBER_SET_METHOD(type, member)

#define MEMBER_SET__REFERENCE(type, member) \
  MEMBER_DEFINITION(REFERENCE<type >, member) \
  MEMBER_SETP_METHOD(type, member)


/////////////////////////////////////////////////////////////////////////////
// exception handling

#define DERIVE_CLASS_BEGIN(modifier, base, derived) \
  class derived : \
    modifier base { \
  public:

#define DERIVE_CLASS_END(derived) \
  public: \
    virtual ~derived() {}; \
  };

#define DERIVE_EXCEPTION_BEGIN(base, derived) \
  DERIVE_CLASS_BEGIN(public, base, derived) \
  derived(const T_TIME & tTime = T_TIME(), const T_STRING & sModule = T_STRING(), const T_STRING & sClassPath = T_STRING(), const T_STRING & sMethod = T_STRING(), T_ULONG uLevel = 0, T_ULONG uCode = 0, const T_STRING & sMessage = T_STRING()) : \
    base(tTime, sModule, sClassPath, sMethod, uLevel, uCode, sMessage) {}; \
  derived(const ::BASE::CMessage & tMessage) : \
    base(tMessage) {}; \
  public: \
  enum __exceptions { \

#define DERIVE_EXCEPTION_END(derived) \
  }; \
  DERIVE_CLASS_END(derived)

#define DERIVE_ABSTRACT_EXCEPTION(base, derived) \
  DERIVE_CLASS_BEGIN(public, base, derived) \
  derived(const T_TIME & tTime = T_TIME(), const T_STRING & sModule = T_STRING(), const T_STRING & sClassPath = T_STRING(), const T_STRING & sMethod = T_STRING(), T_ULONG uLevel = 0, T_ULONG uCode = 0, const T_STRING & sMessage = T_STRING()) : \
    base(tTime, sModule, sClassPath, sMethod, uLevel, uCode, sMessage) {}; \
  derived(const ::BASE::CMessage & tMessage) : \
    base(tMessage) {}; \
  DERIVE_CLASS_END(derived)

#define __CREATE_EXCEPTION(module, classpath, method, code, message) \
  ::BASE::CMessage __tMessage; \
  \
  __tMessage.SetModule(T_STRING(#module)); \
  __tMessage.SetClassPath(T_STRING(#classpath)); \
  __tMessage.SetMethod(T_STRING(#method)); \
  __tMessage.SetCode(code); \
  \
  __tMessage.SetMessage message;

#define EXCEPTION(module, classpath, method, message) \
  { \
    __CREATE_EXCEPTION(module, classpath, method, 0, message);

#define MESSAGE

#define THROW(exception, code) \
    __tMessage.SetCode(exception::code); \
    throw exception(__tMessage); \
  }

#define IGNORE_EXCEPTION(code) \
  try { \
    code; \
  } catch (...) { \
    ; \
  }


/////////////////////////////////////////////////////////////////////////////
// basic conversion

#define BOOLEAN_TO_STRING(value) \
  ((value == TRUE) ? "TRUE" : "FALSE")

#define STRING_TO_BOOLEAN(value) \
  ((strcmp(value, "TRUE") == 0) ? true : false)

#define CASE_TO_STRING_VR(value, result) \
  case value : { \
    return (result); \
  }

#define CASE_TO_STRING(value) \
  case value : { \
    return (#value); \
  }

#define ENUMERATION_TO_STRING(enumeration, cases) \
  static const T_CHAR * to_string(enumeration e) { \
    switch (e) { \
      cases \
    default : { \
      return ("<unknown>"); \
    } \
    } \
  }

#define CASE_TO_ENUMERATION_VR(value, result) \
  if (strcmp(s, value) == 0) { \
    return (result); \
  }

#define CASE_TO_ENUMERATION(value) \
  if (strcmp(s, #value) == 0) { \
    return (value); \
  }

#define STRING_TO_ENUMERATION(enumeration, cases) \
  static enumeration to_ ## enumeration(const T_CHAR * s) { \
    cases \
    return ((enumeration)0); \
  }

#define NVL(value, result) \
  ((value != NULL) ? value : result)

#define ANY_TYPES (0xffffffff)

/////////////////////////////////////////////////////////////////////////////
#undef STATIC

#endif // #ifndef _BASE_MACRO
