
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_clz77hash.h - ::CPR::COMPRESSOR::CLZ77Hash class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_COMPRESSOR_CLZ77HASH
#define _CPR_COMPRESSOR_CLZ77HASH

#include "cpr_configuration.h"

#include "cpr_compressor_ccompressor.h"

namespace CPR {

namespace COMPRESSOR {

DERIVE_EXCEPTION_BEGIN(::CPR::COMPRESSOR::ECompressor, ELZ77Hash)
DERIVE_EXCEPTION_END(ELZ77Hash);

class CPR_EXPORT_IMPORT CLZ77Hash :
  public ::CPR::COMPRESSOR::CCompressor {
protected:
  //! history size
  MEMBER(T_ULONG, HistorySize);
  
  //! hash table of positions
  typedef ::std::list<T_BYTE *> TPositions;
  TPositions m_tPositions[3840];
  
  //! calculate checksum
  T_DWORD CheckSum(T_BYTE * pPattern, T_ULONG uSize);
  //! insert
  void Insert(T_DWORD uCheckSum, T_BYTE * pPointer);
  //! maintain
  void Maintain(T_BYTE * pPosition, T_DWORD uCheckSum);
  //! match
  T_BYTE * Match(T_BYTE * pPosition, T_DWORD uCheckSum, T_BYTE * pPattern, T_ULONG * pLength);
  
public:
  //! constructor
  CLZ77Hash(::CPR::types type, T_ULONG uHistorySize = 0);
  //! destructor
  virtual ~CLZ77Hash();

  //! copy constructor
  CLZ77Hash(const CLZ77Hash & tLZ77Hash);
  //! assignment operator
  CLZ77Hash & operator=(const CLZ77Hash & tLZ77Hash);

  //! compress
  virtual void Compress(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput);
  //! expand
  virtual void Expand(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput);
}; // class CPR_EXPORT_IMPORT CLZ77Hash

} // namespace COMPRESSOR

} // namespace CPR

#endif // #ifndef _CPR_COMPRESSOR_CLZ77HASH
