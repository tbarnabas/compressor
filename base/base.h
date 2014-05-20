
/////////////////////////////////////////////////////////////////////////////
//
// base.h - module header
// --------------------------------------------------------------------------
//
// BASE
//
// MODULE
//
/////////////////////////////////////////////////////////////////////////////

// PLATFORM DEPENDENT

#pragma once
#ifndef _BASE
#define _BASE

#include "base_configuration.h"

#include "base_carray.h"
#include "base_cinterval.h"
#include "base_cmessage.h"
#include "base_cobject.h"
#include "base_creference.h"
#include "base_cstring.h"
#include "base_ctime.h"
#include "base_eexception.h"

namespace BASE {

//! create module
void Create();
//! initialize module
void Initialize();
//! shutdown module
void Shutdown(T_BOOLEAN bImmediate = false);
//! destroy module
void Destroy();

//! convert time to string
T_STRING to_string(const T_TIME & tTime);
//! convert string to time
T_TIME to_time(const T_STRING & sTime);

//! get byte from the specified address
T_BYTE getbyte(const T_BYTE * pAddress);
//! set byte into the specified address
void setbyte(T_BYTE * pAddress, T_BYTE value);
  
//! get word (2 byte) from the specified address
T_WORD getword(const T_BYTE * pAddress, T_BOOLEAN bBigEndian = false);
//! set word (2 byte) into the specified address
void setword(T_BYTE * pAddress, T_WORD value, T_BOOLEAN bBigEndian = false);

//! get dword (4 byte) from the specified address
T_DWORD getdword(const T_BYTE * pAddress, T_BOOLEAN bBigEndian = false);
//! set dword (4 byte) into the specified address
void setdword(T_BYTE * pAddress, T_DWORD value, T_BOOLEAN bBigEndian = false);

#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

//! get qword (8 byte) from the specified address
T_QWORD getqword(const T_BYTE * pAddress, T_BOOLEAN bBigEndian = false);
//! set qword (8 byte) into the specified address
void setqword(T_BYTE * pAddress, T_QWORD value, T_BOOLEAN bBigEndian = false);

#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define __BASE__Dump_BYTES_PER_LINE 16

//! dump memory space
void Dump(const T_BYTE * pAddress, T_ULONG uLength, T_BOOLEAN bHex = true, T_ULONG uBytesPerLine = __BASE__Dump_BYTES_PER_LINE);
//! dump memory space
void Dump(const ::BASE::CArray<T_BYTE> * pArray, T_BOOLEAN bHex = true, T_ULONG uBytesPerLine = __BASE__Dump_BYTES_PER_LINE);

} // namespace BASE

#endif // #ifndef _BASE
