
/////////////////////////////////////////////////////////////////////////////
//
// base_carray.h - ::BASE::CArray<T, L> class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _BASE_CARRAY
#define _BASE_CARRAY

#include "base_configuration.h"

#include "base_cobject.h"

namespace BASE {

template <class T, class L = T_ULONG>
class CArray : public ::BASE::CObject {
public:
  //! copy memory area
  static void STATIC_Copy(const T * pSource, T * pDestination, L uSize);
  //! zero memory area
  static void STATIC_Zero(T * pDestination, L uSize);

private:
  //! pointer to elements
  T * m_pElements;
  //! size
  L m_uSize;

  //! construct
  void __construct(const T * pElements, L uSize);
  //! destruct
  void __destruct();

public:
  //! constructor
  CArray(const T * pElements = NULL, L uSize = 0);
  //! constructor
  CArray(L uSize);
  //! destructor
  virtual ~CArray();

  //! copy constructor
  CArray(const CArray<T, L> & tArray);
  //! assignment operator
  CArray<T, L> & operator=(const CArray<T, L> & tArray);

  //! equality operator
  T_BOOLEAN operator==(const CArray<T, L> & tArray) const;
  //! inequality operator
  T_BOOLEAN operator!=(const CArray<T, L> & tArray) const;
  //! array subscript operator
  T & operator[](L uIndex) const;
  // less than operator
  T_BOOLEAN operator<(const CArray<T, L> & tArray) const;

  //! if array is valid then return true
  T_BOOLEAN IsValid() const;

  //! get pointer to elements
  T * GetElements() const;
  //! get size
  L GetSize() const;
  //! set size
  void SetSize(L uSize, T_BOOLEAN bKeep = false);
  //! if element exists then return true

  T_BOOLEAN Exists(const T & tElement) const;

  //! append
  void Append(const T * pElements, L uSize);
}; // class CArray

} // namespace BASE


/////////////////////////////////////////////////////////////////////////////
//
// BASE::CArray<T, L> class source
//
/////////////////////////////////////////////////////////////////////////////

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
void CArray<T, L>::STATIC_Copy(const T * pSource, T * pDestination, L uSize) {
  while (uSize > 0) {
    uSize = uSize - 1;
    pDestination[uSize] = pSource[uSize];
  }
} // STATIC_Copy


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
void CArray<T, L>::STATIC_Zero(T * pDestination, L uSize) {
  while (uSize > 0) {
    uSize = uSize - 1;
    pDestination[uSize] = 0;
  }
} // STATIC_Zero


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
void CArray<T, L>::__construct(const T * pElements, L uSize) {
  m_pElements = NULL;
  m_uSize = uSize;

  if (uSize > 0) {
    m_pElements = new T[uSize];

    if (pElements != NULL) {
      
      while (uSize > 0) {
        uSize = uSize - 1;
        m_pElements[uSize] = pElements[uSize];
      }
    }
  }
} // __construct


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
void CArray<T, L>::__destruct() {
  if (m_pElements != NULL) {
    delete []m_pElements;

    m_pElements = NULL;
    m_uSize = 0;
  }
} // __destruct


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
CArray<T, L>::CArray(const T * pElements, L uSize) {
  __construct(pElements, uSize);
} // CArray


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
CArray<T, L>::CArray(L uSize) {
  __construct(NULL, uSize);
} // CArray


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
CArray<T, L>::~CArray() {
  __destruct();
} // ~CArray
            

/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
CArray<T, L>::CArray(const CArray<T, L> & tArray) :
  ::BASE::CObject(tArray) {
  __construct(tArray.m_pElements, tArray.m_uSize);
} // CArray


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
CArray<T, L> & CArray<T, L>::operator=(const CArray<T, L> & tArray) {
  __destruct();
  ::BASE::CObject::operator=(tArray);
  __construct(tArray.m_pElements, tArray.m_uSize);
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
T_BOOLEAN CArray<T, L>::operator==(const CArray<T, L> & tArray) const {
  T_BOOLEAN bResult = true;
  L i = 0;

  // compare elements
  if (m_uSize != tArray.m_uSize) {
    bResult = false;
  }
  i = 0;
  while ((bResult == true) && (i < m_uSize)) {
    if (m_pElements[i] == tArray.m_pElements[i]) {
      i = i + 1;
    } else {
      bResult = false;
    }
  }

  return (bResult);
} // operator==


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
T_BOOLEAN CArray<T, L>::operator!=(const CArray<T, L> & tArray) const {
  return (!((* this) == tArray));
} // operator!=


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
T & CArray<T, L>::operator[](L uIndex) const {
  return (m_pElements[uIndex]);
} // operator[]


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
T_BOOLEAN CArray<T, L>::IsValid() const {
  return (m_pElements != NULL);
} // IsValid


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
inline T * CArray<T, L>::GetElements() const {
  return (m_pElements);
} // GetElements


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
inline L CArray<T, L>::GetSize() const {
  return (m_uSize);
} // GetSize


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
void CArray<T, L>::SetSize(L uSize, T_BOOLEAN bKeep) {
  if (bKeep == true) {
    CArray<T, L> tArray(* this);

    __destruct();
    __construct(NULL, uSize);

    STATIC_Copy(tArray.m_pElements, m_pElements, tArray.GetSize());
  } else {
    __destruct();
    __construct(NULL, uSize);
  }
} // SetSize


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
T_BOOLEAN CArray<T, L>::Exists(const T & tElement) const {
  T_BOOLEAN bResult = false;

  L i = 0;
  while ((bResult == false) && (i < m_uSize)) {
    if (m_pElements[i] == tElement) {
      bResult = true;
    } else {
      i = i + 1;
    }

  }

  return (bResult);
} // Exists


/////////////////////////////////////////////////////////////////////////////
template <class T, class L>
void CArray<T, L>::Append(const T * pElements, L uSize) {
  SetSize(m_uSize + uSize, true);
  STATIC_Copy(pElements, m_pElements + m_uSize - uSize, uSize);
} // CArray

} // namespace BASE

#endif // #ifndef _BASE_CARRAY
