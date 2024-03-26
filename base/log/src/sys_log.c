#include <sys_log.h>

// 是否输出日志到文件(sys_true | sys_false)
static sys_bool g_outLogToFile = sys_false;

// 日志输出等级(Info | Warning | Error)
static LogLevel g_level = Info;

// 日志输出路径
static sys_char g_logFilePath[MAX_LOG_FILE_PATH];

sys_void logMessage(const LogLevel pLevel)
{
  baseTime time;
  getCurrentTime(&time);
  switch (pLevel)
  {
  case Warning:
  {
    PRINT(CONSOLE_YELLOW);
    PRINT(STR_WARN);
    break;
  }
  case Info:
  {
    PRINT(CONSOLE_GREEN);
    PRINT(STR_INFO);
    break;
  }
  case Error:
  {
    PRINT(CONSOLE_RED);
    PRINT(STR_ERROR);
    break;
  }
  }

  PRINT("[%04d:%02d:%02d-%02d:%02d:%02d] ", time.year, time.month, time.day, time.hour, time.minute, time.second);
}
sys_bool writeLogToFile(const sys_char *buffer)
{
  FILE *file = fopen(g_logFilePath, "a");

  if (file == NULL)
  {
    file = fopen(g_logFilePath, "w");
    if (file != NULL)
    {
      fprintf(file, "%s", buffer);
      fclose(file);
      return sys_true;
    }
    else
    {
      return sys_false;
    }
  }
  else
  {
    fprintf(file, "%s", buffer);
    fclose(file);

    return sys_true;
  }
}
sys_void setLogLevel(const LogLevel pLevel)
{
  g_level = pLevel;
}

LogLevel getLogLevel(sys_void)
{
  return g_level;
}
sys_bool getOutLogToFileFLag(sys_void)
{
  return g_outLogToFile;
}
sys_void setOutLogToFileFlag(const sys_bool pFlag)
{
  g_outLogToFile = pFlag;
}
sys_bool getLogFilePath(sys_char *pLogFilePath, const sys_uchar pLength)
{
  if (pLength > MAX_LOG_FILE_PATH || pLength <= 0)
  {
    ERROR("File output path exceeds maximum length limit or minmum length limit, pLength=%d\n", pLength);
    return sys_false;
  }
  if (pLogFilePath == NULL)
  {
    ERROR("The file output path pointer is null.\n");
    return sys_false;
  }

  strncpy(pLogFilePath, g_logFilePath, pLength - 1);
  pLogFilePath[pLength - 1] = '\0';

  return sys_true;
}
sys_bool setLogFilePath(const sys_char *pLogFilePath, const sys_uchar pLength)
{
  if (pLength > MAX_LOG_FILE_PATH || pLength <= 0)
  {
    ERROR("File output path exceeds maximum length limit or minmum length limit, pLength=%d\n", pLength);
    return sys_false;
  }
  if (pLogFilePath == NULL)
  {
    ERROR("The file output path pointer is null.\n");
    return sys_false;
  }

  sys_memset(g_logFilePath, 0, MAX_LOG_FILE_PATH);

  strncpy(g_logFilePath, pLogFilePath, pLength - 1);
  g_logFilePath[pLength - 1] = '\0';

  return sys_true;
}
sys_void LogFunction(const LogLevel pLevel, const sys_char *fmt, ...)
{
  logMessage(pLevel);

  va_list ap;
  va_start(ap, fmt);

  baseTime time;
  getCurrentTime(&time);

  sys_char buffer[MAX_LOG_SINGLE_LINE], sBuffer[MAX_LOG_SINGLE_LINE / 2];
  sys_memset(buffer, 0, MAX_LOG_SINGLE_LINE);
  sys_memset(sBuffer, 0, MAX_LOG_SINGLE_LINE / 2);

  vsnprintf((sys_char *)sBuffer, MAX_LOG_SINGLE_LINE / 2, (sys_char *)fmt, ap);

  switch (pLevel)
  {
  case Warning:
  {
    sys_snprintf(buffer, MAX_LOG_SINGLE_LINE, "%s [%04d:%02d:%02d-%02d:%02d:%02d] %s",
             STR_WARN, time.year, time.month, time.day, time.hour, time.minute, time.second, sBuffer);
    break;
  }
  case Info:
  {
    sys_snprintf(buffer, MAX_LOG_SINGLE_LINE, "%s [%04d:%02d:%02d-%02d:%02d:%02d] %s",
             STR_INFO, time.year, time.month, time.day, time.hour, time.minute, time.second, sBuffer);
    break;
  }
  case Error:
  {
    sys_snprintf(buffer, MAX_LOG_SINGLE_LINE, "%s [%04d:%02d:%02d-%02d:%02d:%02d] %s",
             STR_ERROR, time.year, time.month, time.day, time.hour, time.minute, time.second, sBuffer);
    break;
  }
  }
  va_end(ap);

  PRINT("%s", sBuffer);
  PRINT(CONSOLE_END_STR);

  if (getOutLogToFileFLag())
  {
    sys_char fileName[MAX_LOG_FILE_PATH];
    sys_snprintf(fileName, MAX_LOG_FILE_PATH, LOG_NAME);
    setLogFilePath(fileName, MAX_LOG_FILE_PATH);
    writeLogToFile(buffer);
  }
}