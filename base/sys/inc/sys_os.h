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
 * @brief ʹ��ǰ�߳�����ָ��ʱ�䣨���룩��
 * 
 * @param pWaitTime ����ʱ�䣬��λ���롣
 */
void sys_os_sleep(const unsigned int pWaitTime);

/**
 * @brief ����ָ����С���ڴ�ռ䡣
 * 
 * @param pSize �����ڴ�Ĵ�С����λ�ֽڡ�
 * @return ���䵽���ڴ��ָ�룬�������ʧ���򷵻� NULL��
 */
sys_os_ptr sys_os_malloc(const unsigned int pSize);

/**
 * @brief �ͷ�֮ǰͨ�� sys_os_malloc ������ڴ档
 * 
 * @param iAddress Ҫ�ͷŵ��ڴ��ַ��
 */
void sys_os_free(sys_os_ptr iAddress);

/**
 * @brief ����һ���µ�����
 * 
 * @param ptaskName ��������ơ�
 * @param pFunc �������ں�����
 * @param pStackSize �����ջ��С��
 * @param pTaskPriority ��������ȼ���
 * @param pTaskId ����ı�ʶ�������ڷ��ش���������ľ����
 * @param pParam ���ݸ�������ں����Ĳ�����
 * @return ���������״̬��task_success ��ʾ�ɹ�������ֵ��ʾʧ�ܡ�
 */
TaskStatus sys_os_task_create(const char *ptaskName, task_entry_function pFunc, unsigned int pStackSize, unsigned int pTaskPriority, sys_os_handle *pTaskId, sys_os_ptr pParam);

/**
 * @brief ����ָ��������
 * 
 * @param pTaskId Ҫ���ٵ�����ľ����
 * @return �������ٵ�״̬��task_success ��ʾ�ɹ�������ֵ��ʾʧ�ܡ�
 */
TaskStatus sys_os_task_destory(const sys_os_handle pTaskId);

/**
 * @brief ����һ���ź�����
 * 
 * @param pInitialTokenCount ��ʼ��������
 * @param pHandle ���ڷ��ش������ź����ľ����
 * @return �����ź�����״̬��true ��ʾ�ɹ���false ��ʾʧ�ܡ�
 */
sys_os_bool sys_os_semaphore_create(const unsigned int pInitialTokenCount, sys_os_handle *pHandle);

/**
 * @brief ����ָ�����ź�����
 * 
 * @param pHandle Ҫ���ٵ��ź����ľ����
 * @return �ź������ٵ�״̬��true ��ʾ�ɹ���false ��ʾʧ�ܡ�
 */
sys_os_bool sys_os_semaphore_destory(const sys_os_handle pHandle);

/**
 * @brief �ͷ��ź����е�һ�����ơ�
 * 
 * @param pHandle �ź����ľ����
 * @return �ͷ����Ƶ�״̬��true ��ʾ�ɹ���false ��ʾʧ�ܡ�
 */
sys_os_bool sys_os_semaphore_release(const sys_os_handle pHandle);

/**
 * @brief �ȴ��ź����ϵ����ƣ������õȴ���ʱʱ�䡣
 * 
 * @param pHandle �ź����ľ����
 * @param pWaitTime �ȴ��ĳ�ʱʱ�䣬��λ���롣
 * @return �ȴ����Ƶ�״̬��true ��ʾ�ɹ���false ��ʾʧ�ܻ�ʱ��
 */
sys_os_bool sys_os_semaphore_wait(const sys_os_handle pHandle, const unsigned int pWaitTime);

/**
 * @brief ����һ����Ϣ���С�
 * 
 * @param pDeepth ��Ϣ���е���ȡ�
 * @param pQueueName ��Ϣ���е����ơ�
 * @param pHandle ���ڷ��ش�������Ϣ���еľ����
 * @return ������Ϣ���е�״̬��true ��ʾ�ɹ���false ��ʾʧ�ܡ�
 */
sys_os_bool sys_os_queue_create(const unsigned int pDeepth, const unsigned char *pQueueName, sys_os_handle *pHandle);

/**
 * @brief ����ָ������Ϣ���С�
 * 
 * @param pHandle Ҫ���ٵ���Ϣ���еľ����
 * @return ��Ϣ�������ٵ�״̬��true ��ʾ�ɹ���false ��ʾʧ�ܡ�
 */
sys_os_bool sys_os_queue_destory(const sys_os_handle pHandle);

/**
 * @brief ����Ϣ�����н�����Ϣ�������õȴ���ʱʱ�䡣
 * 
 * @param pHandle ��Ϣ���еľ����
 * @param pMsg ���ڴ洢���յ�����Ϣ��ָ�롣
 * @param pWaitTimeMs �ȴ���Ϣ�ĳ�ʱʱ�䣬��λ���롣
 * @return ������Ϣ��״̬��true ��ʾ�ɹ���false ��ʾʧ�ܻ�ʱ��
 */
sys_os_bool sys_os_queue_receive_msg(const sys_os_handle pHandle, sys_os_ptr pMsg, const unsigned int pWaitTimeMs);

/**
 * @brief ����Ϣ�����з�����Ϣ��
 * 
 * @param pHandle ��Ϣ���еľ����
 * @param pMsg Ҫ���͵���Ϣ��ָ�롣
 * @param pMsgSize ��Ϣ�Ĵ�С��
 * @return ������Ϣ��״̬��true ��ʾ�ɹ���false ��ʾʧ�ܡ�
 */
sys_os_bool sys_os_queue_send_msg(const sys_os_handle pHandle, const sys_os_ptr pMsg, const unsigned int pMsgSize);

#endif //__SYS_OS_H__