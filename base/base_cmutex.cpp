
/////////////////////////////////////////////////////////////////////////////
//
// base_cmutex.cpp - ::BASE::CMutex class source
//
/////////////////////////////////////////////////////////////////////////////

#include "base_cmutex.h"

#if ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

extern "C" {
extern int pthread_mutexattr_settype(pthread_mutexattr_t *, int);
}

#endif // #if ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
void CMutex::__construct() {

#if (OS_FAMILY == OSF_WINDOWS)

  // initialize critical section
  InitializeCriticalSection(&m_tCriticalSection);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  // initialize mutex attribute
  pthread_mutexattr_init(&m_tAttribute);

  // set mutex type
  pthread_mutexattr_settype(&m_tAttribute, PTHREAD_MUTEX_TIMED_NP);

  // initialize mutex
  pthread_mutex_init(&m_tMutex, &m_tAttribute);

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

} // __construct


/////////////////////////////////////////////////////////////////////////////
void CMutex::__destruct() {

#if (OS_FAMILY == OSF_WINDOWS)

  // delete critical section
  DeleteCriticalSection(&m_tCriticalSection);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  // destroy mutex
  pthread_mutex_destroy(&m_tMutex);

  // destroy mutex attribute
  pthread_mutexattr_destroy(&m_tAttribute);

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

} // __destruct


/////////////////////////////////////////////////////////////////////////////
CMutex::CMutex() {
  __construct();
} // CMutex


/////////////////////////////////////////////////////////////////////////////
CMutex::~CMutex() {
  __destruct();
} // ~CMutex


/////////////////////////////////////////////////////////////////////////////
CMutex::CMutex(const CMutex & tMutex) {
  __construct();
} // CMutex


/////////////////////////////////////////////////////////////////////////////
CMutex & CMutex::operator=(const CMutex & tMutex) {
  __destruct();
  __construct();
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////
void CMutex::Acquire() {
    
#if (OS_FAMILY == OSF_WINDOWS)
    
  // enter critical section
  EnterCriticalSection(&m_tCriticalSection);
    
#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))
    
  // lock mutex variable
  pthread_mutex_lock(&m_tMutex);
    
#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

} // Acquire


/////////////////////////////////////////////////////////////////////////////
void CMutex::Release() {

#if (OS_FAMILY == OSF_WINDOWS)

  // leave critical section
  LeaveCriticalSection(&m_tCriticalSection);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  // unlock mutex variable
  pthread_mutex_unlock(&m_tMutex);

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

} // Release

} // namespace BASE
