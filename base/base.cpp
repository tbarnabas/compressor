
/////////////////////////////////////////////////////////////////////////////
//
// base.cpp - module source
//
/////////////////////////////////////////////////////////////////////////////

#include "base.h"

namespace BASE {

T_ULONG GLOBAL_uCreated = 0;
T_ULONG GLOBAL_uInitialized = 0;

/////////////////////////////////////////////////////////////////////////////
void Create() {
  if (GLOBAL_uCreated == 0) {
  }
  GLOBAL_uCreated = GLOBAL_uCreated + 1;
} // Create


/////////////////////////////////////////////////////////////////////////////
void Initialize() {
  Create();
  if (GLOBAL_uInitialized == 0) {
  }
  GLOBAL_uInitialized = GLOBAL_uInitialized + 1;
} // Initialize


/////////////////////////////////////////////////////////////////////////////
void Shutdown(T_BOOLEAN bImmediate) {
  GLOBAL_uInitialized = GLOBAL_uInitialized - 1;
  if (GLOBAL_uInitialized == 0) {
  }
} // Shutdown


/////////////////////////////////////////////////////////////////////////////
void Destroy() {
  Shutdown(true);
  GLOBAL_uCreated = GLOBAL_uCreated - 1;
  if (GLOBAL_uCreated == 0) {
  }
} // Destroy


/////////////////////////////////////////////////////////////////////////////
#define __BASE__to_string__BUFFER_SIZE 32

T_STRING to_string(const T_TIME & tTime) {
  T_CHAR pBuffer[__BASE__to_string__BUFFER_SIZE];

#if (OS_FAMILY == OSF_WINDOWS)

  sprintf_s(pBuffer, __BASE__to_string__BUFFER_SIZE, "%.4d-%.2d-%.2d-%.2d:%.2d:%.2d", tTime.GetYear(), tTime.GetMonth(), tTime.GetDay(), tTime.GetHour(), tTime.GetMin(), tTime.GetSec());

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX) | (PA_FAMILY == PAF_AVR))

  snprintf(pBuffer, __BASE__to_string__BUFFER_SIZE, "%.4d-%.2d-%.2d-%.2d:%.2d:%.2d", tTime.GetYear(), tTime.GetMonth(), tTime.GetDay(), tTime.GetHour(), tTime.GetMin(), tTime.GetSec());

#else
#error unsupported platform
#endif

  return (T_STRING(pBuffer));
} // to_string


/////////////////////////////////////////////////////////////////////////////
T_TIME to_time(const T_STRING & sTime) {
  T_TIME tResult;

#if (PA_FAMILY == PAF_X86)

  struct tm _tm;

#if (OS_FAMILY == OSF_WINDOWS)

  sscanf_s(C_STR(sTime), "%d-%d-%d-%d:%d:%d", &_tm.tm_year, &_tm.tm_mon, &_tm.tm_mday, &_tm.tm_hour, &_tm.tm_min, &_tm.tm_sec);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  sscanf(C_STR(sTime), "%d-%d-%d-%d:%d:%d", &_tm.tm_year, &_tm.tm_mon, &_tm.tm_mday, &_tm.tm_hour, &_tm.tm_min, &_tm.tm_sec);

#else
#error unsupported platform
#endif

  _tm.tm_year = _tm.tm_year - 1900;
  _tm.tm_mon = _tm.tm_mon - 1;


  tResult = (T_ULONG)mktime(&_tm);

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

  return (tResult);
} // to_time


/////////////////////////////////////////////////////////////////////////////
T_BYTE getbyte(const T_BYTE * pAddress) {
  return ((T_BYTE)((((* (pAddress + 0)) << 0) & 0xff)));
} // getbyte


/////////////////////////////////////////////////////////////////////////////
void setbyte(T_BYTE * pAddress, T_BYTE value) {
  (* (pAddress + 0)) = (T_BYTE)((value & 0xff) >> 0);
} // setbyte

  
/////////////////////////////////////////////////////////////////////////////
T_WORD getword(const T_BYTE * pAddress, T_BOOLEAN bBigEndian) {
  T_WORD uResult = 0;

  if (bBigEndian == false) {
    uResult = (T_WORD)((((* (pAddress + 1)) << 8) & 0xff00) | (((* (pAddress + 0)) << 0) & 0xff));
  } else {
    uResult = (T_WORD)((((* (pAddress + 0)) << 8) & 0xff00) | (((* (pAddress + 1)) << 0) & 0xff));
  }

  return (uResult);
} // getword


/////////////////////////////////////////////////////////////////////////////
void setword(T_BYTE * pAddress, T_WORD value, T_BOOLEAN bBigEndian) {
  if (bBigEndian == false) {
    (* (pAddress + 1)) = (T_BYTE)((value & 0xff00) >> 8);
    (* (pAddress + 0)) = (T_BYTE)((value & 0xff) >> 0);
  } else {
    (* (pAddress + 0)) = (T_BYTE)((value & 0xff00) >> 8);
    (* (pAddress + 1)) = (T_BYTE)((value & 0xff) >> 0);
  }
} // setword


/////////////////////////////////////////////////////////////////////////////
T_DWORD getdword(const T_BYTE * pAddress, T_BOOLEAN bBigEndian) {
  T_DWORD uResult = 0;

  if (bBigEndian == false) {
    uResult = (T_DWORD)((((* (pAddress + 3)) << 24) & 0xff000000) | (((* (pAddress + 2)) << 16) & 0xff0000) | (((* (pAddress + 1)) << 8) & 0xff00) | (((* (pAddress + 0)) << 0) & 0xff));
  } else {
    uResult = (T_DWORD)((((* (pAddress + 0)) << 24) & 0xff000000) | (((* (pAddress + 1)) << 16) & 0xff0000) | (((* (pAddress + 2)) << 8) & 0xff00) | (((* (pAddress + 3)) << 0) & 0xff));
  }

  return (uResult);
} // getdword


/////////////////////////////////////////////////////////////////////////////
void setdword(T_BYTE * pAddress, T_DWORD value, T_BOOLEAN bBigEndian) {
  if (bBigEndian == false) {
    (* (pAddress + 3)) = (T_BYTE)((value & 0xff000000) >> 24);
    (* (pAddress + 2)) = (T_BYTE)((value & 0xff0000) >> 16);
    (* (pAddress + 1)) = (T_BYTE)((value & 0xff00) >> 8);
    (* (pAddress + 0)) = (T_BYTE)((value & 0xff) >> 0);
  } else {
    (* (pAddress + 0)) = (T_BYTE)((value & 0xff000000) >> 24);
    (* (pAddress + 1)) = (T_BYTE)((value & 0xff0000) >> 16);
    (* (pAddress + 2)) = (T_BYTE)((value & 0xff00) >> 8);
    (* (pAddress + 3)) = (T_BYTE)((value & 0xff) >> 0);
  }
} // setdword


#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

/////////////////////////////////////////////////////////////////////////////
T_QWORD getqword(const T_BYTE * pAddress, T_BOOLEAN bBigEndian) {
  T_QWORD uResult = 0;

  if (bBigEndian == false) {
    uResult = (T_QWORD)((((T_QWORD)(* (pAddress + 7)) << 56) & 0xff00000000000000) | (((T_QWORD)(* (pAddress + 6)) << 48) & 0xff000000000000) | (((T_QWORD)(* (pAddress + 5)) << 40) & 0xff0000000000) | (((T_QWORD)(* (pAddress + 4)) << 32) & 0xff00000000) | (((* (pAddress + 3)) << 24) & 0xff000000) | (((* (pAddress + 2)) << 16) & 0xff0000) | (((* (pAddress + 1)) << 8) & 0xff00) | (((* (pAddress + 0)) << 0) & 0xff));
  } else {
    uResult = (T_QWORD)((((T_QWORD)(* (pAddress + 0)) << 56) & 0xff00000000000000) | (((T_QWORD)(* (pAddress + 1)) << 48) & 0xff000000000000) | (((T_QWORD)(* (pAddress + 2)) << 40) & 0xff0000000000) | (((T_QWORD)(* (pAddress + 3)) << 32) & 0xff00000000) | (((* (pAddress + 4)) << 24) & 0xff000000) | (((* (pAddress + 5)) << 16) & 0xff0000) | (((* (pAddress + 6)) << 8) & 0xff00) | (((* (pAddress + 7)) << 0) & 0xff));
  }

  return (uResult);
} // getqword


/////////////////////////////////////////////////////////////////////////////
void setqword(T_BYTE * pAddress, T_QWORD value, T_BOOLEAN bBigEndian) {
  if (bBigEndian == false) {
    (* (pAddress + 7)) = (T_BYTE)((value & 0xff00000000000000) >> 56);
    (* (pAddress + 6)) = (T_BYTE)((value & 0xff000000000000) >> 48);
    (* (pAddress + 5)) = (T_BYTE)((value & 0xff0000000000) >> 40);
    (* (pAddress + 4)) = (T_BYTE)((value & 0xff00000000) >> 32);
    (* (pAddress + 3)) = (T_BYTE)((value & 0xff000000) >> 24);
    (* (pAddress + 2)) = (T_BYTE)((value & 0xff0000) >> 16);
    (* (pAddress + 1)) = (T_BYTE)((value & 0xff00) >> 8);
    (* (pAddress + 0)) = (T_BYTE)((value & 0xff) >> 0);
  } else {
    (* (pAddress + 0)) = (T_BYTE)((value & 0xff00000000000000) >> 56);
    (* (pAddress + 1)) = (T_BYTE)((value & 0xff000000000000) >> 48);
    (* (pAddress + 2)) = (T_BYTE)((value & 0xff0000000000) >> 40);
    (* (pAddress + 3)) = (T_BYTE)((value & 0xff00000000) >> 32);
    (* (pAddress + 4)) = (T_BYTE)((value & 0xff000000) >> 24);
    (* (pAddress + 5)) = (T_BYTE)((value & 0xff0000) >> 16);
    (* (pAddress + 6)) = (T_BYTE)((value & 0xff00) >> 8);
    (* (pAddress + 7)) = (T_BYTE)((value & 0xff) >> 0);
  }
} // setqword

#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))


/////////////////////////////////////////////////////////////////////////////
#define __BASE__Dump_BUFFER_SIZE 16

void Dump(const T_BYTE * pAddress, T_ULONG uLength, T_BOOLEAN bHex, T_ULONG uBytesPerLine) {
  if (bHex == true) {
    T_CHAR pBuffer[__BASE__Dump_BUFFER_SIZE];
    T_ULONG i = 0;
    T_STRING sHex;
    T_STRING sChar;

    // dump memory
    for (i = 0; i < uLength; i++)  {
      if ((i % uBytesPerLine) == 0) {
        if (sHex.GetLength() > 0) {
          {
            T_CHAR pBuffer[4096];

#if (OS_FAMILY == OSF_WINDOWS)

            sprintf_s(pBuffer, 4096, "%s %s\n", C_STR(sHex), C_STR(sChar));

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX) | (PA_FAMILY == PAF_AVR))

            snprintf(pBuffer, 4096, "%s %s\n", C_STR(sHex), C_STR(sChar));

#else
#error unsupported platform
#endif

            printf(pBuffer);
          }
          sHex = "";
          sChar = "";
        }
      }

#if (OS_FAMILY == OSF_WINDOWS)

      sprintf_s(pBuffer, __BASE__Dump_BUFFER_SIZE, "%.2X ", (* (pAddress + i)));

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX) | (PA_FAMILY == PAF_AVR))

      snprintf(pBuffer, __BASE__Dump_BUFFER_SIZE, "%.2X ", (* (pAddress + i)));

#else
#error unsupported platform
#endif

      sHex = sHex + pBuffer;
      if ((* (pAddress + i)) > 32) {
        sChar = sChar + (T_CHAR)(* (pAddress + i));
      } else {
        sChar = sChar + ".";
      }
    }
    for (i = sChar.GetLength(); i < uBytesPerLine; i++) {
      sHex = sHex + "   ";
    }
    {
     T_CHAR pBuffer[4096];

#if (OS_FAMILY == OSF_WINDOWS)

      sprintf_s(pBuffer, 4096, "%s %s\n", C_STR(sHex), C_STR(sChar));

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX) | (PA_FAMILY == PAF_AVR))

      snprintf(pBuffer, 4096, "%s %s\n", C_STR(sHex), C_STR(sChar));

#else
#error unsupported platform
#endif

      printf(pBuffer);
    }
  } else {
    T_ULONG i = 0;
    T_CHAR pBuffer[32];

    for (i = 0; i < uLength; i++)  {

#if (OS_FAMILY == OSF_WINDOWS)

      sprintf_s(pBuffer, 32, "%c", (T_CHAR)pAddress[i]);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX) | (PA_FAMILY == PAF_AVR))

      snprintf(pBuffer, 32, "%c", (T_CHAR)pAddress[i]);

#else
#error unsupported platform
#endif

      printf(pBuffer);
    }
    printf("\n");
  }
} // Dump


/////////////////////////////////////////////////////////////////////////////
void Dump(const ::BASE::CArray<T_BYTE> * pArray, T_BOOLEAN bHex, T_ULONG uBytesPerLine) {
  if (pArray != NULL) {
    Dump(pArray->GetElements(), pArray->GetSize(), bHex, uBytesPerLine);
  }
} // Dump

} // namespace BASE
