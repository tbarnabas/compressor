
/////////////////////////////////////////////////////////////////////////////
//
// cpr.h - module header
// --------------------------------------------------------------------------
//
// COMPRESSOR
//
// MODULE
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _CPR
#define _CPR

#include "cpr_configuration.h"

#include "cpr_cfile.h"
#include "cpr_cinput.h"
#include "cpr_coutput.h"

#include "cpr_compressor_ccompressor.h"
#include "cpr_compressor_chuffman.h"
#include "cpr_compressor_clz77hash.h"
#include "cpr_compressor_clz77linear.h"

namespace CPR {

//! create module
void Create();
//! initialize module
void Initialize();

//! shutdown module
void Shutdown(T_BOOLEAN bImmediate = false);
//! destroy module
void Destroy();

} // namespace CPR

#endif // ifndef _CPR
