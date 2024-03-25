#ifndef __SYS_LOG_H__
#define __SYS_LOG_H__

#include <sys_type.h>
#include <sys_time.h>
#include <sys_color.h>

typedef enum _log_level_e
{
  Error,
  Warning,
  Info,
} LogLevel;

#define LOG_NAME "./DUMP.log"
#define STR_WARN "[W] "
#define STR_INFO "[I] "
#define STR_ERROR "[E] "

#define MAX_LOG_FILE_PATH 128
#define MAX_LOG_SINGLE_LINE 1024
void logMessage(const LogLevel pLevel);

bool writeLogToFile(const char *buffer);
LogLevel getLogLevel(void);
void setLogLevel(const LogLevel pLevel);
bool getOutLogToFileFLag(void);
void setOutLogToFileFlag(const bool pFlag);
bool getLogFilePath(char *pLogFilePath, const unsigned char pLength);
bool setLogFilePath(const char *pLogFilePath, const unsigned char pLength);
void LogFunction(const LogLevel pLevel, const char *fmt, ...);

#define PRINTK printf
#define PRINT(fmt, arg...) printf(fmt, ##arg)

#define WARN(fmt, arg...) LogFunction(Warning, fmt, ##arg)
#define INFO(fmt, arg...) LogFunction(Info, fmt, ##arg)
#define ERROR(fmt, arg...) LogFunction(Error, fmt, ##arg)
#endif
