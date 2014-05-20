
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_ccompressor.h - ::CPR::COMPRESSOR::CCompressor class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_COMPRESSOR_CCOMPRESSOR
#define _CPR_COMPRESSOR_CCOMPRESSOR

#include "cpr_configuration.h"

#include "cpr_coutput.h"

namespace CPR {

namespace COMPRESSOR {

DERIVE_EXCEPTION_BEGIN(::BASE::EObject, ECompressor)
DERIVE_EXCEPTION_END(ECompressor);

class CPR_EXPORT_IMPORT CCompressor :
  public ::BASE::CObject {
public:
  MEMBER_GET(::CPR::types, Type);

public:
  //! constructor
  CCompressor(::CPR::types type);
  //! destructor
  virtual ~CCompressor();

  //! copy constructor
  CCompressor(const CCompressor & tCompressor);
  //! assignment operator
  CCompressor & operator=(const CCompressor & tCompressor);

  //! compress
  virtual void Compress(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput) = 0;
  //! expand
  virtual void Expand(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput) = 0;
}; // class CPR_EXPORT_IMPORT CCompressor

} // namespace COMPRESSOR

} // namespace CPR

#endif // #ifndef _CPR_COMPRESSOR_CCOMPRESSOR
