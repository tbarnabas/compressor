
/////////////////////////////////////////////////////////////////////////////
//
// cpr_cinput.h - ::CPR::CInput class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_CINPUT
#define _CPR_CINPUT

#include "cpr_configuration.h"

#include "cpr_cfile.h"

namespace CPR {

DERIVE_EXCEPTION_BEGIN(::CPR::EFile, EInput)
  UNKNOWN_FILE_FORMAT
DERIVE_EXCEPTION_END(EInput);

class CPR_EXPORT_IMPORT CInput :
  public ::CPR::CFile {
public:
  //! constructor
  CInput(const T_STRING & sFile = T_STRING());
  //! destructor
  virtual ~CInput();

  //! copy constructor
  CInput(const CInput & tInput);
  //! assignment operator
  CInput & operator=(const CInput & tInput);

  //! read type
  ::CPR::types ReadType();
}; // class CPR_EXPORT_IMPORT CInput

} // namespace CPR

#endif // #ifndef _CPR_CINPUT
