
/////////////////////////////////////////////////////////////////////////////
//
// cpr_cinput.h - ::CPR::COutput class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_COUTPUT
#define _CPR_COUTPUT

#include "cpr_configuration.h"

#include "cpr_cfile.h"

namespace CPR {

DERIVE_EXCEPTION_BEGIN(::CPR::EFile, EOutput)
DERIVE_EXCEPTION_END(EOutput);

class CPR_EXPORT_IMPORT COutput :
  public ::CPR::CFile {
public:
  //! constructor
  COutput(const T_STRING & sFile = T_STRING(), ::CPR::CFile::operations operation = ::CPR::CFile::WRITE);
  //! destructor
  virtual ~COutput();

  //! copy constructor
  COutput(const COutput & tOutput);
  //! assignment operator
  COutput & operator=(const COutput & tOutput);

  //! write type
  void WriteType(::CPR::types type);
}; // class CPR_EXPORT_IMPORT COutput

} // namespace CPR

#endif // #ifndef _CPR_COUTPUT
