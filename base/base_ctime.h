
/////////////////////////////////////////////////////////////////////////////
//
// base_ctime.h - ::BASE::CTime class header
// --------------------------------------------------------------------------
//
// BASE
//
/////////////////////////////////////////////////////////////////////////////

// PLATFORM DEPENDENT
// note: not implemented on PAF_AVR platforms

#pragma once
#ifndef _BASE_CTIME
#define _BASE_CTIME

#include "base_configuration.h"

#include "base_cinterval.h"

namespace BASE {

#define T_TIME_TO_SEC(time) ((T_ULONG)(time.GetDelaySec() + (T_ULONG)(time.GetDelayUSec() / 1000000))) 
#define T_TIME_TO_MSEC(time) ((T_ULONG)((time.GetDelaySec() * 1000) + (T_ULONG)(time.GetDelayUSec() / 1000)))
#define T_TIME_TO_USEC(time) ((T_ULONG)((time.GetDelaySec() * 1000000) + time.GetDelayUSec()))

class BASE_EXPORT_IMPORT CTime {
public:
  //! enumeration for different times types
  enum times {
    YEAR,
    MONTH,
    WEEK,
    DAY,
    HOUR,
    MIN,
    SEC };

  //! get length of times
  static CTime STATIC_GetLengthOf(times base, T_ULONG uYear = 0, T_ULONG uMonth = 0);
  //! get part of times
  static CInterval<CTime> STATIC_GetPartOf(T_ULONG uCount, times part, times base, T_ULONG uYear = 0, T_ULONG uMonth = 0);
  //! get current time
  static CTime STATIC_GetCurrent();

private:
  //! convert to date
  void __convertToDate();
  //! convert to time
  void __convertToTime();
  //! normalize
  void __normalize();

public:
  MEMBER_GET(T_ULONG, Time);
  MEMBER_GET(T_ULONG, Year);
  MEMBER_GET(T_ULONG, Month);
  MEMBER_GET(T_ULONG, Day);
  MEMBER_GET(T_ULONG, Hour);
  MEMBER_GET(T_ULONG, Min);
  MEMBER_GET(T_ULONG, Sec);
  MEMBER_GET(T_ULONG, USec);

public:
  //! constructor
  CTime(T_ULONG uTime = 0);
  //! constructor
  CTime(T_ULONG uYear, T_ULONG uMonth, T_ULONG uDay, T_ULONG uHour, T_ULONG uMin, T_ULONG uSec);
  //! constructor
  CTime(T_ULONG uSec, T_ULONG uUSec);
  //! destructor
  virtual ~CTime();

  //! copy constructor
  CTime(const CTime & tTime);
  //! assignment operator
  CTime & operator=(const CTime & tTime);

  //! assignment operator
  T_ULONG operator=(T_ULONG uTime);
  //! comparison operator
  T_BOOLEAN operator<(const CTime & tTime) const;
  //! addition operator
  CTime operator+(const CTime & tTime) const;
  //! substraction operator
  CTime operator-(const CTime & tTime) const;
  //! multiplication operator
  CTime operator*(T_ULONG uNumber) const;

  //! type cast operator
  operator T_ULONG () const;

  //! if time is valid then return true
  T_BOOLEAN IsValid() const;

  //! set time
  void SetTime(T_ULONG uTime);
  //! set year
  void SetYear(T_ULONG uYear);
  //! set month
  void SetMonth(T_ULONG uMonth);
  //! get year day
  T_ULONG GetYearDay() const;
  //! get week day
  T_ULONG GetWeekDay() const;
  //! set day
  void SetDay(T_ULONG uDay);
  //! set hour
  void SetHour(T_ULONG uHour);
  //! set minute
  void SetMin(T_ULONG uMin);
  //! set second
  void SetSec(T_ULONG uSec);

  //! get delay second
  T_ULONG GetDelaySec() const;
  //! set delay second
  void SetDelaySec(T_ULONG uSec);
  //! get delay micro second
  T_ULONG GetDelayUSec() const;
  //! set delay micro second
  void SetDelayUSec(T_ULONG uUSec);

  //! trim
  void Trim(times base);

  //! get elapsed time
  CTime GetElapsed() const;
  //! if time is timed out then return true
  T_BOOLEAN IsTimedOut(const CTime & tTimeOut) const;
}; // class BASE_EXPORT_IMPORT CTime

} // namespace BASE


/////////////////////////////////////////////////////////////////////////////
//
// ::BASE::CTime class source
//
/////////////////////////////////////////////////////////////////////////////

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetTime(T_ULONG uTime) {
  m_Time = uTime;
  __convertToDate();
} // SetTime


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetYear(T_ULONG uYear) {
  m_Year = uYear;
  __convertToTime();
} // SetYear


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetMonth(T_ULONG uMonth) {
  m_Month = uMonth;
  __convertToTime();
} // SetMonth


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetDay(T_ULONG uDay) {
  m_Day = uDay;
  __convertToTime();
} // SetDay


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetHour(T_ULONG uHour) {
  m_Hour = uHour;
  __convertToTime();
} // SetHour


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetMin(T_ULONG uMin) {
  m_Min = uMin;
  __convertToTime();
} // SetMin


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetSec(T_ULONG uSec) {
  m_Sec = uSec;
  __convertToTime();
} // SetSec


/////////////////////////////////////////////////////////////////////////////
inline T_ULONG CTime::GetDelaySec() const {
  return (m_Time);
} // GetDelaySec


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetDelaySec(T_ULONG uSec) {
  SetTime(uSec);
} // SetSec


/////////////////////////////////////////////////////////////////////////////
inline T_ULONG CTime::GetDelayUSec() const {
  return (m_USec);
} // GetDelayUSec


/////////////////////////////////////////////////////////////////////////////
inline void CTime::SetDelayUSec(T_ULONG uUSec) {
  m_USec = uUSec;
  __normalize();
  __convertToDate();
} // SetUSec

} // namespace BASE

#endif // #ifndef _BASE_CTIME
