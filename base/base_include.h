
/////////////////////////////////////////////////////////////////////////////
//
// base_include.h - include header
// --------------------------------------------------------------------------
//
// BASE
//
// INCLUDE
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_INCLUDE
#define _BASE_INCLUDE

#include "base_platform.h"

#if (OS_FAMILY == OSF_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#if (_WIN32_WINNT < 0x0500)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500 
#endif #if (_WIN32_WINNT < 0x0500)

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <windows.h>

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/timeb.h>

#elif (PA_FAMILY == PAF_AVR)

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#else
#error unsupported platform
#endif

#endif // #ifndef _BASE_INCLUDE

