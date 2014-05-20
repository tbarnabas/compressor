
/////////////////////////////////////////////////////////////////////////////
//
// base_configuration.h - configuration header
// --------------------------------------------------------------------------
//
// BASE
//
// CONFIGURATION
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_CONFIGURATION
#define _BASE_CONFIGURATION

#include "base_include.h"
#include "base_macro.h"

/////////////////////////////////////////////////////////////////////////////
// export/import

#define BASE_EXPORT_IMPORT

#if (OS_FAMILY == OSF_WINDOWS)

#pragma warning (disable:4793)

#if (!defined(BASE_STATIC) && !defined(BASE_EXPORT) && !defined(BASE_IMPORT))
#define BASE_STATIC
#endif // #if (!defined(BASE_STATIC) && !defined(BASE_EXPORT) && !defined(BASE_IMPORT))

#ifdef BASE_STATIC
#undef BASE_EXPORT_IMPORT
#define BASE_EXPORT_IMPORT
#define BASE_EXPORT_IMPORT_TEMPLATE
#endif // #ifdef BASE_STATIC

#ifdef BASE_EXPORT
#undef BASE_EXPORT_IMPORT
#define BASE_EXPORT_IMPORT __declspec(dllexport)
#define BASE_EXPORT_IMPORT_TEMPLATE
#endif // #ifdef BASE_EXPORT

#ifdef BASE_IMPORT
#undef BASE_EXPORT_IMPORT
#define BASE_EXPORT_IMPORT __declspec(dllimport)
#define BASE_EXPORT_IMPORT_TEMPLATE extern
#endif // #ifdef BASE_IMPORT

#endif // #if (OS_FAMILY == OSF_WINDOWS)

#endif // #ifndef _BASE_CONFIGURATION
