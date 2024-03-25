#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>
#include <sys_os.h>

#include <ds_linked_list.h>

int main()
{
  LinkedList *ll = ds_linked_list_create(1);

  ds_linked_list_push_back(ll, 2);
  ds_linked_list_print(ll);
  ds_linked_list_push_back(ll, 4);
  ds_linked_list_print(ll);
  ds_linked_list_push_back(ll, 8);
  ds_linked_list_print(ll);
  ds_linked_list_push_back(ll, 16);
  ds_linked_list_print(ll);
  ds_linked_list_push_back(ll, 32);
  ds_linked_list_print(ll);

  ds_linked_list_pop_back(ll);
  ds_linked_list_print(ll);
  ds_linked_list_pop_back(ll);
  ds_linked_list_print(ll);
  ds_linked_list_pop_back(ll);
  ds_linked_list_print(ll);

  ds_linked_list_push_head(&ll, 100);
  ds_linked_list_print(ll);
  ds_linked_list_push_head(&ll, 200);
  ds_linked_list_print(ll);
  ds_linked_list_push_head(&ll, 300);
  ds_linked_list_print(ll);
  ds_linked_list_push_head(&ll, 400);
  ds_linked_list_print(ll);

  ds_linked_list_pop_head(&ll);
  ds_linked_list_print(ll);

  PRINTK("linked list length : %d\n", ds_linked_list_length(ll));

  ds_linked_list_insert(&ll, 0, 11);
  ds_linked_list_print(ll);

  ds_linked_list_insert(&ll, 3, 22);
  ds_linked_list_print(ll);

  sys_int value = 0;
  ds_linked_list_delete(&ll, 3, &value);
  ds_linked_list_print(ll);
  PRINTK("the value has been deleted is : %d\n", value);

  ds_linked_list_destory(ll);
  return 0;
}