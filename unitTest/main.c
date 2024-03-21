#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>
#include <sys_os.h>

#include <ds_singly_linked_list.h>

int main()
{
  SLinkedList p;

  link_list_init(&p);

  p.init_link_list(&p, 10);
  for (int i = 0; i < p.iSize; i++)
  {
    p.iElem[i] = i + 1;
    p.iLength++;
  }

  for (int i = 0; i < p.iSize; i++)
  {
    printf("%3d ", p.iElem[i]);
  }
  printf("\n");

  p.insert_elem_to_link_list(&p, 4, 88);
  for (int i = 0; i < p.iSize; i++)
  {
    printf("%3d ", p.iElem[i]);
  }
  printf("\n");

  p.insert_elem_to_link_list(&p, 7, 77);
  for (int i = 0; i < p.iSize; i++)
  {
    printf("%3d ", p.iElem[i]);
  }
  printf("\n");
  return 0;
}