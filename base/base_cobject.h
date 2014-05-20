
/////////////////////////////////////////////////////////////////////////////
//
// base_cobject.h - ::BASE::CObject class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

// PLATFORM DEPENDENT

#pragma once
#ifndef _BASE_COBJECT
#define _BASE_COBJECT

#include "base_configuration.h"

#include "base_eexception.h"

namespace BASE {

DERIVE_ABSTRACT_EXCEPTION(::BASE::EException, EObject);

class BASE_EXPORT_IMPORT CObject {
public:
  //! enumeration for different storage types
  enum storages {
    STATIC,
    DYNAMIC };
  //! convert storages enumeration to string
  ENUMERATION_TO_STRING(storages,
    CASE_TO_STRING(STATIC)
    CASE_TO_STRING(DYNAMIC));
  //! convert string to storages enumeration
  STRING_TO_ENUMERATION(storages, 
    CASE_TO_ENUMERATION(STATIC)
    CASE_TO_ENUMERATION(DYNAMIC));

  //! enumeration for different operation types
  enum operations {
    READ,
    WRITE };
  //! convert operations enumeration to string
  ENUMERATION_TO_STRING(operations,
    CASE_TO_STRING(READ)
    CASE_TO_STRING(WRITE));
  //! convert string to operations enumeration
  STRING_TO_ENUMERATION(operations,
    CASE_TO_ENUMERATION(READ)
    CASE_TO_ENUMERATION(WRITE));

  //! enumeration for different synchronization types
  enum synchronizations {
    BLOCKED,
    BLOCKED_UNTIL_SEND,
    BLOCKED_UNTIL_RECEIVE,
    BLOCKED_UNTIL_PROCESS,
    NON_BLOCKED };
  //! convert synchronizations enumeration to string
  ENUMERATION_TO_STRING(synchronizations,
    CASE_TO_STRING(BLOCKED)
    CASE_TO_STRING(BLOCKED_UNTIL_SEND)
    CASE_TO_STRING(BLOCKED_UNTIL_RECEIVE)
    CASE_TO_STRING(BLOCKED_UNTIL_PROCESS)
    CASE_TO_STRING(NON_BLOCKED));
  //! convert string to synchronizations enumeration
  STRING_TO_ENUMERATION(synchronizations,
    CASE_TO_ENUMERATION(BLOCKED)
    CASE_TO_ENUMERATION(BLOCKED_UNTIL_SEND)
    CASE_TO_ENUMERATION(BLOCKED_UNTIL_RECEIVE)
    CASE_TO_ENUMERATION(BLOCKED_UNTIL_PROCESS)
    CASE_TO_ENUMERATION(NON_BLOCKED));

private:
  //! construct
  void __construct();

public:
  MEMBER_GET_SET(storages, Storage);
  MEMBER_GET_SET(T_ULONG, References);

public:
  //! constructor
  CObject();
  //! destructor
  virtual ~CObject();

  //! copy constructor
  CObject(const CObject & tObject);
  //! assignment operator
  CObject & operator=(const CObject & tObject);

  //! initialize
  virtual void Initialize() {}
  //! shutdown
  virtual void Shutdown(T_BOOLEAN bImmediate = false) {}
  //! maintain
  virtual void Maintain() {}
}; // class BASE_EXPORT_IMPORT CObject

} // namespace BASE

#endif // #ifndef _BASE_COBJECT
