#include <ds_linked_list.h>

sys_bool ds_init_linear_list(LinearList *pList, sys_int iSize)
{
  pList->iElem = (sys_int *)sys_os_malloc(iSize * sizeof(sys_int));

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
sys_bool ds_init_linear_list_by_zero(LinearList *pList, sys_int iSize)
{
  pList->iElem = (sys_int *)sys_os_malloc(iSize * sizeof(sys_int));

  if (pList->iElem == NULL)
  {
    pList->iElem = NULL;
    pList->iLength = 0;
    pList->iSize = 0;
    return sys_false;
  }

  pList->iLength = iSize;
  pList->iSize = iSize;

  for(sys_int i = 0; i< iSize; i++)
  {
    pList->iElem[i] = 0;
  }
  return sys_true;
}
sys_bool ds_init_linear_list_by_one(LinearList *pList, sys_int iSize)
{
  pList->iElem = (sys_int *)sys_os_malloc(iSize * sizeof(sys_int));

  if (pList->iElem == NULL)
  {
    pList->iElem = NULL;
    pList->iLength = 0;
    pList->iSize = 0;
    return sys_false;
  }

  pList->iLength = iSize;
  pList->iSize = iSize;

  for(sys_int i = 0; i< iSize; i++)
  {
    pList->iElem[i] = 1;
  }
  return sys_true;
}
sys_bool ds_init_linear_list_by_value(LinearList *pList, sys_int iSize, sys_int pValue)
{
  pList->iElem = (sys_int *)sys_os_malloc(iSize * sizeof(sys_int));

  if (pList->iElem == NULL)
  {
    pList->iElem = NULL;
    pList->iLength = 0;
    pList->iSize = 0;
    return sys_false;
  }

  pList->iLength = iSize;
  pList->iSize = iSize;

  for(sys_int i = 0; i< iSize; i++)
  {
    pList->iElem[i] = pValue;
  }
  return sys_true;
}
sys_bool ds_destory_linear_list(LinearList *pList)
{
  if (pList == NULL || pList->iElem == NULL)
  {
    return sys_false;
  }
  sys_os_free(pList->iElem);
  return sys_true;
}
sys_bool ds_insert_elem_to_linear_list(LinearList *pList, sys_int pPosition, sys_int pValue)
{
  // 检查插入位置是否合法
  if (pPosition < 1 || pPosition > pList->iSize + 1)
  {
    return sys_false;
  }

  // 检查空间是否已满
  if (pList->get_linear_list_length(pList) >= pList->get_linear_list_size(pList))
  {
    sys_int *ptr = (sys_int *)sys_os_realloc(pList->iElem, (pList->get_linear_list_size(pList) + SIZE_INCREASE_STEP) * sizeof(sys_int));

    if (ptr == NULL)
    {
      return sys_false;
    }
    pList->iElem = ptr;
    pList->iSize += SIZE_INCREASE_STEP;
  }
  //INFO("addr=0x%x, size=%d,length=%d\n", pList->iElem, pList->iSize, pList->iLength);

  sys_int *pos = &(pList->iElem[pPosition - 1]);

  for (sys_int *pointer = &(pList->iElem[pList->get_linear_list_length(pList) - 1]); pointer >= pos; pointer--)
  {
    *(pointer + 1) = *pointer;
  }

  *pos = pValue;
  pList->iLength++;

  return sys_true;
}
sys_bool ds_delete_elem_from_linear_list(LinearList *pList, sys_int pPosition, sys_int *pValue)
{
  if (pPosition < 1 || pPosition > pList->get_linear_list_length(pList))
  {
    return sys_false;
  }

  sys_int *pos = &(pList->iElem[pPosition - 1]);

  *pValue = *pos;

  for (sys_int *pointer = pos; pointer <= &(pList->iElem[pList->get_linear_list_length(pList) - 1]); pointer++)
  {
    *pointer = *(pointer + 1);
  }
  pList->iLength--;
  return sys_true;
}
sys_ulong ds_get_linear_list_size(LinearList *pList)
{
  return pList->iSize;
}
sys_ulong ds_get_linear_list_length(LinearList *pList)
{
  return pList->iLength;
}
sys_bool ds_is_linear_list_empty(LinearList *pList)
{
  if (pList->get_linear_list_length(pList) == 0)
  {
    return sys_false;
  }
  return sys_true;
}
sys_void ds_sort_linear_list(LinearList *pList, sys_bool pSortFlag)
{
  for (int i = 0; i < pList->get_linear_list_length(pList) - 1; i++)
  {
    for (int j = 0; j < pList->get_linear_list_length(pList) - i - 1; j++)
    {
      // from max to min
      if (pSortFlag)
      {
        if (pList->iElem[j] < pList->iElem[j + 1])
        {
          sys_int temp = pList->iElem[j];
          pList->iElem[j] = pList->iElem[j + 1];
          pList->iElem[j + 1] = temp;
        }
      }
      // from min to max
      else
      {
        if (pList->iElem[j] > pList->iElem[j + 1])
        {
          sys_int temp = pList->iElem[j];
          pList->iElem[j] = pList->iElem[j + 1];
          pList->iElem[j + 1] = temp;
        }
      }
    }
  }
}
sys_bool ds_merge_linear_list(LinearList *pList_dst, LinearList *pList_src, sys_bool pSortFlag)
{
  if (pList_dst->get_linear_list_size(pList_dst) < pList_dst->get_linear_list_length(pList_dst) + pList_src->get_linear_list_length(pList_src))
  {
    sys_int *ptr = (sys_int *)sys_os_realloc(pList_dst->iElem, (pList_dst->get_linear_list_length(pList_dst) + pList_src->get_linear_list_length(pList_src)) * sizeof(sys_int));

    if (ptr == NULL)
    {
      return sys_false;
    }
    pList_dst->iElem = ptr;
    pList_dst->iSize = pList_dst->get_linear_list_length(pList_dst) + pList_src->get_linear_list_length(pList_src);
  }

  for (sys_int i = pList_dst->get_linear_list_length(pList_dst), j = 0; i < pList_dst->get_linear_list_size(pList_dst) && j < pList_src->get_linear_list_length(pList_src); i++, j++)
  {
    pList_dst->iElem[i] = pList_src->iElem[j];
  }
  pList_dst->iLength += pList_src->get_linear_list_length(pList_src);

  if (pList_dst->sort_linear_list != NULL)
  {
    pList_dst->sort_linear_list(pList_dst, pSortFlag);
  }
  return sys_true;
}
sys_void ds_linear_list_print(LinearList *pList)
{
  PRINTK("linear list data : ");
  for(sys_int i=0; i<pList->get_linear_list_length(pList); i++)
  {
    PRINTK("%d ", pList->iElem[i]);
  }
  PRINTK("\n");
}
LinkedList *ds_linked_list_create(sys_int pData)
{
  LinkedList *pList = (LinkedList *)sys_os_malloc(sizeof(LinkedList));
  if (pList == NULL)
  {
    return NULL;
  }
  pList->next = NULL;
  pList->iData = pData;

  return pList;
}
sys_int ds_linked_list_get_elem_by_index(const LinkedList *pList, sys_int pIndex)
{
  int temp = 0;

  LinkedList *pointer = pList;
  while (pointer->next)
  {
    if (temp == pIndex)
    {
      return pointer->iData;
    }
    pointer = pointer->next;
    temp++;
  }
  return -1;
}
sys_bool ds_linked_list_push_back(LinkedList *pList, sys_int pValue)
{
  LinkedList *newNode = ds_linked_list_create(pValue);
  if (newNode == NULL)
  {
    return sys_false;
  }

  if (pList == NULL)
  {
    pList = newNode;
    return sys_true;
  }
  else
  {
    LinkedList *iterator = pList;

    while (iterator->next != NULL)
    {
      iterator = iterator->next;
    }

    iterator->next = newNode;
  }
  return sys_true;
}
sys_bool ds_linked_list_pop_back(LinkedList *pList)
{
  if (pList == NULL)
  {
    return sys_false;
  }
  if (pList->next == NULL)
  {
    sys_os_free(pList);
    pList = NULL;
    return sys_true;
  }

  LinkedList *iterator = pList;

  while (iterator->next->next != NULL)
  {
    iterator = iterator->next;
  }
  sys_os_free(iterator->next);
  iterator->next = NULL;

  return sys_true;
}
sys_bool ds_linked_list_push_head(LinkedList **pList, sys_int pValue)
{
  if (pList == NULL)
  {
    return sys_false;
  }

  LinkedList *newNode = ds_linked_list_create(pValue);
  if (newNode == NULL)
  {
    return sys_false;
  }

  if (*pList == NULL)
  {
    *pList = newNode;
  }
  else
  {
    newNode->next = *pList;
    *pList = newNode;
  }
  return sys_true;
}
sys_bool ds_linked_list_pop_head(LinkedList **pList)
{
  if (pList == NULL || *pList == NULL)
  {
    return sys_false;
  }

  LinkedList *tempNode = *pList;
  *pList = (*pList)->next;
  sys_os_free(tempNode);

  return sys_true;
}

sys_void ds_linked_list_print(LinkedList *pList)
{
  while (pList != NULL)
  {
    PRINTK("%d ", pList->iData);
    pList = pList->next;
  }
  PRINTK("\n");
}
sys_int ds_linked_list_length(const LinkedList *pList)
{
  sys_int length = 0;
  const LinkedList *current = pList;

  while (current != NULL)
  {
    length++;
    current = current->next;
  }

  return length;
}
sys_int ds_linked_list_insert(LinkedList **pList, sys_int index, sys_int value)
{
  if (index < 0)
  {
    return 0;
  }

  LinkedList *newNode = ds_linked_list_create(value);
  if (newNode == NULL)
  {
    return 0;
  }

  if (index == 0)
  {
    newNode->next = *pList;
    *pList = newNode;
    return 1;
  }

  LinkedList *current = *pList;
  for (sys_int i = 0; current != NULL && i < index - 1; i++)
  {
    current = current->next;
  }

  if (current == NULL)
  {
    sys_os_free(newNode);
    return 0;
  }

  newNode->next = current->next;
  current->next = newNode;

  return 1;
}

sys_int ds_linked_list_delete(LinkedList **pList, sys_int index, sys_int *outData)
{
  // 检查链表是否为空或位置是否有效
  if (*pList == NULL || index < 0)
  {
    return 0;
  }

  LinkedList *temp, *current = *pList;

  // 处理删除头节点的情况
  if (index == 0)
  {
    *pList = current->next;          // 更新头节点
    *outData = current->iData;        // 返回被删除节点的数据
    sys_os_free(current);            // 释放被删除节点的内存
    return 1;
  }

  // 查找目标位置的前一个节点
  for (sys_int i = 0; i < index - 1 && current != NULL; i++)
  {
    current = current->next;
  }

  // 检查是否找到有效的前一个节点
  if (current == NULL || current->next == NULL)
  {
    return 0; // 位置无效
  }

  // 更新链接以跳过要删除的节点
  temp = current->next;       // 指向要删除的节点
  current->next = temp->next; // 跳过要删除的节点
  *outData = temp->iData;      // 返回被删除节点的数据

  sys_os_free(temp);          // 释放被删除节点的内存
  return 1;
}

sys_void ds_linked_list_destory(LinkedList *pList)
{
  LinkedList *current = pList;
  while (current != NULL)
  {
    LinkedList *temp = current;
    current = current->next;
    sys_os_free(temp);
  }
}
sys_bool linear_list_init(LinearList *pList)
{
  pList->create_linear_list = ds_init_linear_list;
  pList->create_linear_list_by_zero = ds_init_linear_list_by_zero;
  pList->create_linear_list_by_one = ds_init_linear_list_by_one;
  pList->create_linear_list_by_value = ds_init_linear_list_by_value;
  pList->destory_linear_list = ds_destory_linear_list;
  pList->insert_elem_to_linear_list = ds_insert_elem_to_linear_list;
  pList->delete_elem_from_linear_list = ds_delete_elem_from_linear_list;
  pList->get_linear_list_length = ds_get_linear_list_length;
  pList->get_linear_list_size = ds_get_linear_list_size;
  pList->is_linear_list_empty = ds_is_linear_list_empty;
  pList->sort_linear_list = ds_sort_linear_list;
  pList->merge_linear_list = ds_merge_linear_list;
  pList->print = ds_linear_list_print;
  return sys_true;
}