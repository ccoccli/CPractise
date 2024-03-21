#include <sys_os.h>

void sys_os_sleep(const unsigned int pWaitTime)
{
  usleep(pWaitTime * 1000);
}
sys_os_ptr sys_os_malloc(const unsigned int pSize)
{
  sys_os_ptr ptr = NULL;
  if (pSize <= 0)
  {
    ERROR("The requested memory space is illegal, iSize=%d.\n", pSize);
    return NULL;
  }
#if SYS_OS_MALLOC_SWITCH
  ptr = malloc(pSize);
#else
  ptr = calloc(1, pSize);
#endif
  if (ptr == NULL)
  {
    ERROR("Failed to apply for memory.\n");
    return NULL;
  }

  // INFO("Success to apply for memory, ptr=0X%X.\n", ptr);
  return ptr;
}
sys_os_ptr sys_os_realloc(const sys_os_ptr pAddr, const unsigned int pSize)
{
  sys_os_ptr ptr = NULL;
  if (pSize <= 0 || pAddr == NULL)
  {
    ERROR("The requested memory space is illegal, iSize=%d.\n", pSize);
    return NULL;
  }
  ptr = realloc(pAddr, pSize);

  if (ptr == NULL)
  {
    ERROR("Failed to apply for memory.\n");
    return NULL;
  }

  // INFO("Success to apply for memory, ptr=0X%X.\n", ptr);
  return ptr;
}
void sys_os_free(sys_os_ptr pAddress)
{
  if (pAddress == NULL)
  {
    ERROR("The memory to be released is empty, illegal operation.\n");
  }
  // INFO("Success to free memory, ptr=0X%X.\n", pAddress);
  free(pAddress);
  pAddress = NULL;
}
static sys_os_ptr threadEntry(sys_os_ptr param)
{
  Task *task = (Task *)param;

  task->threadEntry(task->pvArgv);
}
TaskStatus sys_os_task_create(const char *ptaskName, task_entry_function pFunc, unsigned int pStackSize, unsigned int pTaskPriority, sys_os_handle *pTaskId, sys_os_ptr pParam)
{
  if (ptaskName == NULL || pFunc == NULL || pTaskId == NULL || pStackSize <= 0 || (pTaskPriority < 0 || pTaskPriority > 255))
  {
    ERROR("Invalid parameters for task creation.\n");
    return task_failed;
  }

  // INFO("Start create task-->name=%s, func=0X%X, stack size=0X%X, task priority=%d\n", ptaskName, pFunc, pStackSize, pTaskPriority);

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
  task->iStackSize = pStackSize /*+ ADDED_STACK_SIZE*/;
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
    pthread_attr_destroy(&attr);
    sys_os_free(task);
    return task_failed;
  }

  *pTaskId = (sys_os_handle)task;
  pthread_attr_destroy(&attr);

  return task_success;
}
TaskStatus sys_os_task_destory(const sys_os_handle pTaskId)
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
sys_os_bool sys_os_semaphore_create(const unsigned int pInitialTokenCount, sys_os_handle *pHandle)
{
  sem_t *pSem = (sem_t *)sys_os_malloc(sizeof(sem_t));

  if (NULL == pSem)
  {
    return false;
  }

  if (-1 == sem_init(pSem, 0, pInitialTokenCount))
  {
    return false;
  }
  *pHandle = (sys_os_handle)pSem;
  return true;
}
sys_os_bool sys_os_semaphore_destory(const sys_os_handle pHandle)
{
  if (pHandle == NULL || pHandle == INVALID_VALUE)
  {
    return false;
  }

  sem_t *pSem = (sem_t *)pHandle;

  if (sem_destroy(pSem) == -1)
  {
    sys_os_free(pSem);

    return false;
  }

  sys_os_free(pSem);

  return true;
}
sys_os_bool sys_os_semaphore_release(const sys_os_handle pHandle)
{
  if (pHandle == NULL || pHandle == INVALID_VALUE)
  {
    return false;
  }

  sem_t *pSem = (sem_t *)pHandle;
  if (0 != sem_post(pSem))
  {
    return false;
  }
  return true;
}
sys_os_bool sys_os_semaphore_wait(const sys_os_handle pHandle, const unsigned int pWaitTime)
{
  if (pHandle == NULL || pHandle == INVALID_VALUE)
  {
    return false;
  }

  struct timespec ts;
  struct timeval tv;
  sem_t *pSem = (sem_t *)pHandle;

  if (pWaitTime == INVALID_VALUE)
  {
    if (0 != sem_wait(pSem))
    {
      return false;
    }
  }
  else
  {
    gettimeofday(&tv, NULL);

    int sec = pWaitTime / 1000;
    int msec = pWaitTime % 1000;

    ts.tv_sec = tv.tv_sec + sec;
    ts.tv_nsec = tv.tv_usec * 1000 + msec * 1000 * 1000;
    ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
    ts.tv_nsec %= (1000 * 1000 * 1000);

    return sem_timedwait(pSem, &ts) == 0;
  }
}
sys_os_bool sys_os_queue_create(const unsigned int pDeepth, const unsigned char *pQueueName, sys_os_handle *pHandle)
{
  if (pHandle == NULL)
  {
    return false;
  }
  if (NULL == pQueueName || 0 == pDeepth)
  {
    *pHandle = (sys_os_handle)NULL;
    return false;
  }

  Queue *queue = (Queue *)sys_os_malloc(sizeof(Queue));
  if (queue == NULL)
  {
    *pHandle = (sys_os_handle)NULL;
    return false;
  }

  memset(queue, 0, sizeof(Queue));

  sys_os_semaphore_create(1, &queue->semHandle);
  if (queue->semHandle == NULL)
  {
    *pHandle = (sys_os_handle)NULL;
    sys_os_free(queue);
    queue = NULL;
    return false;
  }

  int msgid = msgget(IPC_PRIVATE, IPC_EXCL | IPC_CREAT | 0666);
  if (0 > msgid)
  {
    *pHandle = (sys_os_handle)NULL;
    sys_os_free(queue);
    queue = NULL;
    return false;
  }
  queue->queueHandle = msgid + 1;
  queue->maxMsgItem = pDeepth;

  *pHandle = (sys_os_handle)queue;

  return true;
}
sys_os_bool sys_os_queue_destory(const sys_os_handle pHandle)
{
  if (pHandle == (sys_os_handle)NULL || pHandle == INVALID_VALUE)
  {
    return false;
  }

  Queue *queue = (Queue *)pHandle;

  sys_os_semaphore_wait(queue->semHandle, INVALID_VALUE);

  int msgid = queue->queueHandle - 1;

  if (0 != msgctl(msgid, IPC_RMID, NULL))
  {
    sys_os_semaphore_release(queue->semHandle);
    return false;
  }

  sys_os_semaphore_release(queue->semHandle);
  sys_os_semaphore_destory(queue->semHandle);
  queue->semHandle = 0;

  sys_os_free(queue);
  queue = NULL;

  return true;
}
sys_os_bool sys_os_queue_receive_msg(const sys_os_handle pHandle, sys_os_ptr pMsg, const unsigned int pWaitTimeMs)
{
  if (pHandle == (sys_os_handle)NULL || pHandle == INVALID_VALUE)
  {
    return false;
  }

  Queue *queue = (Queue *)pHandle;

  QueueMsg queueMsg;
  memset(&queueMsg, 0, sizeof(QueueMsg));

  int msgid = queue->queueHandle - 1;

  if (pWaitTimeMs == INVALID_VALUE)
  {
    if (-1 == msgrcv(msgid, &queueMsg, sizeof(QueueMsg) - 4, 0, 0))
    {
      return false;
    }
    else
    {
      memcpy(pMsg, (sys_os_ptr)queueMsg.msgData, queueMsg.msgLen);
      sys_os_free(queueMsg.msgData);

      goto success;
    }
  }
  else
  {
    struct timeval tv1, tv2;

    gettimeofday(&tv1, NULL);
    tv1.tv_sec += pWaitTimeMs / 1000;
    tv1.tv_usec += (pWaitTimeMs % 1000) * 1000;

    do
    {
      gettimeofday(&tv2, NULL);

      if (msgrcv(msgid, &queueMsg, sizeof(QueueMsg) - 4, 0, IPC_NOWAIT) == -1)
      {
        if (ENOMSG != errno)
        {
          return false;
        }
      }
      else
      {
        memcpy(pMsg, (sys_os_ptr)queueMsg.msgData, queueMsg.msgLen);
        sys_os_free(queueMsg.msgData);

        goto success;
      }

      if (1000 * (tv2.tv_sec - tv1.tv_sec) + ((int)tv2.tv_usec - (int)tv1.tv_usec) / 1000 > 0)
      {
        break;
      }
      sys_os_sleep(1 * 1000);
    } while (1);
  }

  return false;
success:
  sys_os_semaphore_wait(queue->semHandle, INVALID_VALUE);
  queue->msgCount--;
  sys_os_semaphore_release(queue->semHandle);
  return true;
}
sys_os_bool sys_os_queue_send_msg(const sys_os_handle pHandle, const sys_os_ptr pMsg, const unsigned int pMsgSize)
{
  if (pHandle == (sys_os_handle)NULL || pHandle == INVALID_VALUE)
  {
    return false;
  }

  Queue *queue = (Queue *)pHandle;
  sys_os_semaphore_wait(queue->semHandle, INVALID_VALUE);
  if (queue->msgCount >= queue->maxMsgItem)
  {
    sys_os_semaphore_release(queue->semHandle);
    return false;
  }
  sys_os_semaphore_release(queue->semHandle);

  if (NULL == pMsg)
  {
    return false;
  }

  sys_os_ptr msg = sys_os_malloc(pMsgSize);
  if (NULL == msg)
  {
    return false;
  }
  memcpy(msg, pMsg, pMsgSize);

  int msgid = queue->queueHandle - 1;

  QueueMsg queueMsg;
  memset(&queueMsg, 0, sizeof(QueueMsg));

  queueMsg.msgData = (sys_os_ptr)msg;
  queueMsg.msgLen = pMsgSize;

  if (0 != msgsnd(msgid, &queueMsg, sizeof(QueueMsg) - 4, IPC_NOWAIT))
  {
    sys_os_free(msg);
    return false;
  }

  sys_os_semaphore_wait(queue->semHandle, INVALID_VALUE);
  queue->msgCount++;
  sys_os_semaphore_release(queue->semHandle);

  return true;
}

unsigned long long int sys_os_get_os_version(void)
{
  return OS_VERSION;
}
unsigned long long int sys_os_get_os_build_date(void)
{
  return getCurrentUTCTimestamp();
}