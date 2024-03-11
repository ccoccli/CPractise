#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>
#include <sys_os.h>

#define TEST_QUEUE_NAME "queue"
#define TEST_TASK_NAME "task"
static sys_os_handle g_QueueHandle = 0;
static sys_os_handle g_TaskHandle = 0;

void task(void *param)
{
  char buffer[1024];

  memset(buffer, 0, 1024);
  while (1)
  {
    if (sys_os_queue_receive_msg(g_QueueHandle, buffer, 10) != true)
    {
      continue;
    }
    else
    {
      INFO("%s\n", buffer);
    }
  }
}
int main()
{
  setLogLevel(Info);
  //setOutLogToFileFlag(true);

  if (sys_os_queue_create(1, TEST_QUEUE_NAME, &g_QueueHandle) == true)
  {
    INFO("test queue create success, g_QueueHandle=0x%x\n", g_QueueHandle);
  }
  else
  {
    ERROR("test queue create failed!\n");
  }

  if (sys_os_task_create(TEST_TASK_NAME, task, 1024, TASK_PRIORITY_15, &g_TaskHandle, 0) == task_success)
  {
    INFO("test task create success,g_TaskHandle=0x%x\n", g_TaskHandle);
  }
  else
  {
    ERROR("test task create failed!\n");
  }
  int count = 0;
  char buf[1024];


  while(1)
  {
    memset(buf, 0, sizeof(buf));
    snprintf(buf, MAX_LOG_SINGLE_LINE, "conuter");
    sys_os_queue_send_msg(g_QueueHandle, buf, 1024);

    sys_os_sleep(3);
  }
  return 0;
}