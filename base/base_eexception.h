
/////////////////////////////////////////////////////////////////////////////
//
// base_eexception.h - ::BASE::EException class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_EEXCEPTION
#define _BASE_EEXCEPTION

#include "base_configuration.h"

#include "base_cmessage.h"

namespace BASE {

class BASE_EXPORT_IMPORT EException :
  public ::BASE::CMessage {
public:
  //! constructor
  EException(const T_TIME & tTime = T_TIME(), const T_STRING & sModule = T_STRING(), const T_STRING & sClassPath = T_STRING(), const T_STRING & sMethod = T_STRING(), T_ULONG uLevel = 0, T_ULONG uCode = 0, const T_STRING & sMessage = T_STRING());
  //! constructor
  EException(const ::BASE::CMessage & tMessage);
  //! destructor
  virtual ~EException();

  //! copy constructor
  EException(const EException & tException);
  //! assignment operator
  EException & operator=(const EException & tException);
}; // class BASE_EXPORT_IMPORT EException

} // namespace BASE

#endif // #ifndef _BASE_EEXCEPTION
