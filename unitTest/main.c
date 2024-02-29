#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>
#include <sys_os.h>

int main()
{
  setLogLevel(Info);
  setOutLogToFileFlag(true);

  int count = 0;
  while(1)
  {
    INFO("count:%d.\n", count);
    WARN("count:%d.\n", count);
    ERROR("count:%d.\n", count++);

    WARN("%s\n", "hhhhhhhhhhhhhhhhhh");
    ERROR("%s\n", "aaaaaaaaaaaaaaaaaaaaaaaaaaa");
    INFO("%s\n", "bbbbbbbbbbbbbbbbbbbbbbbbb");
    if(count > 100)
      break;
    
    sys_os_sleep(3000);
  }
  return 0;
}