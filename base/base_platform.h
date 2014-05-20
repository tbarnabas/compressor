
/////////////////////////////////////////////////////////////////////////////
//
// base_platform.h - platform header
// --------------------------------------------------------------------------
//
// BASE
//
// PLATFORM
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_PLATFORM
#define _BASE_PLATFORM

#define __NOT_DEFINED               (0x00000000)

/////////////////////////////////////////////////////////////////////////////
// processor architecture

#ifndef PROCESSOR_ARCHITECTURE
#error PROCESSOR_ARCHITECTURE macro must be specified
//#define PROCESSOR_ARCHITECTURE PAF_X86
#endif // #ifndef PROCESSOR_ARCHITECTURE

// processor architecture family    (0x00------)
#define PAF_X86                     (0x01000000)
#define PAF_AVR                     (0x02000000)

#define PA_FAMILY ((PROCESSOR_ARCHITECTURE) & 0xff000000)

// processor architecture type      (0x--00----)
#define PAT_X86_I386                (0x00010000 | PAF_X86)
#define PAT_X86_I486                (0x00020000 | PAF_X86)
#define PAT_X86_PENTIUM             (0x00030000 | PAF_X86)
#define PAT_AVR_ATMEGA              (0x00040000 | PAF_AVR)

#define PA_TYPE ((PROCESSOR_ARCHITECTURE) & 0xffff0000)

// processor architecture version   (0x----00--)
#define PAV_AVR_ATMEGA_328P         (0x00000100 | PAT_AVR_ATMEGA)

#define PA_VERSION ((PROCESSOR_ARCHITECTURE) & 0xffffff00)


/////////////////////////////////////////////////////////////////////////////
// operating system

#ifndef OPERATING_SYSTEM
//#error OPERATING_SYSTEM macro must be specified
#define OPERATING_SYSTEM __NOT_DEFINED
#endif // #ifndef OPERATING_SYSTEM

// operating system family          (0x00------)
#define OSF_LINUX                   (0x01000000)
#define OSF_UNIX                    (0x02000000)
#define OSF_WINDOWS                 (0x03000000)

#define OS_FAMILY ((OPERATING_SYSTEM) & 0xff000000)

// operating system type            (0x--00---- )
#define OST_LINUX_DEBIAN            (0x00010000 | OSF_LINUX)
#define OST_LINUX_REDHAT            (0x00020000 | OSF_LINUX)
#define OST_LINUX_FEDORA            (0x00030000 | OSF_LINUX)
#define OST_WINDOWS_31              (0x00010000 | OSF_WINDOWS)
#define OST_WINDOWS_95              (0x00020000 | OSF_WINDOWS)
#define OST_WINDOWS_98              (0x00030000 | OSF_WINDOWS)
#define OST_WINDOWS_ME              (0x00040000 | OSF_WINDOWS)
#define OST_WINDOWS_NT              (0x00050000 | OSF_WINDOWS)
#define OST_WINDOWS_2000            (0x00060000 | OSF_WINDOWS)
#define OST_WINDOWS_XP              (0x00070000 | OSF_WINDOWS)
#define OST_WINDOWS_2003_SERVER     (0x00080000 | OSF_WINDOWS)
#define OST_WINDOWS_VISTA           (0x00090000 | OSF_WINDOWS)
#define OST_WINDOWS_7               (0x000a0000 | OSF_WINDOWS)
#define OST_WINDOWS_8               (0x000b0000 | OSF_WINDOWS)

#define OS_TYPE ((OPERATING_SYSTEM) & 0xffff0000)

// operating system version         (0x----00--)
#define OSV_WINDOWS_95_OSR2         (0x00000100 | OST_WINDOWS_95)
#define OSV_WINDOWS_98_SE           (0x00000100 | OST_WINDOWS_98)
#define OSV_WINDOWS_NT_351_WKS      (0x00000100 | OST_WINDOWS_NT)
#define OSV_WINDOWS_NT_351_SRV      (0x00000200 | OST_WINDOWS_NT)
#define OSV_WINDOWS_NT_4_WKS        (0x00000300 | OST_WINDOWS_NT)
#define OSV_WINDOWS_NT_4_SRV        (0x00000400 | OST_WINDOWS_NT)

#define OS_VERSION ((OPERATING_SYSTEM) & 0xffffff00)


/////////////////////////////////////////////////////////////////////////////
// development environment

#ifndef DEVELOPMENT_ENVIRONMENT
//#error DEVELOPMENT_ENVIRONMENT macro must be specified
#define DEVELOPMENT_ENVIRONMENT __NOT_DEFINED
#endif // #ifndef DEVELOPMENT_ENVIRONMENT

// development environment family   (0x00------)
#define DEF_MSVC                    (0x01000000)
#define DEF_ARDUINO                 (0x02000000)

#define DE_FAMILY ((DEVELOPMENT_ENVIRONMENT) & 0xff000000)

// development environment version  (0x----00--)
#define DEV_MSVC_6                  (0x00000100 | DEF_MSVC)
#define DEV_MSVC_NET_2005           (0x00000200 | DEF_MSVC)
#define DEV_ARDUINO_022             (0x00000100 | DEF_ARDUINO)

#define DE_VERSION ((DEVELOPMENT_ENVIRONMENT) & 0xff00ff00)


/////////////////////////////////////////////////////////////////////////////
// platform dependent types and aliases

#if (OS_FAMILY == OSF_WINDOWS)

typedef bool __T_BOOLEAN;

typedef __int8 __T_INT8;
typedef unsigned __int8 __T_UINT8;
typedef __int16 __T_INT16;
typedef unsigned __int16 __T_UINT16;
typedef __int32 __T_INT32;
typedef unsigned __int32 __T_UINT32;
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
typedef __int64 __T_INT64;
typedef unsigned __int64 __T_UINT64;
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

typedef float __T_FLOAT;
typedef double __T_DOUBLE;
typedef long double __T_LONGDOUBLE;

#elif (OS_FAMILY == OSF_LINUX)

#include "bits/types.h"

typedef bool __T_BOOLEAN;

typedef __int8_t __T_INT8;
typedef __uint8_t __T_UINT8;
typedef __int16_t __T_INT16;
typedef __uint16_t __T_UINT16;
typedef __int32_t __T_INT32;
typedef __uint32_t __T_UINT32;
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
typedef __int64_t __T_INT64;
typedef __uint64_t __T_UINT64;
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

typedef float __T_FLOAT;
typedef double __T_DOUBLE;
typedef long double __T_LONGDOUBLE;

#elif (PA_FAMILY == PAF_AVR)

#include "stdint.h"

typedef bool __T_BOOLEAN;

typedef int8_t __T_INT8;
typedef uint8_t __T_UINT8;
typedef int16_t __T_INT16;
typedef uint16_t __T_UINT16;
typedef int32_t __T_INT32;
typedef uint32_t __T_UINT32;
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
typedef int64_t __T_INT64;
typedef uint64_t __T_UINT64;
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

typedef float __T_FLOAT;
typedef double __T_DOUBLE;
typedef long double __T_LONGDOUBLE;

#define NULL 0x00000000

#else
#error unsupported platform
#endif

#define __T_BYTE __T_UINT8
#define __T_WORD __T_UINT16
#define __T_DWORD __T_UINT32
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
#define __T_QWORD __T_UINT64
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define __T_SHORT __T_INT16
#define __T_USHORT __T_UINT16
#define __T_INT __T_INT32
#define __T_UINT __T_UINT32
#define __T_LONG __T_INT32
#define __T_ULONG __T_UINT32
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
#define __T_LONGLONG __T_INT64
#define __T_ULONGLONG __T_UINT64
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define __T_CHAR char


/////////////////////////////////////////////////////////////////////////////
// platform independent types and alisases and additional types

#define T_BOOLEAN __T_BOOLEAN

#define T_INT8 __T_INT8
#define T_UINT8 __T_UINT8
#define T_INT16 __T_INT16
#define T_UINT16 __T_UINT16
#define T_INT32 __T_INT32
#define T_UINT32 __T_UINT32
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
#define T_INT64 __T_INT64
#define T_UINT64 __T_UINT64
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define T_FLOAT __T_FLOAT
#define T_DOUBLE __T_DOUBLE
#define T_LONGDOUBLE __T_LONGDOUBLE

#define T_CHAR __T_CHAR

#define T_BYTE __T_BYTE
#define T_WORD __T_WORD
#define T_DWORD __T_DWORD
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
#define T_QWORD __T_QWORD
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define T_SHORT __T_SHORT
#define T_USHORT __T_USHORT
#define T_INT __T_INT
#define T_UINT __T_UINT
#define T_LONG __T_LONG
#define T_ULONG __T_ULONG
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
#define T_LONGLONG __T_LONGLONG
#define T_ULONGLONG __T_ULONGLONG
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define LOW_BYTE(dword) ((BYTE)(dword & 0xff))
#define HIGH_BYTE(dword) ((BYTE)((dword & 0xff00) >> 8))
#define LOW_WORD(dword) ((WORD)(dword & 0xffff))
#define HIGH_WORD(dword) ((WORD)((dword & 0xffff0000) >> 16))
#if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))
#define LOW_DWORD(dword) ((DWORD)(dword & 0xffffffff))
#define HIGH_DWORD(dword) ((DWORD)((dword & 0xffffffff00000000) >> 32))
#endif // #if ((PA_FAMILY == PAF_IA64) | (PA_FAMILY == PAF_AMD64))

#define T_STRING ::BASE::CString
#define T_IPADDRESS ::BASE::CIPAddress
#define T_TIME ::BASE::CTime
#define T_INTERVAL ::BASE::CInterval

#endif // #ifndef _BASE_PLATFORM
