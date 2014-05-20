
/////////////////////////////////////////////////////////////////////////////
//
// base_ctime.cpp - ::BASE::CTime class source
//
/////////////////////////////////////////////////////////////////////////////

#include "base_ctime.h"

namespace BASE {

/////////////////////////////////////////////////////////////////////////////
CTime CTime::STATIC_GetLengthOf(times base, T_ULONG uYear, T_ULONG uMonth) {
  CTime tResult;

  switch (base) {
  case YEAR : {
      if ((((uYear % 4) == 0) && ((uYear % 100) != 0)) || (((uYear % 4) == 0) && ((uYear % 400) == 0))) {
        tResult = CTime(366 * T_TIME_TO_SEC(STATIC_GetLengthOf(DAY)));
      } else {
        tResult = CTime(365 * T_TIME_TO_SEC(STATIC_GetLengthOf(DAY)));
      }
    break;
  }
  case MONTH : {
    switch (uMonth) {
    case 1 :
    case 3 :
    case 5 :
    case 7 :
    case 8 :
    case 10 :
    case 12 : {
      tResult = CTime(31 * T_TIME_TO_SEC(STATIC_GetLengthOf(DAY)));
      break;
    }
    case 4 :
    case 6 :
    case 9 :
    case 11 : {
      tResult = CTime(30 * T_TIME_TO_SEC(STATIC_GetLengthOf(DAY)));
      break;
    }
    case 2 : {
      if ((((uYear % 4) == 0) && ((uYear % 100) != 0)) || (((uYear % 4) == 0) && ((uYear % 400) == 0))) {
        tResult = CTime(29 * T_TIME_TO_SEC(STATIC_GetLengthOf(DAY)));
      } else {
        tResult = CTime(28 * T_TIME_TO_SEC(STATIC_GetLengthOf(DAY)));
      }
      break;
    }
    }
    break;
  }
  case WEEK : {
    tResult = CTime(604800, 0);
    break;
  }
  case DAY : {
    tResult = CTime(86400, 0);
    break;
  }
  case HOUR : {
    tResult = CTime(3600, 0);
    break;
  }
  case MIN : {
    tResult = CTime(60, 0);
    break;
  }
  case SEC : {
    tResult = CTime(1, 0);
    break;
  }
  }

  return (tResult);
} // STATIC_GetLengthOf 


/////////////////////////////////////////////////////////////////////////////
CInterval<CTime> CTime::STATIC_GetPartOf(T_ULONG uCount, times part, times base, T_ULONG uYear, T_ULONG uMonth) {
  CInterval<CTime> tResult;

  T_ULONG uPartLength = T_TIME_TO_SEC(STATIC_GetLengthOf(part, uYear, uMonth));
  T_ULONG uBaseLength = T_TIME_TO_SEC(STATIC_GetLengthOf(base, uYear, uMonth));

  if ((uPartLength * uCount) <= uBaseLength) {
    tResult.SetBegin(CTime(uPartLength * (uCount - 1)));
    tResult.SetEnd(CTime(uPartLength * uCount));
  }

  return (tResult);
} // STATIC_GetPartOf


/////////////////////////////////////////////////////////////////////////////
CTime CTime::STATIC_GetCurrent() {
  CTime tResult;

#if (PA_FAMILY == PAF_X86)

#if (OS_FAMILY == OSF_WINDOWS)

  struct _timeb t;

  // get current time
  _ftime64_s(&t);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  struct timeb t;

  // get current time
  ftime(&t);

#else
#error unsupported platform
#endif

  // set result
  tResult.SetDelaySec((T_ULONG)t.time);
  tResult.SetDelayUSec(t.millitm * 1000);

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif
  
  return (tResult);
} // STATIC_GetCurrent


/////////////////////////////////////////////////////////////////////////////
void CTime::__convertToDate() {

#if (PA_FAMILY == PAF_X86)

  if (m_Time == 0) {
    m_Year = 0;
    m_Month = 0;
    m_Day = 0;
    m_Hour = 0;
    m_Min = 0;
    m_Sec = 0;
  } else {
    struct tm _tm;
    time_t t = m_Time;

    // convert time
    memset(&_tm, -1, sizeof(_tm));

#if (OS_FAMILY == OSF_WINDOWS)

    localtime_s(&_tm, &t);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

    localtime_r(&t, &_tm);

#else
#error unsupported platform
#endif

    m_Year = (T_ULONG)_tm.tm_year + 1900;
    m_Month = (T_ULONG)_tm.tm_mon + 1;
    m_Day = (T_ULONG)_tm.tm_mday;
    m_Hour = (T_ULONG)_tm.tm_hour;
    m_Min = (T_ULONG)_tm.tm_min; 
    m_Sec = (T_ULONG)_tm.tm_sec;
  }

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

} // __convertToDate


/////////////////////////////////////////////////////////////////////////////
void CTime::__convertToTime() {

#if (PA_FAMILY == PAF_X86)

  if ((m_Year == 0) && (m_Month == 0) && (m_Day == 0) && (m_Hour == 0) && (m_Min == 0) && (m_Sec == 0)) {
    m_Time = 0;
  } else {
    struct tm _tm;

    // convert time
    _tm.tm_year = m_Year - 1900;
    _tm.tm_mon = m_Month - 1;
    _tm.tm_yday = 0;
    _tm.tm_mday = m_Day;
    _tm.tm_wday = 0;
    _tm.tm_hour = m_Hour;
    _tm.tm_min = m_Min;
    _tm.tm_sec = m_Sec;
    _tm.tm_isdst = -1;
    m_Time = (T_ULONG)mktime(&_tm);
  }

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

} // __convertToTime


/////////////////////////////////////////////////////////////////////////////
void CTime::__normalize() {
  m_Time = m_Time + (m_USec / 1000000);
  m_USec = m_USec % 1000000;
} // __normalize


/////////////////////////////////////////////////////////////////////////////
CTime::CTime(T_ULONG uTime) :
  m_Time(uTime),
  m_Year(0), 
  m_Month(0), 
  m_Day(0), 
  m_Hour(0), 
  m_Min(0), 
  m_Sec(0), 
  m_USec(0) {
  __convertToDate();
} // CTime


/////////////////////////////////////////////////////////////////////////////
CTime::CTime(T_ULONG uYear, T_ULONG uMonth, T_ULONG uDay, T_ULONG uHour, T_ULONG uMin, T_ULONG uSec) :
  m_Time(0),
  m_Year(uYear), 
  m_Month(uMonth), 
  m_Day(uDay), 
  m_Hour(uHour), 
  m_Min(uMin), 
  m_Sec(uSec), 
  m_USec(0) {
  __convertToTime();
} // CTime


/////////////////////////////////////////////////////////////////////////////
CTime::CTime(T_ULONG uSec, T_ULONG uUSec) :
  m_Time(uSec),
  m_Year(0), 
  m_Month(0), 
  m_Day(0), 
  m_Hour(0), 
  m_Min(0), 
  m_Sec(0), 
  m_USec(uUSec) {
  __normalize();
  __convertToDate();
} // CTime


/////////////////////////////////////////////////////////////////////////////
CTime::~CTime() {
} // ~CTime


/////////////////////////////////////////////////////////////////////////////
CTime::CTime(const CTime & tTime) :
  m_Time(tTime.m_Time),
  m_Year(tTime.m_Year), 
  m_Month(tTime.m_Month), 
  m_Day(tTime.m_Day), 
  m_Hour(tTime.m_Hour), 
  m_Min(tTime.m_Min), 
  m_Sec(tTime.m_Sec), 
  m_USec(tTime.m_USec) {
} // CTime


/////////////////////////////////////////////////////////////////////////////
CTime & CTime::operator=(const CTime & tTime) {
  m_Time = tTime.m_Time;
  m_Year = tTime.m_Year;
  m_Month = tTime.m_Month; 
  m_Day = tTime.m_Day; 
  m_Hour = tTime.m_Hour; 
  m_Min = tTime.m_Min; 
  m_Sec = tTime.m_Sec;
  m_USec = tTime.m_USec;
  return (* this);
} // operator=


/////////////////////////////////////////////////////////////////////////////
T_ULONG CTime::operator=(T_ULONG uTime) {
  SetTime(uTime);
  return (uTime);
} // operator=


/////////////////////////////////////////////////////////////////////////////
T_BOOLEAN CTime::operator<(const CTime & tTime) const {
  return ((GetDelaySec() < tTime.GetDelaySec()) || ((GetDelaySec() == tTime.GetDelaySec()) && (GetDelayUSec() < tTime.GetDelayUSec())));
} // operator<


/////////////////////////////////////////////////////////////////////////////
CTime CTime::operator+(const CTime & tTime) const {
  return (CTime(GetDelaySec() + tTime.GetDelaySec(), GetDelayUSec() + tTime.GetDelayUSec()));
} // operator+


/////////////////////////////////////////////////////////////////////////////
CTime CTime::operator-(const CTime & tTime) const {
  CTime tResult;

  tResult.SetDelaySec(GetDelaySec() - tTime.GetDelaySec());
  if (GetDelayUSec() >= tTime.GetDelayUSec()) {
    tResult.SetDelayUSec(GetDelayUSec() - tTime.GetDelayUSec());
  } else {
    tResult.SetDelaySec(tResult.GetDelaySec() - 1);
    tResult.SetDelayUSec(1000000 - (tTime.GetDelayUSec() - GetDelayUSec()));
  } 

  return (tResult);
} // operator-


/////////////////////////////////////////////////////////////////////////////
CTime CTime::operator*(T_ULONG uNumber) const {
  return (CTime(GetDelaySec() * uNumber, GetDelayUSec() * uNumber));
} // operator*


/////////////////////////////////////////////////////////////////////////////
CTime::operator T_ULONG () const {
  return (GetTime());
}  // operator T_ULONG


/////////////////////////////////////////////////////////////////////////////
T_BOOLEAN CTime::IsValid() const {
  return ((m_Time != 0) || (m_Year != 0) || (m_Month != 0) || (m_Day != 0) || (m_Hour != 0) || (m_Min != 0)|| (m_Sec != 0) || (m_USec != 0));
} // IsValid


/////////////////////////////////////////////////////////////////////////////
T_ULONG CTime::GetYearDay() const {
  T_ULONG uResult = 0;

#if (PA_FAMILY == PAF_X86)

  struct tm _tm;
  time_t t = GetTime();

  // convert time
  memset(&_tm, -1, sizeof(_tm));

#if (OS_FAMILY == OSF_WINDOWS)

  localtime_s(&_tm, &t);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  localtime_r(&t, &_tm);

#else
#error unsupported platform
#endif

  // set result
  uResult = (T_ULONG)_tm.tm_yday + 1; 

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

  return (uResult);
} // GetYearDay


/////////////////////////////////////////////////////////////////////////////
T_ULONG CTime::GetWeekDay() const {
  T_ULONG uResult = 0;

#if (PA_FAMILY == PAF_X86)

  struct tm _tm;
  time_t t = GetTime();

  // convert time
  memset(&_tm, -1, sizeof(_tm));

#if (OS_FAMILY == OSF_WINDOWS)

  localtime_s(&_tm, &t);

#elif ((OS_FAMILY == OSF_LINUX) | (OS_FAMILY == OSF_UNIX))

  localtime_r(&t, &_tm);

#else
#error unsupported platform
#endif

  // set result
  uResult = (T_ULONG)_tm.tm_wday + 1; 

#elif (PA_FAMILY == PAF_AVR)

#else
#error unsupported platform
#endif

  return (uResult);
} // GetWeekDay


/////////////////////////////////////////////////////////////////////////////
void CTime::Trim(times base) {
  switch (base) {
  case YEAR : {
    SetYear(1970);
    Trim(MONTH);
    break;
  }
  case MONTH : {
    SetMonth(1);
    Trim(DAY);
    break;
  }
  case WEEK: {
    break;
  }
  case DAY : {
    SetDay(1);
    Trim(HOUR);
    break;
  }
  case HOUR : {
    SetHour(0);
    Trim(MIN);
    break;
  }
  case MIN : {
    SetMin(0);
    Trim(SEC);
    break;
  }
  case SEC : {
    SetSec(0);
    break;
  }
  }
} // Trim


/////////////////////////////////////////////////////////////////////////////
CTime CTime::GetElapsed() const {
  return (STATIC_GetCurrent() - (* this));
} // GetElapsed


/////////////////////////////////////////////////////////////////////////////
T_BOOLEAN CTime::IsTimedOut(const CTime & tTimeOut) const {
  return ((tTimeOut.IsValid()) && (tTimeOut < GetElapsed()));
} // IsTimedOut

} // namespace BASE
