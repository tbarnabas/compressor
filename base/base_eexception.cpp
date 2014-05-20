
/////////////////////////////////////////////////////////////////////////////
//
// base_eexception.cpp - ::BASE::EException class source
//
/////////////////////////////////////////////////////////////////////////////

#include "base_eexception.h"

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
EException::EException(const T_TIME & tTime, const T_STRING & sModule, const T_STRING & sClassPath, const T_STRING & sMethod, T_ULONG uLevel, T_ULONG uCode, const T_STRING & sMessage) :
  ::BASE::CMessage(tTime, sModule, sClassPath, sMethod, uLevel, uCode, sMessage) {
} // EException


/////////////////////////////////////////////////////////////////////////////
EException::EException(const ::BASE::CMessage & tMessage) :
  ::BASE::CMessage(tMessage) {
} // EException


/////////////////////////////////////////////////////////////////////////////
EException::~EException() {
} // ~EException


/////////////////////////////////////////////////////////////////////////////
EException::EException(const EException & tException) :
  ::BASE::CMessage(tException) {
} // EException


/////////////////////////////////////////////////////////////////////////////
EException & EException::operator=(const EException & tException) {
  ::BASE::CMessage::operator=(tException);
  return (* this);
} // operator=

} // namespace BASE
