
/////////////////////////////////////////////////////////////////////////////
//
// cpr_cfile.cpp - ::CPR::CFile class source
//
/////////////////////////////////////////////////////////////////////////////

#include "cpr_cfile.h"

namespace CPR {

/////////////////////////////////////////////////////////////////////////////
void CFile::__construct() {
  m_pFile = NULL;
  m_TotalRead = 0;
  m_TotalWrite = 0;
  switch (m_Operation) {
  case READ : {
    if (m_Name.IsValid() == true) {
      m_pFile = fopen(C_STR(m_Name), "rb");
//      fopen_s(&m_pFile, C_STR(m_Name), "rb");
      if (m_pFile == NULL) {
        EXCEPTION(CPR, ::CPR::CFile, __construct,
        MESSAGE("file not found"));
        THROW(EFile, FILE_NOT_FOUND);
      }
    } else {
      m_Name = "stdin";
      m_pFile = stdin;
//      _setmode(_fileno(stdin), _O_BINARY);
    }
    break;
  }
  case WRITE : {
    if (m_Name.IsValid() == true) {
      m_pFile = fopen(C_STR(m_Name), "wb");
//      fopen_s(&m_pFile, C_STR(m_Name), "wb");
      if (m_pFile == NULL) {
        EXCEPTION(CPR, ::CPR::CFile, __construct,
        MESSAGE("unable to create file"));
        THROW(EFile, UNABLE_TO_CREATE_FILE);
      }
    } else {
      m_Name = "stdout";
      m_pFile = stdout;
//      setmode(fileno(stdout), O_BINARY);
    }
    break;
  }
  case APPEND : {
    if (m_Name.IsValid() == true) {
      m_pFile = fopen(C_STR(m_Name), "ab");
//      fopen_s(&m_pFile, C_STR(m_Name), "wb");
      if (m_pFile == NULL) {
        EXCEPTION(CPR, ::CPR::CFile, __construct,
        MESSAGE("unable to create file"));
        THROW(EFile, UNABLE_TO_CREATE_FILE);
      }
    }
    break;
  }
  }

//  printf("file opened (name=\"%s\", operation=\"%s\")\n", C_STR(m_Name), to_string(m_Operation));
} // __construct


/////////////////////////////////////////////////////////////////////////////
void CFile::__destruct() {
  if ((m_pFile != NULL) && (m_pFile != stdin) && (m_pFile != stdout)) {
    fclose(m_pFile);
  }
  m_pFile = NULL;

//  printf("file closed (name=\"%s\")\n", C_STR(m_Name));
} // __destruct


/////////////////////////////////////////////////////////////////////////////
CFile::CFile(const T_STRING & sName, operations operation) :
  m_Name(sName),
  m_Operation(operation) {
  __construct();
} // CFile


/////////////////////////////////////////////////////////////////////////////
CFile::~CFile() {
  __destruct();
} // ~CFile


/////////////////////////////////////////////////////////////////////////////
CFile::CFile(const CFile & tFile) :
  ::BASE::CObject(tFile),
  m_Name(tFile.m_Name),
  m_Operation(tFile.m_Operation),
  m_TotalRead(tFile.m_TotalRead),
  m_TotalWrite(tFile.m_TotalWrite) {
  __construct();
} // CFile


/////////////////////////////////////////////////////////////////////////////
CFile & CFile::operator=(const CFile & tFile) {
  __destruct();
  ::BASE::CObject::operator=(tFile);
  m_Name = tFile.m_Name;
  m_Operation = tFile.m_Operation;
  m_TotalRead = tFile.m_TotalRead;
  m_TotalWrite = tFile.m_TotalWrite;
  __construct();
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////
T_ULONG CFile::GetSize() {
  T_ULONG uResult = 0;

  T_ULONG uPos = ftell(m_pFile);
  fseek(m_pFile, 0, SEEK_END);
  uResult = ftell(m_pFile);
  fseek(m_pFile, uPos, SEEK_SET);

//  printf("tell file (name=\"%s\") size: %ld\n", C_STR(m_Name), uResult);

  return (uResult);
} // GetSize


/////////////////////////////////////////////////////////////////////////////
REFERENCE< ::BASE::CArray<T_BYTE> > CFile::Read(T_ULONG uLength) {
  REFERENCE< ::BASE::CArray<T_BYTE> > tResult;
  T_ULONG uNumber = 0;

  if (uLength == 0) {
    uLength = GetSize();
  }

  // create a new result
  tResult.Create(new ::BASE::CArray<T_BYTE>(NULL, uLength));

  // read data from file
  uNumber = fread(tResult->GetElements(), sizeof(T_BYTE), tResult->GetSize(), m_pFile);
  m_TotalRead = m_TotalRead + uNumber;
  if (uNumber != uLength) {
    EXCEPTION(CPR, ::CPR::CFile, Read,
    MESSAGE("unable to read"));
    THROW(EFile, UNABLE_TO_READ);
  }

//  printf("%ld byte(s) read from file (name=\"%s\")\n", uNumber, C_STR(m_Name));

  return (tResult);
} // Read


/////////////////////////////////////////////////////////////////////////////
void CFile::Write(::BASE::CArray<T_BYTE> * pBuffer) {
  Write(pBuffer->GetElements(), pBuffer->GetSize());
} // Write


/////////////////////////////////////////////////////////////////////////////
void CFile::Write(T_BYTE * pBuffer, T_ULONG uSize) {
  T_ULONG uNumber = 0;

  // write data into file
  uNumber = fwrite((const void *)pBuffer, sizeof(T_BYTE), uSize, m_pFile);
  m_TotalWrite = m_TotalWrite + uNumber;
  if (uNumber != uSize) {
    EXCEPTION(CPR, ::CPR::CFile, Write,
    MESSAGE("unable to write"));
    THROW(EFile, UNABLE_TO_WRITE);
  }

//  printf("WRITE\n");
//  ::BASE::Dump(pBuffer, uSize);

  
//  printf("%ld byte(s) written into file (name=\"%s\")\n", uNumber, C_STR(m_Name));
} // Write

} // namespace CPR
