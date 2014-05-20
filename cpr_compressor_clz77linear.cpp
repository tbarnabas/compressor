
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_clz77linear.cpp - ::CPR::COMPRESSOR::CLZ77Linear class source
//
/////////////////////////////////////////////////////////////////////////////

#include "cpr_compressor_clz77linear.h"

#define __CPR__COMPRESSOR__CLZ77LINEAR__LOOKSIZE 16

namespace CPR {

namespace COMPRESSOR {

/////////////////////////////////////////////////////////////////////////////
CLZ77Linear::CLZ77Linear(::CPR::types type, T_ULONG uHistorySize) :
  ::CPR::COMPRESSOR::CCompressor(type),
  m_HistorySize(uHistorySize - 16) {
} // CLZ77Linear


/////////////////////////////////////////////////////////////////////////////
CLZ77Linear::~CLZ77Linear() {
} // ~CLZ77Linear


/////////////////////////////////////////////////////////////////////////////
CLZ77Linear::CLZ77Linear(const CLZ77Linear & tLZ77Linear) :
  ::CPR::COMPRESSOR::CCompressor(tLZ77Linear),
  m_HistorySize(tLZ77Linear.m_HistorySize) {
} // CLZ77Linear


/////////////////////////////////////////////////////////////////////////////
CLZ77Linear & CLZ77Linear::operator=(const CLZ77Linear & tLZ77Linear) {
  ::CPR::COMPRESSOR::CCompressor::operator=(tLZ77Linear);
  m_HistorySize = tLZ77Linear.m_HistorySize;
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////

//! write word
#define __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteWord(value) \
  { \
    ::BASE::CArray<T_BYTE> tBuffer(NULL, 2); \
    ::BASE::setword(tBuffer.GetElements(), (value)); \
    pOutput->Write(&tBuffer); \
  }

  //! write token with code 4 bit and length 4 bit
#define __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteTokenByte(code, length) \
  { \
    ::BASE::CArray<T_BYTE> tBuffer(NULL, 1); \
    ::BASE::setbyte(tBuffer.GetElements(), (((code) & 15) << 8) | ((length) & 15)); \
    pOutput->Write(&tBuffer); \
  }

//! write token with length 4 bit and offset 12 bit
#define __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteTokenWord(length, offset) \
  { \
    ::BASE::CArray<T_BYTE> tBuffer(NULL, 2); \
    ::BASE::setword(tBuffer.GetElements(), (((length) & 15) << 12) | ((offset) & 4095), true); \
    pOutput->Write(&tBuffer); \
  }

//! flush characters
#define __CPR__COMPRESSOR__CLZ77LINEAR__Compress__FlushCharacters \
  if (tCharacters.empty() == false) { \
    __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteTokenByte(0, tCharacters.size()); \
    ::BASE::CArray<T_BYTE> tBuffer(NULL, tCharacters.size()); \
    for (T_ULONG i = 0; i < tBuffer.GetSize(); i++) { \
      tBuffer[i] = (T_BYTE)tCharacters.front(); \
      tCharacters.pop(); \
    } \
    pOutput->Write(&tBuffer); \
  }

void CLZ77Linear::Compress(::BASE::CArray<T_BYTE> * pInput, ::CPR::COutput * pOutput) {
  T_ULONG uPosition = 0;
  ::std::queue<T_CHAR> tCharacters;
  
  // write history size
  __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteWord(m_HistorySize);
  
  while (uPosition < pInput->GetSize()) {
  	T_BOOLEAN bMatch = false;
  	T_BOOLEAN bMaximalMatch = false;
    T_ULONG uMatchOffset = 0;
    T_ULONG uMatchLength = 0;

	  // set look length
	  T_ULONG uLookLength = pInput->GetSize() - uPosition;
	  if (uLookLength > __CPR__COMPRESSOR__CLZ77LINEAR__LOOKSIZE) {
	    uLookLength = __CPR__COMPRESSOR__CLZ77LINEAR__LOOKSIZE;
	  }

    // set history offset
    T_ULONG uHistoryOffset = uPosition; 
    if (uHistoryOffset > m_HistorySize) {
      uHistoryOffset = m_HistorySize;
    }
    
//    printf("INPUT SIZE : %d\n", pInput->GetSize());
//    printf("POSITION %d, HISTORY OFFSET : %d, LOOK LENGTH : %d\n", uPosition, uHistoryOffset, uLookLength);
   
    // search maximal matching in history window (very slow matching)
    while ((bMaximalMatch == false) && (uHistoryOffset > 0)) {
      // match pattern at current position
      T_ULONG uHistoryPosition = uPosition - uHistoryOffset;
      T_ULONG i = 0;
      T_BOOLEAN bExit = false;
      while ((bExit == false) && (i < uLookLength)) {
        if ((* pInput)[uHistoryPosition + i] != (* pInput)[uPosition + i]) {
          bExit = true;
        } else {
          i = i + 1;
          // set maximal matching
          if ((i > uMatchLength) && (i >= 2)) {
            uMatchLength = i;
            uMatchOffset = uHistoryOffset;
            bMatch = true;
            if (uMatchLength == uLookLength) {
              bMaximalMatch = true;
//              printf("MAXIMAL ");
            }
//            printf("MATCH-- HISTORY POSITION : %d, POSITION %d, HISTORY OFFSET : %d, LOOK LENGTH : %d, MATCH LENGTH : %d\n", uHistoryPosition, uPosition, uHistoryOffset, uLookLength, uMatchLength);
          }
        }
      }        
      
      uHistoryOffset = uHistoryOffset - 1;
    }

    if (bMatch == true) {
      // flush characters
      __CPR__COMPRESSOR__CLZ77LINEAR__Compress__FlushCharacters;

      // write token
      __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteTokenWord(uMatchLength - 1, uMatchOffset);

      // shift sliding window
      uPosition = uPosition + uMatchLength;
    } else {
//      printf("WRITE UNCOMPRESSED CHAR: %c\n", (* pInput)[uPosition]);
      
      // flush characters
      if (tCharacters.size() == 15) {
        __CPR__COMPRESSOR__CLZ77LINEAR__Compress__FlushCharacters;
      }

      // write character
      tCharacters.push((* pInput)[uPosition]);

      // shift sliding window
      uPosition = uPosition + 1;
    }    
  }

  // flush characters
  __CPR__COMPRESSOR__CLZ77LINEAR__Compress__FlushCharacters;

  // write EOF token
  __CPR__COMPRESSOR__CLZ77LINEAR__Compress__WriteTokenByte(0, 0);
} // Compress


/////////////////////////////////////////////////////////////////////////////

//! write character
#define __CPR__COMPRESSOR__CLZ77LINEAR__Expand__WriteCharacter(c) \
  { \
    tBuffer[0] = c; \
    pOutput->Write(&tBuffer); \
  }

void CLZ77Linear::Expand(::BASE::CArray<T_BYTE> * pInput, ::CPR::COutput * pOutput) {
  ::BASE::CArray<T_BYTE> tBuffer(NULL, 1); \

  // create history
  m_HistorySize = ::BASE::getword(&(* pInput)[1]);
  T_ULONG uBufferSize = m_HistorySize + 16;
  T_BYTE tHistory[uBufferSize];
  T_ULONG uHistoryPosition = 0;
  
  // read input
  T_BOOLEAN bExit = false;
  T_ULONG uPosition = 3;
  do {
    T_ULONG uCode = 0;
    T_ULONG uLength = 0;
    T_ULONG uHistoryOffset = 0;
    
    uCode = (::BASE::getbyte(&(* pInput)[uPosition]) >> 4) & 15;
    if (uCode == 0) {
      uLength = ::BASE::getbyte(&(* pInput)[uPosition]) & 15;
      if (uLength != 0) {
        // write uncompressed characters
        for (T_ULONG i = 0; i < uLength; i++) {
          tHistory[(uHistoryPosition + i) % uBufferSize] = (* pInput)[uPosition + 1 + i];
          __CPR__COMPRESSOR__CLZ77LINEAR__Expand__WriteCharacter((* pInput)[uPosition + 1 + i]);
        }
        uHistoryPosition = (uHistoryPosition + uLength) % uBufferSize;

        uPosition = uPosition + 1 + uLength;
      } else {
        // reach end of file
        uPosition = uPosition + 1;
        bExit = true;
      }
    } else {
      uLength = uCode + 1;
      uHistoryOffset = ::BASE::getword(&(* pInput)[uPosition], true) & 4095;

      // write compressed characters
      for (T_ULONG i = 0; i < uLength; i++) {
        T_ULONG uPosition = 0;
        if (uHistoryPosition >= uHistoryOffset) {
          uPosition = uHistoryPosition - uHistoryOffset;
        } else {
          uPosition = uBufferSize - (uHistoryOffset- uHistoryPosition);
        }
        tHistory[(uHistoryPosition + i) % uBufferSize] = tHistory[(uPosition + i) % uBufferSize];
        __CPR__COMPRESSOR__CLZ77LINEAR__Expand__WriteCharacter(tHistory[(uPosition + i) % uBufferSize]);
      }
      uHistoryPosition = (uHistoryPosition + uLength) % uBufferSize;

      uPosition = uPosition + 2;
    }
  } while (bExit == false);
} // Expand

} // namespace COMPRESSOR

} // namespace CPR
