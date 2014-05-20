
/////////////////////////////////////////////////////////////////////////////
//
// base_cmessage.h - ::BASE::CMessage class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

// PLATFORM DEPENDENT

#pragma once
#ifndef _BASE_CMESSAGE
#define _BASE_CMESSAGE

#include "base_configuration.h"

#include "base_cstring.h"
#include "base_ctime.h"

namespace BASE {

class BASE_EXPORT_IMPORT CMessage {
public:
  MEMBER_GET_SET(T_TIME, Time);
  MEMBER_GET_SET(T_STRING, Module);
  MEMBER_GET_SET(T_STRING, ClassPath);
  MEMBER_GET_SET(T_STRING, Method);
  MEMBER_GET_SET(T_ULONG, Level);
  MEMBER_GET_SET(T_ULONG, Code);
  MEMBER_GET_SET(T_STRING, Message);

public:
  //! constructor
  CMessage(const T_TIME & tTime = T_TIME(), const T_STRING & sModule = T_STRING(), const T_STRING & sClassPath = T_STRING(), const T_STRING & sMethod = T_STRING(), T_ULONG uLevel = 0, T_ULONG uCode = 0, const T_STRING & sMessage = T_STRING());
  //! destructor
  virtual ~CMessage();

  //! copy constructor
  CMessage(const CMessage & tMessage);
  //! assignment operator
  CMessage & operator=(const CMessage & tMessage);

  //! set message
  void SetMessage(const T_CHAR * pMessage, ...);
}; // class BASE_EXPORT_IMPORT CTMessage

} // namespace BASE

#endif // #ifndef _BASE_CMESSAGE
