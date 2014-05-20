
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_chuffman.cpp - ::CPR::COMPRESSOR::CHuffman class source
//
/////////////////////////////////////////////////////////////////////////////

#include "cpr_compressor_chuffman.h"

namespace CPR {

namespace COMPRESSOR {

/////////////////////////////////////////////////////////////////////////////
CHuffman::TNode * CHuffman::create(T_BOOLEAN bLeaf, T_ULONG uFrequency, T_WORD uValue, struct TNode * pLeft, struct TNode * pRight) {
  m_tPool[m_uPoolSize].m_bLeaf = bLeaf;
  m_tPool[m_uPoolSize].m_pLeft = pLeft;
  m_tPool[m_uPoolSize].m_pRight = pRight;
  if (bLeaf == true) {
    m_tPool[m_uPoolSize].m_uFrequency = uFrequency;
    m_tPool[m_uPoolSize].m_uValue = uValue;
  } else {
    m_tPool[m_uPoolSize].m_uFrequency = pLeft->m_uFrequency + pRight->m_uFrequency;
    m_tPool[m_uPoolSize].m_uValue = 0;
  }

//printf("CREATE %p %ld %ld %p %p\n", &m_tPool[m_uPoolSize], m_tPool[m_uPoolSize].m_uFrequency, m_tPool[m_uPoolSize].m_uValue, pLeft, pRight);

  m_uPoolSize++;

  return (&m_tPool[m_uPoolSize - 1]);
} // create


/////////////////////////////////////////////////////////////////////////////
void CHuffman::insert(TNode * pNode) {
  TNode * * pPriorityQueue = m_tPriorityQueue - 1;
  T_ULONG i = m_uPriorityQueueSize + 1;
  T_ULONG j = 0;

  do {
    j = (i >> 1);
    if (j != 0) {
      if (pPriorityQueue[j]->m_uFrequency <= pNode->m_uFrequency) {
        j = 0;
      } else {
        pPriorityQueue[i] = pPriorityQueue[j];
        i = j;  
      }
    }
  } while (j != 0);

  pPriorityQueue[i] = pNode;
  m_uPriorityQueueSize++;
} // Insert
 

/////////////////////////////////////////////////////////////////////////////
CHuffman::TNode * CHuffman::remove() {
 TNode * pResult = NULL;

 if (m_uPriorityQueueSize != 0) {
   pResult = m_tPriorityQueue[0];

   TNode * * pPriorityQueue = m_tPriorityQueue - 1;
   T_ULONG i = 1;
   T_ULONG j = 0;

   do {
     j = (i << 1);
     if (j <= m_uPriorityQueueSize) {
       if (((j + 1) <= m_uPriorityQueueSize) && (pPriorityQueue[j + 1]->m_uFrequency < pPriorityQueue[j]->m_uFrequency)) {
         j++;
       }
       pPriorityQueue[i] = pPriorityQueue[j];
       i = j;
     }
   } while (j <= m_uPriorityQueueSize);
   pPriorityQueue[i] = pPriorityQueue[m_uPriorityQueueSize];

   m_uPriorityQueueSize--;
 }

 return (pResult);
} // Remove


/////////////////////////////////////////////////////////////////////////////
void CHuffman::build(TNode * pNode, T_DWORD uCode, T_WORD uCodeLength) {
  if (pNode->m_bLeaf == true) {
    pNode->m_uCode = uCode;
    pNode->m_uCodeLength = uCodeLength;

//    printf("VALUE: %X, CODE: %X, LENGTH: %ld\n", pNode->m_uValue, pNode->m_uCode, pNode->m_uCodeLength);
  } else {
    T_DWORD uMask = (1 << uCodeLength);

    build(pNode->m_pLeft, uCode & (~uMask), uCodeLength + 1);
    build(pNode->m_pRight, uCode | uMask, uCodeLength + 1);
  }
} // build


/////////////////////////////////////////////////////////////////////////////
void CHuffman::initializeTables() {
  T_ULONG i = 0;

  // initialize tables
  for (i = 0; i < 256; i++) {
    m_tFrequencies[i] = 0;
    m_tPriorityQueue[i] = NULL;
  }
  m_tFrequencies[256] = 1;
  m_tPriorityQueue[256] = NULL;
} // initializeTables


/////////////////////////////////////////////////////////////////////////////
CHuffman::TNode * CHuffman::buildHuffmanCodes() {
  TNode * pResult = NULL;
  T_ULONG i = 0;

  // create initial huffman tree
  m_uPoolSize = 0;
  m_uPriorityQueueSize = 0;
  for (i = 0; i < 257; i++) {
    if (m_tFrequencies[i] != 0) {
      insert(create(true, m_tFrequencies[i], i, NULL, NULL));
    }
  }

  // build optimal huffman tree from priority queue
  while (m_uPriorityQueueSize > 1) {
    insert(create(false, 0, 0, remove(), remove()));
  }

  // remove root element from priority queue
  pResult = remove();

  // build huffman codes
  build(pResult, 0, 0);

  return (pResult);
} // buildHuffmanCodes


/////////////////////////////////////////////////////////////////////////////
CHuffman::CHuffman() :
  ::CPR::COMPRESSOR::CCompressor(::CPR::HUFFMAN) {
} // CHuffman


/////////////////////////////////////////////////////////////////////////////
CHuffman::~CHuffman() {
} // ~CHuffman


/////////////////////////////////////////////////////////////////////////////
CHuffman::CHuffman(const CHuffman & tHuffman) :
  ::CPR::COMPRESSOR::CCompressor(tHuffman) {
} // CHuffman


/////////////////////////////////////////////////////////////////////////////
CHuffman & CHuffman::operator=(const CHuffman & tHuffman) {
  ::CPR::COMPRESSOR::CCompressor::operator=(tHuffman);
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////

#define __CPR__COMPRESSOR__CHUFFMAN__Compress__WRITE \
  \
  for (j = 0; j < pNode->m_uCodeLength; j++) { \
    uOutput = ((pNode->m_uCode >> j) & 1); \
    \
    uOutput <<= (7 - uOutputBitPosition); \
    (* tResult)[uOutputBytePosition] |= uOutput; \
    uOutputBitPosition++; \
    if (uOutputBitPosition > 7) { \
      uOutputBitPosition = 0; \
      uOutputBytePosition++; \
    } \
  }

void CHuffman::Compress(::BASE::CArray<T_BYTE> * pInput, ::CPR::COutput * pOutput) {
  REFERENCE< ::BASE::CArray<T_BYTE> > tResult;
  T_ULONG i = 0;
  T_ULONG j = 0;
  T_ULONG uSize = 0;
  T_WORD uHeaderSize = 0;
  ::std::map<T_WORD, TNode *> tCodes;

  // initialize tables
  initializeTables();

  // calculate frequencies
  for (i = 0; i < pInput->GetSize(); i++) {
    m_tFrequencies[(* pInput)[i]]++; 
  }

  // build huffman codes
  buildHuffmanCodes();

  // calculate output size and create map of codes
  uSize = 0;
  for (i = 0; i < m_uPoolSize; i++) {
    if (m_tPool[i].m_bLeaf == true) {
      uSize = uSize + m_tPool[i].m_uFrequency * m_tPool[i].m_uCodeLength;
      tCodes.insert(::std::make_pair(m_tPool[i].m_uValue, &m_tPool[i]));
    }
  }
  uSize = (uSize >> 3) + (((uSize % 8) == 0) ? 0 : 1);

  // calculate header and body size 
  uHeaderSize = (tCodes.size() * 6) + 2;
  uSize = uSize + uHeaderSize;

  // create result
  tResult.Create(new ::BASE::CArray<T_BYTE>(NULL, uSize));
  for (i = 0; i < tResult->GetSize(); i++) {
    (* tResult)[i] = 0;
  }

  // create header
  ::BASE::setword(&(* tResult)[0], tCodes.size());
//  printf("HEADER SIZE : %ld\n", uHeaderSize);
  j = 0;
  for (i = 0; i < m_uPoolSize; i++) {
    if (m_tPool[i].m_bLeaf == true) {
      ::BASE::setdword(&((* tResult)[2 + (j * 6)]), m_tPool[i].m_uFrequency);
      ::BASE::setword(&((* tResult)[2 + (j * 6) + 4]), m_tPool[i].m_uValue);
      j++;
//      printf("HEADER : %ld %ld\n", m_tPool[i].m_uFrequency, m_tPool[i].m_uValue);
    }
  }

  // write output bit by bit
  TNode * pNode = NULL;
  T_ULONG uOutputBytePosition = uHeaderSize;
  T_ULONG uOutputBitPosition = 0;
  T_BYTE uOutput = 0;
  for (i = 0; i < pInput->GetSize(); i++) {
    pNode = tCodes.find((* pInput)[i])->second;
    __CPR__COMPRESSOR__CHUFFMAN__Compress__WRITE;
  }
  pNode = tCodes.find(256)->second;
  __CPR__COMPRESSOR__CHUFFMAN__Compress__WRITE;

  pOutput->Write(tResult);
} // Compress


/////////////////////////////////////////////////////////////////////////////
void CHuffman::Expand(::BASE::CArray<T_BYTE> * pInput, ::CPR::COutput * pOutput) {
  T_ULONG i = 0;
  T_WORD uHeaderSize = 0;
  T_BYTE uOutput = 0;

  // initialize tables
  initializeTables();

  // read header
  uHeaderSize = ::BASE::getword(&(* pInput)[1]);
//  printf("HEADER SIZE : %ld\n", uHeaderSize);
  for (i = 0; i < uHeaderSize; i++) {
    T_ULONG uFrequency = ::BASE::getdword(&(* pInput)[1 + 2 + (i * 6)]);
    T_WORD uValue = ::BASE::getword(&(* pInput)[1 + 2 + (i * 6) + 4]);
    m_tFrequencies[uValue] = uFrequency;
//    printf("HEADER : %ld %ld\n", uValue, uFrequency);
  }

  // build huffman codes
  TNode * pRoot = buildHuffmanCodes();

  // read input bit by bit
  T_ULONG uInputBytePosition = 1 + (uHeaderSize * 6) + 2;
  T_ULONG uInputBitPosition = 0;
  T_WORD uInput = 0;
  TNode * pNode = pRoot;
  while ((uInput != 256) && (uInputBytePosition < pInput->GetSize())) {
    uInput = ((* pInput)[uInputBytePosition] & (1 << (7 - uInputBitPosition))) >> (7 - uInputBitPosition);
//    printf("INPUT > %ld\n", uInput);

    if (uInput == 0) {
      pNode = pNode->m_pLeft;
    } else {
      pNode = pNode->m_pRight;
    }
    uInput = pNode->m_uValue;

    if (pNode->m_bLeaf == true) {
      if (uInput != 256) {
        uOutput = (T_BYTE)uInput;
        pOutput->Write(&uOutput, 1);
//        printf("OUTPUT > %ld %ld\n", uInputBytePosition, pNode->m_uValue);
      }
      pNode = pRoot;
    }

    uInputBitPosition++;
    if (uInputBitPosition > 7) {
      uInputBitPosition = 0;
      uInputBytePosition++;
    }
  }
} // Expand

} // namespace COMPRESSOR

} // namespace CPR
