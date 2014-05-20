
/////////////////////////////////////////////////////////////////////////////
//
// cpr.cpp - module source
//
/////////////////////////////////////////////////////////////////////////////

#include "cpr.h"

namespace CPR {

T_BOOLEAN GLOBAL_bCreated = false;
T_BOOLEAN GLOBAL_bInitialized = false;

/////////////////////////////////////////////////////////////////////////////
void Create() {
  if (GLOBAL_bCreated == false) {
    ::BASE::Create();
    GLOBAL_bCreated = true;
  }
} // Create


/////////////////////////////////////////////////////////////////////////////
void Initialize() {
  Create();
  if (GLOBAL_bInitialized == false)  {
    ::BASE::Initialize();
    GLOBAL_bInitialized = true;
  }
} // Initialize


/////////////////////////////////////////////////////////////////////////////
void Shutdown(T_BOOLEAN bImmediate) {
  if (GLOBAL_bInitialized == true)  {
    ::BASE::Shutdown(bImmediate);
    GLOBAL_bInitialized = false;
  }
} // Shutdown


/////////////////////////////////////////////////////////////////////////////
void Destroy() {
  Shutdown(true);
  if (GLOBAL_bCreated == true)  {
    ::BASE::Destroy();
    GLOBAL_bCreated = false;
  }
} // Destroy

} // namespace CPR
