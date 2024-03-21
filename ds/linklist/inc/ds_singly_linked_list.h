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

  sys_bool (*init_link_list)(struct _ds_singly_linked_list_s *, sys_int);
  sys_bool (*insert_elem_to_link_list)(struct _ds_singly_linked_list_s *, sys_int, sys_char);
  sys_bool (*delete_elem_from_link_list)(struct _ds_singly_linked_list_s *, sys_int, sys_char *);
} SLinkedList;

sys_bool link_list_init(struct _ds_singly_linked_list_s *pList);

sys_bool ds_init_linked_list(SLinkedList *pList, sys_int iSize);
sys_bool ds_insert_elem_to_link_list(SLinkedList *pList, sys_int pPosition, sys_char pValue);
sys_bool ds_delete_elem_from_link_list(SLinkedList *pList, sys_int pPosition, sys_char *pValue);
#endif //__DS_SINGLY_LINKED_LIST_H__