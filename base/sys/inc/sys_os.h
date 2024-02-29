#ifndef __SYS_OS_H__
#define __SYS_OS_H__

#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>

#define TASK_PRIOR_STEP 17
#define POSIX_TASK_LOWEST 1
#define POSIX_TASK_LOW 20
#define POSIX_TASK_NORMAL 40
#define POSIX_TASK_HIGH 70
#define POSIX_TASK_HIGHEST 90
#define POSIX_TASK_IST 99

#define ADDED_STACK_SIZE (8 * 1024)

typedef enum _task_status_e
{
  task_success = 0,
  task_failed = -1,
  task_timeout = -50,
} TaskStatus;

typedef enum _task_priority_e
{
  TASK_PRIORITY_0 = 0 * 17,
  TASK_PRIORITY_1 = 1 * 17,
  TASK_PRIORITY_2 = 2 * 17,
  TASK_PRIORITY_3 = 3 * 17,
  TASK_PRIORITY_4 = 4 * 17,
  TASK_PRIORITY_5 = 5 * 17,
  TASK_PRIORITY_6 = 6 * 17,
  TASK_PRIORITY_7 = 7 * 17,
  TASK_PRIORITY_8 = 8 * 17,
  TASK_PRIORITY_9 = 9 * 17,
  TASK_PRIORITY_10 = 10 * 17,
  TASK_PRIORITY_11 = 11 * 17,
  TASK_PRIORITY_12 = 12 * 17,
  TASK_PRIORITY_13 = 13 * 17,
  TASK_PRIORITY_14 = 14 * 17,
  TASK_PRIORITY_15 = 15 * 17
} TASK_PRIORITY;

typedef void (*task_entry_function)(void *);

typedef struct _sys_os_task_s
{
  void *pvArgv;
  pthread_t thread;
  task_entry_function threadEntry;
  unsigned int iPriority;
  unsigned int iStackSize;
  char name[64];
} Task;

void sys_os_sleep(unsigned int pWaitTime);

void *sys_os_malloc(unsigned int pSize);
void sys_os_free(void *iAddress);
TaskStatus sys_os_task_create(const char *ptaskName, task_entry_function pFunc, unsigned int pStackSize, unsigned int pTaskPriority, unsigned int *pTaskId, void *pParam);
TaskStatus sys_os_task_destory(unsigned int pTaskId);
#endif //__SYS_OS_H__