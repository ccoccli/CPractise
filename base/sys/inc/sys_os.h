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
#define MAX_QUEUE_MSG_SIZE 1024

typedef unsigned long long int sys_os_handle;
typedef void *sys_os_ptr;
typedef bool sys_os_bool;

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

typedef void (*task_entry_function)(sys_os_ptr);

typedef struct _sys_os_task_s
{
  sys_os_ptr pvArgv;
  pthread_t thread;
  task_entry_function threadEntry;
  unsigned int iPriority;
  unsigned int iStackSize;
  char name[64];
} Task;
typedef struct _sys_os_queue_s
{
  int maxMsgItem;
  int msgCount;
  sys_os_handle queueHandle;
  sys_os_handle semHandle;
} Queue;
typedef struct _sys_os_queue_msg_s
{
  int msgLen;
  sys_os_ptr msgData;
} QueueMsg;

/**
 * @brief 使当前线程休眠指定时间（毫秒）。
 * 
 * @param pWaitTime 休眠时间，单位毫秒。
 */
void sys_os_sleep(const unsigned int pWaitTime);

/**
 * @brief 分配指定大小的内存空间。
 * 
 * @param pSize 分配内存的大小，单位字节。
 * @return 分配到的内存的指针，如果分配失败则返回 NULL。
 */
sys_os_ptr sys_os_malloc(const unsigned int pSize);

sys_os_ptr sys_os_realloc(const sys_os_ptr pAddr, const unsigned int pSize);
/**
 * @brief 释放之前通过 sys_os_malloc 分配的内存。
 * 
 * @param iAddress 要释放的内存地址。
 */
void sys_os_free(sys_os_ptr iAddress);

/**
 * @brief 创建一个新的任务。
 * 
 * @param ptaskName 任务的名称。
 * @param pFunc 任务的入口函数。
 * @param pStackSize 任务的栈大小。
 * @param pTaskPriority 任务的优先级。
 * @param pTaskId 任务的标识符，用于返回创建的任务的句柄。
 * @param pParam 传递给任务入口函数的参数。
 * @return 创建任务的状态，task_success 表示成功，其他值表示失败。
 */
TaskStatus sys_os_task_create(const char *ptaskName, task_entry_function pFunc, unsigned int pStackSize, unsigned int pTaskPriority, sys_os_handle *pTaskId, sys_os_ptr pParam);

/**
 * @brief 销毁指定的任务。
 * 
 * @param pTaskId 要销毁的任务的句柄。
 * @return 任务销毁的状态，task_success 表示成功，其他值表示失败。
 */
TaskStatus sys_os_task_destory(const sys_os_handle pTaskId);

/**
 * @brief 创建一个信号量。
 * 
 * @param pInitialTokenCount 初始令牌数。
 * @param pHandle 用于返回创建的信号量的句柄。
 * @return 创建信号量的状态，true 表示成功，false 表示失败。
 */
sys_os_bool sys_os_semaphore_create(const unsigned int pInitialTokenCount, sys_os_handle *pHandle);

/**
 * @brief 销毁指定的信号量。
 * 
 * @param pHandle 要销毁的信号量的句柄。
 * @return 信号量销毁的状态，true 表示成功，false 表示失败。
 */
sys_os_bool sys_os_semaphore_destory(const sys_os_handle pHandle);

/**
 * @brief 释放信号量中的一个令牌。
 * 
 * @param pHandle 信号量的句柄。
 * @return 释放令牌的状态，true 表示成功，false 表示失败。
 */
sys_os_bool sys_os_semaphore_release(const sys_os_handle pHandle);

/**
 * @brief 等待信号量上的令牌，可设置等待超时时间。
 * 
 * @param pHandle 信号量的句柄。
 * @param pWaitTime 等待的超时时间，单位毫秒。
 * @return 等待令牌的状态，true 表示成功，false 表示失败或超时。
 */
sys_os_bool sys_os_semaphore_wait(const sys_os_handle pHandle, const unsigned int pWaitTime);

/**
 * @brief 创建一个消息队列。
 * 
 * @param pDeepth 消息队列的深度。
 * @param pQueueName 消息队列的名称。
 * @param pHandle 用于返回创建的消息队列的句柄。
 * @return 创建消息队列的状态，true 表示成功，false 表示失败。
 */
sys_os_bool sys_os_queue_create(const unsigned int pDeepth, const unsigned char *pQueueName, sys_os_handle *pHandle);

/**
 * @brief 销毁指定的消息队列。
 * 
 * @param pHandle 要销毁的消息队列的句柄。
 * @return 消息队列销毁的状态，true 表示成功，false 表示失败。
 */
sys_os_bool sys_os_queue_destory(const sys_os_handle pHandle);

/**
 * @brief 从消息队列中接收消息，可设置等待超时时间。
 * 
 * @param pHandle 消息队列的句柄。
 * @param pMsg 用于存储接收到的消息的指针。
 * @param pWaitTimeMs 等待消息的超时时间，单位毫秒。
 * @return 接收消息的状态，true 表示成功，false 表示失败或超时。
 */
sys_os_bool sys_os_queue_receive_msg(const sys_os_handle pHandle, sys_os_ptr pMsg, const unsigned int pWaitTimeMs);

/**
 * @brief 向消息队列中发送消息。
 * 
 * @param pHandle 消息队列的句柄。
 * @param pMsg 要发送的消息的指针。
 * @param pMsgSize 消息的大小。
 * @return 发送消息的状态，true 表示成功，false 表示失败。
 */
sys_os_bool sys_os_queue_send_msg(const sys_os_handle pHandle, const sys_os_ptr pMsg, const unsigned int pMsgSize);

/**
 * @brief 获取操作系统版本信息
 * 
 * @return 操作系统版本的无符号长整型表示
 */
unsigned long long int sys_os_get_os_version(void);

/**
 * @brief 获取操作系统构建日期
 * 
 * @return 操作系统构建日期的无符号长整型表示
 */
unsigned long long int sys_os_get_os_build_date(void);

#endif //__SYS_OS_H__