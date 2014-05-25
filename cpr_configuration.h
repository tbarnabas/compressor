
/////////////////////////////////////////////////////////////////////////////
//
// cpr_configuration.h - configuration header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
// CONFIGURATION
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR_CONFIGURATION
#define _CPR_CONFIGURATION

#include "cpr_include.h"
#include "cpr_macro.h"

namespace CPR {

//! enumeration for different operations
enum operations {
  COMPRESS,
  EXPAND,
  HELP };

//! enumeration for different types
enum types {
  HUFFMAN = 13,
  LZ77_1 = 17,
  LZ77_2 = 19,
  LZ77_3 = 20,
  LZ77_4 = 21 };

}


/////////////////////////////////////////////////////////////////////////////
// DLL export/import

#define CPR_EXPORT_IMPORT

#if (OS_FAMILY == OSF_WINDOWS)

#if (!defined(CPR_STATIC) && !defined(CPR_EXPORT) && !defined(CPR_IMPORT))
#define CPR_STATIC
#endif // #if (!defined(CPR_STATIC) && !defined(CPR_EXPORT) && !defined(CPR_IMPORT))

#ifdef CPR_STATIC
#undef CPR_EXPORT_IMPORT
#define CPR_EXPORT_IMPORT
#define CPR_EXPORT_IMPORT_TEMPLATE
#endif // #ifdef CPR_STATIC

#ifdef CPR_EXPORT
#undef CPR_EXPORT_IMPORT
#define CPR_EXPORT_IMPORT __declspec(dllexport)
#define CPR_EXPORT_IMPORT_TEMPLATE
#endif // #ifdef CPR_EXPORT

#ifdef CPR_IMPORT
#undef CPR_EXPORT_IMPORT
#define CPR_EXPORT_IMPORT __declspec(dllimport)
#define CPR_EXPORT_IMPORT_TEMPLATE extern
#endif // #ifdef CPR_IMPORT

#endif // #if (OS_FAMILY == OSF_WINDOWS)

#endif // #ifndef _CPR_CONFIGURATION
