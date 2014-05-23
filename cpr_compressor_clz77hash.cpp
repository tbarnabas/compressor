
/////////////////////////////////////////////////////////////////////////////
//
// cpr_compressor_clz77hash.cpp - ::CPR::COMPRESSOR::CLZ77Hash class source
//
/////////////////////////////////////////////////////////////////////////////

#include "cpr_compressor_clz77hash.h"

#define __CPR__COMPRESSOR__CLZ77HASH__LOOKSIZE 16

namespace CPR {

namespace COMPRESSOR {

/////////////////////////////////////////////////////////////////////////////
T_DWORD CLZ77Hash::CheckSum(T_BYTE * pPattern, T_ULONG uSize) {
  T_DWORD uResult = 0;
  
  switch (uSize) {
  case 1 : {
    uResult = (T_DWORD)pPattern[0] + 0;
    break;
  }    
  case 2 : {
    uResult = (T_DWORD)pPattern[0] + (T_DWORD)pPattern[1] + 256;
    break;
  }    
  case 4 : {
    uResult = (T_DWORD)pPattern[0] + (T_DWORD)pPattern[1] + (T_DWORD)pPattern[2] + (T_DWORD)pPattern[3] + 256 + 512;
    break;
  }    
  case 8 : {
    uResult = (T_DWORD)pPattern[0] + (T_DWORD)pPattern[1] + (T_DWORD)pPattern[2] + (T_DWORD)pPattern[3] + (T_DWORD)pPattern[4] + (T_DWORD)pPattern[5] + (T_DWORD)pPattern[6] + (T_DWORD)pPattern[7] + 256 + 512 + 1024;
    break;
  }    
  }
  
//   printf("CREATE CHECKSUM FOR PATTERN\n");
//   ::BASE::Dump(pPattern, uSize);
//   printf("CHECKSUM: %d\n", uResult);

  return (uResult);
} // CheckSum


/////////////////////////////////////////////////////////////////////////////
void CLZ77Hash::Insert(T_ULONG uCheckSum, T_BYTE * pPointer) {
  m_tPositions[uCheckSum].push_back(pPointer);
//  printf("INSERT CHECKSUM: %d, POINTER: %p, ELEMENTS: %ld\n", uCheckSum, pPointer, m_tPositions[uCheckSum].size());
} // Insert


/////////////////////////////////////////////////////////////////////////////
void CLZ77Hash::Maintain(T_BYTE * pPosition, T_ULONG uCheckSum) {
  T_BYTE * pPointer = NULL;
  T_BOOLEAN bExit = false;

  while ((bExit == false) && (m_tPositions[uCheckSum].empty() == false)) {
    if (m_tPositions[uCheckSum].empty() == false) {
      pPointer = m_tPositions[uCheckSum].front();     
      if ((pPosition - pPointer) > m_HistorySize) {
        m_tPositions[uCheckSum].pop_front();
      } else {
        bExit = true;
      }
    }
  }
} // Maintain


/////////////////////////////////////////////////////////////////////////////
T_BYTE * CLZ77Hash::Match(T_BYTE * pPosition, T_DWORD uCheckSum, T_BYTE * pPattern, T_ULONG * pLength) {
  T_BYTE * pResult = NULL;
  T_BOOLEAN bMatch = false;
  T_ULONG uLength = (* pLength);
  (* pLength) = 0;

//  printf("MATCH CHECKSUM: %d, PATTERN: %p, LENGTH: %d\n", uCheckSum, pPattern, uLength);

  // maintain table
  Maintain(pPosition, uCheckSum);
  
  TPositions::iterator i = m_tPositions[uCheckSum].begin();
  while ((bMatch == false) && (i != m_tPositions[uCheckSum].end())) {
    T_BOOLEAN bExit = false;

    T_ULONG j = 0;
  
    while ((bMatch == false) && (bExit == false) && (j < uLength)) {
      if ((* i)[j] != pPattern[j]) {
        bExit = true;
      } else {
        j = j + 1;
        if (j > (* pLength)) {
          (* pLength) = j;
          pResult = (* i);
//          printf("MATCH POINTER %p: OFFSET : %ld\n", pResult, pPosition - pResult);
          if ((* pLength) == uLength) {
            bMatch = true;
          }
        }
      } 
    }
  
    i++;
  }

  return (pResult);
} // Match
  
/////////////////////////////////////////////////////////////////////////////
CLZ77Hash::CLZ77Hash(::CPR::types type, T_ULONG uHistorySize) :
  ::CPR::COMPRESSOR::CCompressor(type),
  m_HistorySize(uHistorySize - 16) {
} // CLZ77Hash


/////////////////////////////////////////////////////////////////////////////
CLZ77Hash::~CLZ77Hash() {
} // ~CLZ77Hash


/////////////////////////////////////////////////////////////////////////////
CLZ77Hash::CLZ77Hash(const CLZ77Hash & tLZ77Hash) :
  ::CPR::COMPRESSOR::CCompressor(tLZ77Hash),
  m_HistorySize(tLZ77Hash.m_HistorySize) {
} // CLZ77Hash


/////////////////////////////////////////////////////////////////////////////
CLZ77Hash & CLZ77Hash::operator=(const CLZ77Hash & tLZ77Hash) {
  ::CPR::COMPRESSOR::CCompressor::operator=(tLZ77Hash);
  m_HistorySize = tLZ77Hash.m_HistorySize;
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////

//! write word
#define __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteWord(value) \
  ::BASE::setword((T_BYTE *)&uWORD, (value)); \
  pOutput->Write((T_BYTE *)&uWORD, 2);

  //! write token with code 4 bit and length 4 bit
#define __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteTokenByte(code, length) \
  ::BASE::setbyte(&uBYTE, (((code) & 15) << 8) | ((length) & 15)); \
  pOutput->Write(&uBYTE, 1);

//! write token with length 4 bit and offset 12 bit
#define __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteTokenWord(length, offset) \
  ::BASE::setword((T_BYTE *)&uWORD, (((length) & 15) << 12) | ((offset) & 4095), true); \
  pOutput->Write((T_BYTE *)&uWORD, 2);

//! flush characters
#define __CPR__COMPRESSOR__CLZ77HASH__Compress__FlushCharacters \
  if (tCharacters.empty() == false) { \
    __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteTokenByte(0, tCharacters.size()); \
    ::BASE::CArray<T_BYTE> tBuffer(NULL, tCharacters.size()); \
    for (T_ULONG i = 0; i < tBuffer.GetSize(); i++) { \
      tBuffer[i] = (T_BYTE)tCharacters.front(); \
      tCharacters.pop(); \
    } \
    pOutput->Write(&tBuffer); \
  }

void CLZ77Hash::Compress(::BASE::CArray<T_BYTE> * pInput, ::CPR::COutput * pOutput) {
  T_WORD uWORD = 0;
  T_BYTE uBYTE = 0;
  T_ULONG uPosition = 0;
  ::std::queue<T_CHAR> tCharacters;
  
  // write history size
  __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteWord(m_HistorySize);
  
  while (uPosition < pInput->GetSize()) {
  	T_BOOLEAN bMatch = false;
    T_ULONG uSize = 1;
    T_ULONG uShift = 0;

    // set history offset
    T_ULONG uHistoryOffset = uPosition; 
    if (uHistoryOffset > m_HistorySize) {
      uHistoryOffset = m_HistorySize;
    }

	  // set look offset
	  T_ULONG uLookOffset = pInput->GetSize() - uPosition;
	  if (uLookOffset > __CPR__COMPRESSOR__CLZ77HASH__LOOKSIZE) {
	    uLookOffset = __CPR__COMPRESSOR__CLZ77HASH__LOOKSIZE;
	  }


//    printf("/////////////////////////////////////////////////////\n");
//    printf("POSITION %d,%p, HISTORY OFFSET : %d, LOOK OFFSET : %d\n", uPosition, &(* pInput)[uPosition], uHistoryOffset, uLookOffset);
//    if (uHistoryOffset != 0) {
//      ::BASE::Dump(&(* pInput)[uPosition - uHistoryOffset], uHistoryOffset);
//    }
//    ::BASE::Dump(&(* pInput)[uPosition], uLookOffset);
//    printf("-----------------------------------------------------\n");

    T_BYTE * pMatchPosition = NULL;
    T_ULONG uMatchLength = 0;
    T_ULONG uMatchOffset = 0;
    T_ULONG uShiftOffset = 0;    

    // select the best match
    uSize = 8;
    while ((bMatch == false) && (uSize > 0)) {
      T_ULONG uLength = uLookOffset;    
      pMatchPosition = Match(&(* pInput)[uPosition], CheckSum(&(* pInput)[uPosition], uSize), &(* pInput)[uPosition], &uLength);

      if ((pMatchPosition != NULL) && (uLength >= 2) && (uLength >= uSize)) {
//        printf("IT IS MATCHED MATCH POSITION: %p, LENGTH: %d, SIZE: %d\n", pMatchPosition, uLength, uSize);
        uMatchOffset = &(* pInput)[uPosition] - pMatchPosition;
        uMatchLength = uLength;
          uShiftOffset = uMatchLength;
        bMatch = true;
      } else {
//        printf("IT ISN'T MATCHED SIZE: %d\n", uSize);
        uSize >>= 1;      
      }
    }
    
    if (bMatch == true) {
      // flush characters
      __CPR__COMPRESSOR__CLZ77HASH__Compress__FlushCharacters;

      // write token
      __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteTokenWord(uMatchLength - 1, uMatchOffset);

      // shift sliding window
       uShift = uShiftOffset;
    } else {
      // flush characters
      if (tCharacters.size() == 15) {
        __CPR__COMPRESSOR__CLZ77HASH__Compress__FlushCharacters;
      }

//      printf("UNCOMPRESSED CHAR\n");
//      ::BASE::Dump(&(* pInput)[uPosition], 1);

      // write character
      tCharacters.push((* pInput)[uPosition]);

      // shift sliding window
      uShift = 1;
    }

    for (T_ULONG i = 0; i < uShift; i++) {
//      printf("SHIFT SLIDING WINDOW %d -> %d\n", uPosition, uPosition + 1);
      
      // shift sliding window
      uPosition = uPosition + 1;
      
      // maintain positions
      if (uPosition < pInput->GetSize()) {
        uSize = 1;
        while (uSize < uLookOffset) {
          // insert 1, 2, 4, 8 size positions
          if (uSize <= uPosition) {
            Insert(CheckSum(&(* pInput)[uPosition - uSize], uSize), &(* pInput)[uPosition - uSize]);
          }
          uSize <<= 1;
        }
      }
    }
    
//    printf("NEXT\n\n");
  }

//  printf("FINISHED\n\n");
  // flush characters
  __CPR__COMPRESSOR__CLZ77HASH__Compress__FlushCharacters;

  // write EOF token
  __CPR__COMPRESSOR__CLZ77HASH__Compress__WriteTokenByte(0, 0);
//  printf("CLOSED\n\n");

} // Compress


/////////////////////////////////////////////////////////////////////////////

//! write character
#define __CPR__COMPRESSOR__CLZ77HASH__Expand__WriteCharacter(c) \
  { \
    tBuffer[0] = c; \
    pOutput->Write(&tBuffer); \
  }

void CLZ77Hash::Expand(::BASE::CArray<T_BYTE> * pInput, ::CPR::COutput * pOutput) {
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
          __CPR__COMPRESSOR__CLZ77HASH__Expand__WriteCharacter((* pInput)[uPosition + 1 + i]);
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
        __CPR__COMPRESSOR__CLZ77HASH__Expand__WriteCharacter(tHistory[(uPosition + i) % uBufferSize]);
      }
      uHistoryPosition = (uHistoryPosition + uLength) % uBufferSize;

      uPosition = uPosition + 2;
    }
  } while (bExit == false);
} // Expand

} // namespace COMPRESSOR

} // namespace CPR
