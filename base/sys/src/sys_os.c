#include <sys_os.h>

void sys_os_sleep(unsigned int pWaitTime)
{
  usleep(pWaitTime * 1000);
}
void *sys_os_malloc(unsigned int pSize)
{
  setLogLevel(Error);

  void *ptr = NULL;
  if (pSize <= 0)
  {
    ERROR("The requested memory space is illegal, iSize=%d.\n", pSize);
    return NULL;
  }

  ptr = calloc(1, pSize);
  if (ptr == NULL)
  {
    ERROR("Failed to apply for memory.\n");
    return NULL;
  }

  INFO("Success to apply for memory, ptr=0X%X.\n", ptr);
  return ptr;
}
void sys_os_free(void *pAddress)
{
  setLogLevel(Error);
  if (pAddress == NULL)
  {
    ERROR("The memory to be released is empty, illegal operation.\n");
  }
  INFO("Success to free memory, ptr=0X%X.\n", pAddress);
  free(pAddress);
  pAddress = NULL;
}
static void *threadEntry(void *param)
{
  Task *task = (Task *)param;

  task->threadEntry(task->pvArgv);
}
TaskStatus sys_os_task_create(const char *ptaskName, task_entry_function pFunc, unsigned int pStackSize, unsigned int pTaskPriority, unsigned int *pTaskId, void *pParam)
{
  setLogLevel(Error);

  if (ptaskName == NULL || pFunc == NULL || pTaskId == NULL || pStackSize <= 0 || (pTaskPriority < 0 || pTaskPriority > 255))
  {
    ERROR("Invalid parameters for task creation.\n");
    return task_failed;
  }

  INFO("Start create task-->name=%s, func=0X%X, stack size=0X%X, task priority=%d\n", ptaskName, pFunc, pStackSize, pTaskPriority);

  pStackSize = (pStackSize < 0x4000) ? 0x4000 : pStackSize;

  int nNewPrio = POSIX_TASK_NORMAL;
  int nTempPrio = pTaskPriority / TASK_PRIOR_STEP;

  if (nTempPrio < 4)
  {
    nNewPrio = POSIX_TASK_LOWEST;
  }
  else if (nTempPrio < 8)
  {
    nNewPrio = POSIX_TASK_LOW;
  }
  else if (nTempPrio < 12)
  {
    nNewPrio = POSIX_TASK_NORMAL;
  }
  else if (nTempPrio < 14)
  {
    nNewPrio = POSIX_TASK_HIGH;
  }
  else
  {
    nNewPrio = POSIX_TASK_HIGHEST;
  }

  Task *task = (Task *)sys_os_malloc(sizeof(Task));
  if (task == NULL)
  {
    ERROR("Memory allocation for task structure failed.\n");
    return task_failed;
  }

  task->pvArgv = pParam;
  task->iStackSize = pStackSize + ADDED_STACK_SIZE;
  task->iPriority = nNewPrio;
  task->threadEntry = pFunc;
  snprintf(task->name, sizeof(task->name), "%s", ptaskName);

  pthread_attr_t attr;
  struct sched_param prio;

  // 初始化线程属性
  if (pthread_attr_init(&attr) != 0)
  {
    ERROR("Failed to initialize thread attributes.\n");
    sys_os_free(task);
    return task_failed;
  }

  // 设置线程栈大小
  if (pthread_attr_setstacksize(&attr, task->iStackSize) != 0)
  {
    ERROR("Failed to set thread stack size.\n");
    pthread_attr_destroy(&attr);
    sys_os_free(task);
    return task_failed;
  }

  // 设置调度策略为轮转调度
  if (pthread_attr_setschedpolicy(&attr, SCHED_RR) != 0)
  {
    ERROR("Failed to set scheduling policy.\n");
    pthread_attr_destroy(&attr);
    sys_os_free(task);
    return task_failed;
  }

  // 获取当前调度参数
  if (pthread_attr_getschedparam(&attr, &prio) != 0)
  {
    ERROR("Failed to get scheduling parameters.\n");
    pthread_attr_destroy(&attr);
    sys_os_free(task);
    return task_failed;
  }

  // 设置调度参数的优先级
  prio.sched_priority = task->iPriority;
  if (pthread_attr_setschedparam(&attr, &prio) != 0)
  {
    ERROR("Failed to set scheduling parameters.\n");
    pthread_attr_destroy(&attr);
    sys_os_free(task);
    return task_failed;
  }

  // 创建线程
  if (pthread_create(&(task->thread), &attr, threadEntry, task) != 0)
  {
    ERROR("Failed to create thread.\n");
    pthread_attr_destroy(&attr);
    sys_os_free(task);
    return task_failed;
  }

  *pTaskId = (unsigned int)task;
  pthread_attr_destroy(&attr);
  return task_success;
}
TaskStatus sys_os_task_destory(unsigned int pTaskId)
{
  if (pTaskId == NULL || pTaskId == INVALID_VALUE)
  {
    return task_failed;
  }

  Task *task = (Task *)pTaskId;

  if (pthread_cancel(task->thread) != 0)
  {
    ERROR("Failed to cancel the thread.\n");
    return task_failed;
  }

  if (pthread_join(task->thread, NULL) != 0)
  {
    ERROR("Failed to join the thread.\n");
    return task_failed;
  }

  sys_os_free(task);

  return task_success;
}
