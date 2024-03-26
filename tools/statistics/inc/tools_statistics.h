#ifndef __TOOLS_STATISTICS_H__
#define __TOOLS_STATISTICS_H__

#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>
#include <sys_os.h>
#include <sys_string.h>

void countLines(const char *filename);
void traverseDir(const char *dirPath);
#endif //__TOOLS_STATISTICS_H__