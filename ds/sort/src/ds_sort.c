#include <ds_sort.h>

sys_void ds_sort_bubble_sort(sys_int *pArray, sys_int pLength, sys_bool pSortRule)
{
  for (sys_int i = 0; i < pLength - 1; i++)
  {
    for (sys_int j = 0; j < pLength - i - 1; j++)
    {
      if (pSortRule)
      {
        if (pArray[j] > pArray[j + 1])
        {
          sys_int temp = pArray[j];
          pArray[j] = pArray[j + 1];
          pArray[j + 1] = temp;
        }
      }
      else
      {
        if (pArray[j] < pArray[j + 1])
        {
          sys_int temp = pArray[j];
          pArray[j] = pArray[j + 1];
          pArray[j + 1] = temp;
        }
      }
    }
  }
}
sys_void ds_sort_select_sort(sys_int *pArray, sys_int pLength, sys_bool pSortRule)
{
  sys_int min_idx;
  for (sys_int i = 0; i < pLength - 1; i++)
  {
    min_idx = i;
    for (sys_int j = i + 1; j < pLength; j++)
    {
      if (pSortRule)
      {
        if (pArray[j] < pArray[min_idx])
        {
          min_idx = j;
        }
      }
      else
      {
        if (pArray[j] > pArray[min_idx])
        {
          min_idx = j;
        }
      }
    }
    sys_int temp = pArray[min_idx];
    pArray[min_idx] = pArray[i];
    pArray[i] = temp;
  }
}