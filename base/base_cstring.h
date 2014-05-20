
/////////////////////////////////////////////////////////////////////////////
//
// base_cstring.h - ::BASE::CString class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

// PLATFORM DEPENDENT
// note: not implemented on PAF_AVR platforms

#pragma once
#ifndef _BASE_CSTRING
#define _BASE_CSTRING

#include "base_configuration.h"

namespace BASE {

#define C_STR(s) ((const T_CHAR *)s)

class BASE_EXPORT_IMPORT CString {
private:
  //! pointer to string
  T_CHAR * m_pString;

  //! copy string
  static void STATIC_strcpy(T_CHAR * pDestination, const T_CHAR * pSource, T_ULONG uLength);
  //! get length
  static T_ULONG STATIC_strlen(const T_CHAR * pString);
  //! compare strings
  static T_INT STATIC_strcmp(const T_CHAR * pLeft, const T_CHAR * pRight);

  //! construct
  void __construct(const T_CHAR * pString, T_ULONG uLength);
  //! destruct
  void __destruct();

public:
  //! length
  MEMBER_GET(T_ULONG, Length);

public:
  //! constructor
  CString(const T_CHAR * pString = NULL, T_ULONG uLength = 0);
  //! constructor
  CString(T_CHAR cChar);

#if ((OS_FAMILY == OSF_WINDOWS) | (OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  //! addition operator
  CString(T_ULONG uValue);
  //! addition operator
  CString(T_LONG iValue);
  //! addition operator
  CString(T_DOUBLE dValue);

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

  //! destructor
  virtual ~CString();

  //! copy constructor
  CString(const CString & tString);
  //! assignment operator
  CString & operator=(const CString & tString);
  //! assignment operator
  CString & operator=(const T_CHAR * pString);

  //! array subscript operator
  T_CHAR & operator[](T_ULONG uIndex) const;
  //! array subscript operator
  T_CHAR & operator[](T_INT uIndex) const;
  //! type cast operator
  operator const T_CHAR * () const;

  //! equality operator
  T_BOOLEAN operator==(const T_CHAR * pString) const;
  //! equality operator
  T_BOOLEAN operator==(const CString & tString) const;
  //! inequality operator
  T_BOOLEAN operator!=(const T_CHAR * pString) const;
  //! inequality operator
  T_BOOLEAN operator!=(const CString & tString) const;
  // less than operator
  T_BOOLEAN operator<(const CString & tString) const;

  //! addition operator
  CString operator+(const CString & tString) const;
  //! addition operator
  CString operator+(const T_CHAR * pString) const;
  //! addition operator
  CString operator+(T_CHAR cChar) const;

#if ((OS_FAMILY == OSF_WINDOWS) | (OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  //! addition operator
  CString operator+(T_ULONG uValue) const;
  //! addition operator
  CString operator+(T_LONG iValue) const;
  //! addition operator
  CString operator+(T_DOUBLE dValue) const;

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

  //! if string is valid then return true
  T_BOOLEAN IsValid() const;

  // return true if nth character is lower case
  T_BOOLEAN IsLower(T_ULONG uIndex) const;
  // return true if nth character is upper case
  T_BOOLEAN IsUpper(T_ULONG uIndex) const;

  // return true if nth character is numeric
  T_BOOLEAN IsNumeric(T_ULONG uIndex) const;

  //! to lower case
  CString ToLower() const;
  //! to upper case
  CString ToUpper() const;

  //! substring
  CString SubString(T_ULONG uIndex, T_ULONG uLength = 0) const;
  //! find subtring at specified index
  T_BOOLEAN Find(T_ULONG uIndex, const T_STRING & sValue) const;
}; // class BASE_EXPORT_IMPORT CString

} // namespace BASE

#endif // #ifndef _BASE_CSTRING
