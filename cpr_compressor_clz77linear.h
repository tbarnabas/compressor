
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_clz77Linear.h - ::CPR::COMPRESSOR::CLZ77Linear class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_COMPRESSOR_CLZ77LINEAR
#define _CPR_COMPRESSOR_CLZ77LINEAR

#include "cpr_configuration.h"

#include "cpr_compressor_ccompressor.h"

namespace CPR {

namespace COMPRESSOR {

DERIVE_EXCEPTION_BEGIN(::CPR::COMPRESSOR::ECompressor, ELZ77Linear)
DERIVE_EXCEPTION_END(ELZ77Linear);

class CPR_EXPORT_IMPORT CLZ77Linear :
  public ::CPR::COMPRESSOR::CCompressor {
protected:
  //! history size
  MEMBER(T_ULONG, HistorySize);
  
public:
  //! constructor
  CLZ77Linear(::CPR::types type, T_ULONG uHistorySize = 0);
  //! destructor
  virtual ~CLZ77Linear();

  //! copy constructor
  CLZ77Linear(const CLZ77Linear & tLZ77Linear);
  //! assignment operator
  CLZ77Linear & operator=(const CLZ77Linear & tLZ77Linear);

  //! compress
  virtual void Compress(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput);
  //! expand
  virtual void Expand(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput);
}; // class CPR_EXPORT_IMPORT CLZ77Linear

} // namespace COMPRESSOR

} // namespace CPR

#endif // #ifndef _CPR_COMPRESSOR_CLZ77LINEAR
