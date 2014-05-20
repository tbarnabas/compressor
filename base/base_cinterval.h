
/////////////////////////////////////////////////////////////////////////////
//
// base_cinterval.h - ::BASE::CInterval<T> class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_CINTERVAL
#define _BASE_CINTERVAL

#include "base_configuration.h"

namespace BASE {

template <class T>
class CInterval {
public:
  MEMBER_GET_SET(T, Begin);
  MEMBER_GET_SET(T, End);

public:
  //! constructor
  CInterval(const T & tBegin = T(), const T & tEnd = T());
  //! destructor
  virtual ~CInterval();

  //! copy constructor
  CInterval(const CInterval<T> & tInterval);
  //! assignment operator
  CInterval<T> & operator=(const CInterval<T> & tInterval);

  //! if time is valid then return true
  T_BOOLEAN IsValid() const;
}; // class CInterval

} // namespace BASE


/////////////////////////////////////////////////////////////////////////////
//
// ::BASE::CInterval<T> class source
//
/////////////////////////////////////////////////////////////////////////////

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
template <class T>
CInterval<T>::CInterval(const T & tBegin, const T & tEnd) :
  m_Begin(tBegin), 
  m_End(tEnd) {
} // CInterval


/////////////////////////////////////////////////////////////////////////////
template <class T>
CInterval<T>::~CInterval() {
} // ~CInterval


/////////////////////////////////////////////////////////////////////////////
template <class T>
CInterval<T>::CInterval(const CInterval<T> & tInterval) : 
  m_Begin(tInterval.m_Begin), 
  m_End(tInterval.m_End) {
} // CInterval


/////////////////////////////////////////////////////////////////////////////
template <class T>
CInterval<T> & CInterval<T>::operator=(const CInterval<T> & tInterval) {
  m_Begin = tInterval.m_Begin;
  m_End = tInterval.m_End;
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////
template <class T>
inline T_BOOLEAN CInterval<T>::IsValid() const {
  return (m_Begin != m_End);
} // IsValid

} // namespace BASE

#endif // #ifndef _BASE_CINTERVAL
