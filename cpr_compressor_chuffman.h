
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_chuffman.h - ::CPR::COMPRESSOR::CHuffman class header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_COMPRESSOR_CHUFFMAN
#define _CPR_COMPRESSOR_CHUFFMAN

#include "cpr_configuration.h"

#include "cpr_compressor_ccompressor.h"

namespace CPR {

namespace COMPRESSOR {

DERIVE_EXCEPTION_BEGIN(::CPR::COMPRESSOR::ECompressor, EHuffman)
DERIVE_EXCEPTION_END(EHuffman);

class CPR_EXPORT_IMPORT CHuffman :
  public ::CPR::COMPRESSOR::CCompressor {
private:
  //! type definition for node
  struct TNode {
    T_BOOLEAN m_bLeaf;
    T_ULONG m_uFrequency;
    T_WORD m_uValue;
    T_DWORD m_uCode;
    T_WORD m_uCodeLength;
    struct TNode * m_pLeft;
    struct TNode * m_pRight;
  };

  //! array for frequences
  T_ULONG m_tFrequencies[257];

  //! node pool for huffman tree
  TNode m_tPool[513];
  //! pool size
  T_ULONG m_uPoolSize;

  //! priority queue
  TNode * m_tPriorityQueue[257];
  //! priority queue size
  T_ULONG m_uPriorityQueueSize;

  //! create node in pool
  TNode * create(T_BOOLEAN bLeaf, T_ULONG uFrequency, T_WORD uValue, struct TNode * pLeft, struct TNode * pRight);
  //! insert node into priority queue
  void insert(TNode * pNode);
  //! remove node from priority queue
  TNode * remove();
  //! build huffman code
  void build(TNode * pNode, T_DWORD uCode, T_WORD uCodeLength);
  //! initialize table
  void initializeTables();
  //! build huffman codes
  TNode * buildHuffmanCodes();
    
public:
  //! constructor
  CHuffman();
  //! destructor
  virtual ~CHuffman();

  //! copy constructor
  CHuffman(const CHuffman & tHuffman);
  //! assignment operator
  CHuffman & operator=(const CHuffman & tHuffman);

  //! compress
  virtual void Compress(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput);
  //! expand
  virtual void Expand(::BASE::CArray<T_BYTE> * pBuffer, ::CPR::COutput * pOutput);
}; // class CPR_EXPORT_IMPORT CHuffman

} // namespace COMPRESSOR

} // namespace CPR

#endif // #ifndef _CPR_COMPRESSOR_CHUFFMAN
