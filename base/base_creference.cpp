
/////////////////////////////////////////////////////////////////////////////
//
// base_creference.cpp - ::BASE::CReference<T> class source
//
/////////////////////////////////////////////////////////////////////////////

#include "base_creference.h"

namespace BASE {

::BASE::CMutex * GLOBAL_CReference__pMutex = NULL;

/////////////////////////////////////////////////////////////////////////////
void STATIC_CReference__Create() {
  if (GLOBAL_CReference__pMutex == NULL) {
    GLOBAL_CReference__pMutex = new ::BASE::CMutex();
  }
} // STATIC_CReference__Create


/////////////////////////////////////////////////////////////////////////////
void STATIC_CReference__Destroy() {
  if (GLOBAL_CReference__pMutex != NULL) {
    delete GLOBAL_CReference__pMutex;
    GLOBAL_CReference__pMutex = NULL;
  }
} // STATIC_CReference__Destroy
           
} // namespace BASE
