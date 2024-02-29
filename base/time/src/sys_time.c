#include <sys_time.h>

bool getCurrentTime(baseTime *pTime)
{
  if (!pTime)
  {
    return false;
  }

  time_t currentTime;

  time(&currentTime);
  struct tm *localTime = localtime(&currentTime);

  memset(pTime, 0, sizeof(baseTime));

  pTime->year = localTime->tm_year + 1900;
  pTime->month = localTime->tm_mon + 1;
  pTime->day = localTime->tm_mday;
  pTime->hour = localTime->tm_hour;
  pTime->minute = localTime->tm_min;
  pTime->second = localTime->tm_sec;

  return true;
}
time_t getCurrentUTCTimestamp(void)
{
  time_t currentTime;
  time(&currentTime);
  return currentTime;
}
bool getCurrentYear(base_time_t *pYear)
{
  if (!pYear)
  {
    return false;
  }
  baseTime iTime;

  memset(&iTime, 0, sizeof(baseTime));

  if (!getCurrentTime(&iTime))
  {
    *pYear = 0;
    return false;
  }

  *pYear = iTime.year;

  return true;
}
bool getCurrentMonth(base_time_t *pMonth)
{
  if (!pMonth)
  {
    return false;
  }

  baseTime currentTime;
  if (!getCurrentTime(&currentTime))
  {
    *pMonth = 0;
    return false;
  }

  *pMonth = currentTime.month;

  return true;
}
bool getCurrentDay(base_time_t *pDay)
{
  if (!pDay)
  {
    return false;
  }

  baseTime currentTime;
  if (!getCurrentTime(&currentTime))
  {
    *pDay = 0;
    return false;
  }

  *pDay = currentTime.day;

  return true;
}
bool getCurrentHour(base_time_t *pHour)
{
  if (!pHour)
  {
    return false;
  }

  baseTime currentTime;
  if (!getCurrentTime(&currentTime))
  {
    *pHour = 0;
    return false;
  }

  *pHour = currentTime.hour;

  return true;
}
bool getCurrentMinute(base_time_t *pMinute)
{
  if (!pMinute)
  {
    return false;
  }

  baseTime currentTime;
  if (!getCurrentTime(&currentTime))
  {
    *pMinute = 0;
    return false;
  }

  *pMinute = currentTime.minute;

  return true;
}
bool getCurrentSecond(base_time_t *pSecond)
{
  if (!pSecond)
  {
    return false;
  }

  baseTime currentTime;
  if (!getCurrentTime(&currentTime))
  {
    *pSecond = 0;
    return false;
  }

  *pSecond = currentTime.second;

  return true;
}
char compareBaseTime(const baseTime *t1, const baseTime *t2)
{
  if (t1->year > t2->year)
  {
    return 1;
  }
  else if (t1->year < t2->year)
  {
    return -1;
  }

  if (t1->month > t2->month)
  {
    return 1;
  }
  else if (t1->month < t2->month)
  {
    return -1;
  }

  if (t1->day > t2->day)
  {
    return 1;
  }
  else if (t1->day < t2->day)
  {
    return -1;
  }

  if (t1->hour > t2->hour)
  {
    return 1;
  }
  else if (t1->hour < t2->hour)
  {
    return -1;
  }

  if (t1->minute > t2->minute)
  {
    return 1;
  }
  else if (t1->minute < t2->minute)
  {
    return -1;
  }

  if (t1->second > t2->second)
  {
    return 1;
  }
  else if (t1->second < t2->second)
  {
    return -1;
  }

  return 0;
}
void getMaxTime(const baseTime *t1, const baseTime *t2, baseTime *result)
{
  *result = (compareBaseTime(t1, t2) >= 0) ? *t1 : *t2;
}
void getMinTime(const baseTime *t1, const baseTime *t2, baseTime *result)
{
  *result = (compareBaseTime(t1, t2) <= 0) ? *t1 : *t2;
}
bool convertUTCToLocalTime(const time_t utcTimestamp, baseTime *pTime)
{
  if (utcTimestamp == (long long)-1 || pTime == NULL)
  {
    return false;
  }

  struct tm *localTime = localtime(&utcTimestamp);

  memset(pTime, 0, sizeof(baseTime));

  pTime->year = localTime->tm_year + 1900;
  pTime->month = localTime->tm_mon + 1;
  pTime->day = localTime->tm_mday;
  pTime->hour = localTime->tm_hour;
  pTime->minute = localTime->tm_min;
  pTime->second = localTime->tm_sec;

  return true;
}

unsigned long long convertLocalTimeToUTC(const baseTime *pTime)
{
  if (pTime == NULL)
  {
    return INVALID_VALUE;
  }

  struct tm localTime;

  memset(&localTime, 0, sizeof(struct tm));

  localTime.tm_year = pTime->year - 1900;
  localTime.tm_mon = pTime->month - 1;
  localTime.tm_mday = pTime->day;
  localTime.tm_hour = pTime->hour;
  localTime.tm_min = pTime->minute;
  localTime.tm_sec = pTime->second;

  if (localTime.tm_mon < 0 || localTime.tm_mon > 11 ||
      localTime.tm_mday < 1 || localTime.tm_mday > 31 ||
      localTime.tm_hour < 0 || localTime.tm_hour > 23 ||
      localTime.tm_min < 0 || localTime.tm_min > 59 ||
      localTime.tm_sec < 0 || localTime.tm_sec > 59)
  {
    return INVALID_VALUE;
  }

  return mktime(&localTime);
}