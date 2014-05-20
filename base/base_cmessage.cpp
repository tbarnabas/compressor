
/////////////////////////////////////////////////////////////////////////////
//
// base_cmessage.cpp - ::BASE::CMessage class source
//
/////////////////////////////////////////////////////////////////////////////

#include "base_cmessage.h"

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
CMessage::CMessage(const ::BASE::CTime & tTime, const T_STRING & sModule, const T_STRING & sClassPath, const T_STRING & sMethod, T_ULONG uLevel, T_ULONG uCode, const T_STRING & sMessage) :
  m_Time(tTime),
  m_Module(sModule),
  m_ClassPath(sClassPath),
  m_Method(sMethod),
  m_Level(uLevel),
  m_Code(uCode),
  m_Message(sMessage) {
} // CMessage


/////////////////////////////////////////////////////////////////////////////
CMessage::~CMessage() {
} // ~CMessage


/////////////////////////////////////////////////////////////////////////////
CMessage::CMessage(const CMessage & tMessage) :
  m_Time(tMessage.m_Time),
  m_Module(tMessage.m_Module),
  m_ClassPath(tMessage.m_ClassPath),
  m_Method(tMessage.m_Method),
  m_Level(tMessage.m_Level),
  m_Code(tMessage.m_Code),
  m_Message(tMessage.m_Message) {
} // CMessage


/////////////////////////////////////////////////////////////////////////////
CMessage & CMessage::operator=(const CMessage & tMessage) {
  m_Time = tMessage.m_Time;
  m_Module = tMessage.m_Module;
  m_ClassPath = tMessage.m_ClassPath;
  m_Method = tMessage.m_Method;
  m_Level = tMessage.m_Level;
  m_Code = tMessage.m_Code;
  m_Message = tMessage.m_Message;
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////

#define __BASE__CMessage__SetMessage__BUFFER_SIZE 1024

void CMessage::SetMessage(const T_CHAR * pMessage, ...) {
  T_CHAR pBuffer[__BASE__CMessage__SetMessage__BUFFER_SIZE];

  va_list tArguments;
  va_start(tArguments, pMessage);

#if (OS_FAMILY == OSF_WINDOWS)

  vsprintf_s(pBuffer, pMessage, tArguments);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX) | (PA_FAMILY == PAF_AVR))

  vsprintf(pBuffer, pMessage, tArguments);

#else
#error unsupported platform
#endif

  m_Message = pBuffer;
} // SetMessage

} // namespace BASE
