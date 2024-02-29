#include <sys_log.h>

// 是否输出日志到文件(true | false)
static bool g_outLogToFile = false;

// 日志输出等级(Info | Warning | Error)
static LogLevel g_level = Info;

// 日志输出路径
static char g_logFilePath[MAX_LOG_FILE_PATH];

void logMessage(const LogLevel pLevel)
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
bool writeLogToFile(const char *buffer)
{
  FILE *file = fopen(g_logFilePath, "a");

  if (file == NULL)
  {
    file = fopen(g_logFilePath, "w");
    if (file != NULL)
    {
      fprintf(file, "%s", buffer);
      fclose(file);
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    fprintf(file, "%s", buffer);
    fclose(file);

    return true;
  }
}
void setLogLevel(const LogLevel pLevel)
{
  g_level = pLevel;
}

LogLevel getLogLevel(void)
{
  return g_level;
}
bool getOutLogToFileFLag(void)
{
  return g_outLogToFile;
}
void setOutLogToFileFlag(const bool pFlag)
{
  g_outLogToFile = pFlag;
}
bool getLogFilePath(char *pLogFilePath, const unsigned char pLength)
{
  if (pLength > MAX_LOG_FILE_PATH || pLength <= 0)
  {
    ERROR("File output path exceeds maximum length limit or minmum length limit, pLength=%d\n", pLength);
    return false;
  }
  if (pLogFilePath == NULL)
  {
    ERROR("The file output path pointer is null.\n");
    return false;
  }

  strncpy(pLogFilePath, g_logFilePath, pLength - 1);
  pLogFilePath[pLength - 1] = '\0';

  return true;
}
bool setLogFilePath(const char *pLogFilePath, const unsigned char pLength)
{
  if (pLength > MAX_LOG_FILE_PATH || pLength <= 0)
  {
    ERROR("File output path exceeds maximum length limit or minmum length limit, pLength=%d\n", pLength);
    return false;
  }
  if (pLogFilePath == NULL)
  {
    ERROR("The file output path pointer is null.\n");
    return false;
  }

  memset(g_logFilePath, 0, MAX_LOG_FILE_PATH);

  strncpy(g_logFilePath, pLogFilePath, pLength - 1);
  g_logFilePath[pLength - 1] = '\0';

  return true;
}
void LogFunction(const LogLevel pLevel, const char *fmt, ...)
{
  logMessage(pLevel);

  va_list ap;
  va_start(ap, fmt);

  baseTime time;
  getCurrentTime(&time);

  char buffer[MAX_LOG_SINGLE_LINE], sBuffer[MAX_LOG_SINGLE_LINE / 2];
  memset(buffer, 0, MAX_LOG_SINGLE_LINE);
  memset(sBuffer, 0, MAX_LOG_SINGLE_LINE / 2);

  vsnprintf((char *)sBuffer, MAX_LOG_SINGLE_LINE / 2, (char *)fmt, ap);

  switch (pLevel)
  {
  case Warning:
  {
    snprintf(buffer, MAX_LOG_SINGLE_LINE, "%s [%04d:%02d:%02d-%02d:%02d:%02d] %s",
             STR_WARN, time.year, time.month, time.day, time.hour, time.minute, time.second, sBuffer);
    break;
  }
  case Info:
  {
    snprintf(buffer, MAX_LOG_SINGLE_LINE, "%s [%04d:%02d:%02d-%02d:%02d:%02d] %s",
             STR_INFO, time.year, time.month, time.day, time.hour, time.minute, time.second, sBuffer);
    break;
  }
  case Error:
  {
    snprintf(buffer, MAX_LOG_SINGLE_LINE, "%s [%04d:%02d:%02d-%02d:%02d:%02d] %s",
             STR_ERROR, time.year, time.month, time.day, time.hour, time.minute, time.second, sBuffer);
    break;
  }
  }
  va_end(ap);

  PRINT("%s", sBuffer);
  PRINT(CONSOLE_END_STR);

  if (getOutLogToFileFLag())
  {
    char fileName[MAX_LOG_FILE_PATH];
    snprintf(fileName, MAX_LOG_FILE_PATH, LOG_NAME);
    setLogFilePath(fileName, MAX_LOG_FILE_PATH);
    writeLogToFile(buffer);
  }
}