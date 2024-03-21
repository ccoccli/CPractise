#ifndef __DS_SINGLY_LINKED_LIST_H__
#define __DS_SINGLY_LINKED_LIST_H__

#include <sys_type.h>
#include <sys_os.h>

#define SIZE_INCREASE_STEP 10

typedef struct _ds_singly_linked_list_s
{
  sys_char *iElem;
  sys_ulong iLength;
  sys_ulong iSize;

  sys_bool (*init_link_list)(struct _ds_singly_linked_list_s*, sys_int);
  sys_bool (*insert_elem_to_link_list)(struct _ds_singly_linked_list_s*, sys_int, sys_char);
  sys_bool (*delete_elem_from_link_list)(struct _ds_singly_linked_list_s*, sys_int, sys_char*);
}SLinkedList;

sys_bool init(struct _ds_singly_linked_list_s *pList);
#endif //__DS_SINGLY_LINKED_LIST_H__