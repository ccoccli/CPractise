#ifndef __DS_SORT_H__
#define __DS_SORT_H__

#include <sys_type.h>
#include <sys_os.h>
#include <sys_log.h>

/**
 * @brief 冒泡排序函数，对整型数组进行排序
 *
 * @param pArray 要排序的整型数组的指针
 * @param pLength 数组的长度
 * @param pSortRule 排序规则, 从小到大或从大到小
 * @return void
 */
sys_void ds_sort_bubble_sort(sys_int *pArray, sys_int pLength, sys_bool pSortRule);

/**
 * @brief 选择排序函数，对整型数组进行排序
 * 
 * @param pArray 要排序的整型数组的指针
 * @param pLength 数组的长度
 * @param pSortRule 排序规则，为真时按升序排列，为假时按降序排列
 * @return void
 */
sys_void ds_sort_select_sort(sys_int *pArray, sys_int pLength, sys_bool pSortRule);
#endif //__DS_SORT_H__