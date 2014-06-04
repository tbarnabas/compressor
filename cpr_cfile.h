
/////////////////////////////////////////////////////////////////////////////
//
// cpr_cfile.h - ::CPR::CFile class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_CFILE
#define _CPR_CFILE

#include "cpr_configuration.h"

namespace CPR {

DERIVE_EXCEPTION_BEGIN(::BASE::EObject, EFile)
  FILE_NOT_FOUND,
  UNABLE_TO_CREATE_FILE,
  UNABLE_TO_READ,
  UNABLE_TO_WRITE,
  TIMED_OUT
DERIVE_EXCEPTION_END(EFile);

class CPR_EXPORT_IMPORT CFile :
  public ::BASE::CObject {
public:
  //! enumeration for different operations
  enum operations {
    READ,
    WRITE,
    APPEND };
  //! convert operations enumeration to string
  ENUMERATION_TO_STRING(operations,
    CASE_TO_STRING(READ)
    CASE_TO_STRING(WRITE)
    CASE_TO_STRING(APPEND));
  //! convert string to operations enumeration
  STRING_TO_ENUMERATION(operations, 
    CASE_TO_ENUMERATION(READ)
    CASE_TO_ENUMERATION(WRITE)
    CASE_TO_ENUMERATION(APPEND));

  //! waiting for the specified operation
  static void STATIC_Wait(__T_INT iDescriptor, operations operation, const T_TIME & tTimeOut);

protected:
  //! pointer to file stream
  FILE * m_pFile;

  //! construct
  void __construct();
  //! destruct
  void __destruct();

public:
  MEMBER_GET(T_STRING, Name);
  MEMBER_GET(operations, Operation);
  MEMBER_GET(T_ULONG, TotalRead);
  MEMBER_GET(T_ULONG, TotalWrite);

public:
  //! constructor
  CFile(const T_STRING & sName, operations operation);
  //! destructor
  virtual ~CFile();

  //! copy constructor
  CFile(const CFile & tFile);
  //! assignment operator
  CFile & operator=(const CFile & tFile);

  //! get size
  T_ULONG GetSize();

  //! read buffer
  REFERENCE< ::BASE::CArray<T_BYTE> > Read(T_ULONG uLength = 0, const T_TIME tTimeOut = T_TIME(0xffffff));
  //! write buffer
  void Write(::BASE::CArray<T_BYTE> * pBuffer, const T_TIME tTimeOut = T_TIME(0xffffff));
  //! write buffer
  void Write(T_BYTE * pBuffer, T_ULONG uSize, const T_TIME tTimeOut = T_TIME(0xffffff));
}; // class CPR_EXPORT_IMPORT CFile

} // namespace CPR

#endif // #ifndef _CPR_CFILE
