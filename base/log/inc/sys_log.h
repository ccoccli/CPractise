#ifndef __SYS_LOG_H__
#define __SYS_LOG_H__

#include <sys_type.h>
#include <sys_time.h>
#include <sys_color.h>
#include <sys_string.h>

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
sys_void logMessage(const LogLevel pLevel);

sys_bool writeLogToFile(const char *buffer);
LogLevel getLogLevel(sys_void);
sys_void setLogLevel(const LogLevel pLevel);
sys_bool getOutLogToFileFLag(sys_void);
sys_void setOutLogToFileFlag(const sys_bool pFlag);
sys_bool getLogFilePath(char *pLogFilePath, const sys_uchar pLength);
sys_bool setLogFilePath(const char *pLogFilePath, const sys_uchar pLength);
sys_void LogFunction(const LogLevel pLevel, const sys_char *fmt, ...);

#define PRINTK printf
#define PRINT(fmt, arg...) printf(fmt, ##arg)

#define WARN(fmt, arg...) LogFunction(Warning, fmt, ##arg)
#define INFO(fmt, arg...) LogFunction(Info, fmt, ##arg)
#define ERROR(fmt, arg...) LogFunction(Error, fmt, ##arg)
#endif
