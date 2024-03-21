#include <ds_singly_linked_list.h>

sys_bool ds_init_linked_list(SLinkedList *pList, sys_int iSize)
{
  pList->iElem = (sys_char *)sys_os_malloc(iSize * sizeof(sys_char));

  if (pList->iElem == NULL)
  {
    pList->iElem = NULL;
    pList->iLength = 0;
    pList->iSize = 0;
    return sys_false;
  }

  pList->iLength = 0;
  pList->iSize = iSize;

  return sys_true;
}
sys_bool ds_insert_elem_to_link_list(SLinkedList *pList, sys_int pPosition, sys_char pValue)
{
  // 检查插入位置是否合法
  if (pPosition < 1 || pPosition > pList->iSize + 1)
  {
    return sys_false;
  }

  // 检查空间是否已满
  if (pList->iLength >= pList->iSize)
  {
    sys_char *ptr = (sys_char *)sys_os_realloc(pList->iElem, (pList->iSize + SIZE_INCREASE_STEP) * sizeof(sys_char));

    if (ptr == NULL)
    {
      return sys_false;
    }
    pList->iElem = ptr;
    pList->iSize += SIZE_INCREASE_STEP;
  }
  INFO("addr=0x%x, size=%d,length=%d\n", pList->iElem, pList->iSize, pList->iLength);

  sys_char *pos = &(pList->iElem[pPosition - 1]);

  for (sys_char *pointer = &(pList->iElem[pList->iLength - 1]); pointer >= pos; pointer--)
  {
    *(pointer + 1) = *pointer;
  }

  *pos = pValue;
  pList->iLength++;

  return sys_true;
}
ds_delete_elem_from_link_list(SLinkedList *pList, sys_int pPosition, sys_char *pValue)
{

}

sys_bool init(struct _ds_singly_linked_list_s *pList)
{
  pList->init_link_list = ds_init_linked_list;
  pList->insert_elem_to_link_list = ds_insert_elem_to_link_list;
  pList->delete_elem_from_link_list = ds_delete_elem_from_link_list;
  return sys_true;
}