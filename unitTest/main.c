#include <unitTest.h>

int main()
{
  for (;;)
  {
    unit_test_print_menu();

    sys_char cmd[3];
    sys_memset(cmd, 0, sizeof(cmd));

    scanf("%2s", &cmd);
    executeCommand(cmd);
  }

  return 0;
}

sys_void unit_test_print_menu()
{
  baseTime time;
  getCurrentTime(&time);
  PRINTK("*******************%04d/%02d/%02d %02d:%02d:%02d*****************************\n", time.year, time.month, time.day, time.hour, time.minute, time.second);
  PRINTK("*********************** UNIT TEST *********************************\n");
  PRINTK("*******************************************************************\n");
  PRINTK("*              * 1. log test                                      *\n");
  PRINTK("*                  * a. out put a info message                    *\n");
  PRINTK("*                  * b. out put a warning message                 *\n");
  PRINTK("*                  * c. out put a error message                   *\n");
  PRINTK("*              * 2. system base module test                       *\n");
  PRINTK("*                  * a. init a task                               *\n");
  PRINTK("*                  * b. destory a task                            *\n");
  PRINTK("*                  * c. init a semaphore                          *\n");
  PRINTK("*                  * d. destory a semaphore                       *\n");
  PRINTK("*                  * e. semaphore release                         *\n");
  PRINTK("*                  * f. semaphore wait                            *\n");
  PRINTK("*                  * g. init a message queue                      *\n");
  PRINTK("*                  * h. destory a message queue                   *\n");
  PRINTK("*                  * i. send a message to message queue           *\n");
  PRINTK("*                  * j. receive a message from message queue      *\n");
  PRINTK("*                  * k. get os version                            *\n");
  PRINTK("*                  * l. get os build date                         *\n");
  PRINTK("*              * 3. time test                                     *\n");
  PRINTK("*              * 4. linear list test                              *\n");
  PRINTK("*                  * a.init a linear list                         *\n");
  PRINTK("*                  * b.insert a value to linear list by index     *\n");
  PRINTK("*                  * c.delete a value from linear list by index   *\n");
  PRINTK("*                  * d.get the size of the linear list            *\n");
  PRINTK("*                  * e.get the length of the linear list          *\n");
  PRINTK("*                  * f.determine if the linear list is empty      *\n");
  PRINTK("*                  * g.sort the linear list                       *\n");
  PRINTK("*                  * h.merge two linear lists                     *\n");
  PRINTK("*                  * i.destroy the linear list                    *\n");
  PRINTK("*              * 5. linked list test                              *\n");
  PRINTK("*              * e. exit unit test                                *\n");
  PRINTK("*******************************************************************\n");

  PRINTK("command > ");
}

sys_void executeCommand(sys_char *pCommand)
{
  switch (pCommand[0])
  {
  case '1':
  {
    switch (pCommand[1])
    {
    case 'a':
    {
      INFO("this is a test info message !\n");
      break;
    }
    case 'b':
    {
      WARN("this is a test warning message !\n");
      break;
    }
    case 'c':
    {
      ERROR("this is a test error message !\n");
      break;
    }
    default:
    {
      ERROR("invalid command.\n");
    }
    }
    break;
  }
  case '2':
  {
    break;
  }
  case '3':
  {
    break;
  }
  case '4':
  {
    static LinearList list;

    switch (pCommand[1])
    {
    // carete linear list
    case 'a':
    {
      if (linear_list_init(&list))
      {
        sys_int list_size = 0, list_value = 0;
        PRINTK("please input the initial size of the linear list and the initial value :");
        scanf("%d%d", &list_size, &list_value);
        if (list.create_linear_list_by_value(&list, list_size, list_value))
        {
          INFO("init linear list success, addr=0x%x\n", &list);
        }
        else
        {
          ERROR("init linear list failed !\n");
        }
      }
      break;
    }
    // insert value to liear list by index
    case 'b':
    {
      sys_int insert_value = 0, insert_index = 0;
      PRINTK("please input the insert value and the insert index :");
      scanf("%d%d", &insert_value, &insert_index);
      if (list.insert_elem_to_linear_list(&list, insert_index, insert_value))
      {
        INFO("insert value to the linear list success!\n");
        list.print(&list);
      }
      break;
    }
    // delete value from linear list by index and return the value
    case 'c':
    {
      sys_int delete_index = 0, delete_value = 0;
      PRINTK("please input the delete index :");
      scanf("%d", &delete_index);
      if (list.delete_elem_from_linear_list(&list, delete_index, &delete_value))
      {
        INFO("delete value from the linear list success, the delete value is : %d\n", delete_value);
        list.print(&list);
      }
      break;
    }
    // get the size of the linear list
    case 'd':
    {
      INFO("the linear list size is : %d\n", list.get_linear_list_size(&list));
      break;
    }
    // get the length of the linear list
    case 'e':
    {
      INFO("the linear list length is : %d\n", list.get_linear_list_length(&list));
      break;
    }
    // is th lear list empty
    case 'f':
    {
      if (list.is_linear_list_empty(&list))
      {
        INFO("the linear list isn't empty !\n");
      }
      else
      {
        INFO("the linear list is empty !\n");
      }
      break;
    }
    // sort the linear list
    case 'g':
    {
      sys_int sortRule = 0;
      INFO("please input the sort rule(0 is from min to max | 1 is from max to min) : ");
      scanf("%d", &sortRule);
      if (sortRule == 0)
      {
        list.sort_linear_list(&list, sys_false);
        list.print(&list);
      }
      else if (sortRule == 1)
      {
        list.sort_linear_list(&list, sys_true);
        list.print(&list);
      }
      break;
    }
    // merge two linear lists
    case 'h':
    {
      break;
    }
    // destory the linear list
    case 'i':
    {
      if (list.destory_linear_list(&list))
      {
        INFO("free linear list success !\n");
      }
      else
      {
        INFO("free linear list failed !\n");
      }
      break;
    }
    default:
    {
      ERROR("invalid command.\n");
      break;
    }
    }
    break;
  }
  case '5':
  {
    break;
  }
  case 'e':
  {
    WARN("unit test end !\n");
    exit(0);
  }
  default:
  {
    ERROR("invalid command.\n");
    break;
  }
  }
}