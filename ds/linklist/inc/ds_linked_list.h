#ifndef __DS_SINGLY_LINKED_LIST_H__
#define __DS_SINGLY_LINKED_LIST_H__

#include <sys_type.h>
#include <sys_os.h>

#define SIZE_INCREASE_STEP 10

// 线性表
typedef struct _ds_linear_list_s
{
  sys_int *iElem;
  sys_ulong iLength;
  sys_ulong iSize;

  // 函数指针，初始化线性表并指定容量
  sys_bool (*create_linear_list)(struct _ds_linear_list_s *, sys_int);
  
  // 函数指针，用0初始化线性表并指定容量
  sys_bool (*create_linear_list_by_zero)(struct _ds_linear_list_s *, sys_int);

  // 函数指针，用1初始化线性表并指定容量
  sys_bool (*create_linear_list_by_one)(struct _ds_linear_list_s *, sys_int);

  // 函数指针，用指定数据初始化线性表并指定容量
  sys_bool (*create_linear_list_by_value)(struct _ds_linear_list_s *, sys_int, sys_int);

  // 函数指针，用于销毁线性表
  sys_bool (*destory_linear_list)(struct _ds_linear_list_s *);

  // 函数指针，用于在指定位置插入元素到线性表中
  sys_bool (*insert_elem_to_linear_list)(struct sys_int_ds_linear_list_s *, sys_int, sys_int);

  // 函数指针，用于从线性表中的指定位置删除元素并返回被删除的元素
  sys_bool (*delete_elem_from_linear_list)(struct sys_int_ds_linear_list_s *, sys_int, sys_int *);

  // 函数指针，用于获取线性表的当前大小（容量）
  sys_ulong (*get_linear_list_size)(struct sys_int_ds_linear_list_s *);

  // 函数指针，用于获取线性表的当前长度（元素数量）
  sys_ulong (*get_linear_list_length)(struct sys_int_ds_linear_list_s *);

  // 函数指针，用于检查线性表是否为空
  sys_bool (*is_linear_list_empty)(struct sys_int_ds_linear_list_s *);

  // 函数指针，用于排序线性表
  sys_void (*sort_linear_list)(struct sys_int_ds_linear_list_s *, sys_bool);

  // 函数指针，用于合并两个线性表
  sys_bool (*merge_linear_list)(struct sys_int_ds_linear_list_s *, struct sys_int_ds_linear_list_s *, sys_bool);

  // 函数指针，用于打印线性表
  sys_void (*print)(struct sys_int_ds_linear_list_s *);
} LinearList;

// 单向链表
typedef struct _linked_list_node_s
{
  sys_int iData;
  struct _linked_list_node_s *next;
} LinkedList;

// 声明用于初始化线性表的函数
sys_bool linear_list_init(LinearList *pList);

/**
 * 创建一个新的链表节点。
 *
 * @param pData 节点存储的数据。
 * @return 返回新创建的链表节点的指针。如果内存分配失败，返回NULL。
 */
LinkedList *ds_linked_list_create(sys_int pData);

/**
 * 根据索引获取链表中的元素。
 *
 * @param pList 指向链表头节点的指针。
 * @param pIndex 要获取的元素的索引（基于0）。
 * @return 如果索引有效，返回对应元素的值。如果索引无效或链表为空，行为未定义，需要确保调用前链表及索引有效性。
 */
sys_int ds_linked_list_get_elem_by_index(const LinkedList *pList, sys_int pIndex);

/**
 * 在链表的末尾添加一个新的节点。
 *
 * @param pList 指向链表头节点的指针。
 * @param pValue 要添加到链表末尾的值。
 * @return 如果成功添加，返回sys_true；如果内存分配失败，返回sys_false。
 */
sys_bool ds_linked_list_push_back(LinkedList *pList, sys_int pValue);

/**
 * 移除链表末尾的节点。
 *
 * @param pList 指向链表头节点的指针。
 * @return 如果链表非空并成功移除末尾节点，返回sys_true；如果链表为空，返回sys_false。
 */
sys_bool ds_linked_list_pop_back(LinkedList *pList);

/**
 * 在链表的开头添加一个新的节点。
 *
 * @param pList 指向链表头节点指针的指针，允许修改头节点地址。
 * @param pValue 要添加的元素值。
 * @return 如果成功添加，返回sys_true；如果内存分配失败，返回sys_false。
 */
sys_bool ds_linked_list_push_head(LinkedList **pList, sys_int pValue);

/**
 * 移除链表开头的节点。
 *
 * @param pList 指向链表头节点指针的指针，允许修改头节点地址。
 * @return 如果链表非空并成功移除头节点，返回sys_true；如果链表为空，返回sys_false。
 */
sys_bool ds_linked_list_pop_head(LinkedList **pList);

/**
 * 打印链表中所有的元素。
 *
 * @param pList 指向链表头节点的指针。
 */
sys_void ds_linked_list_print(LinkedList *pList);

/**
 * 获取链表的长度。
 *
 * 遍历链表，计算并返回链表中的节点总数。
 *
 * @param pList 指向链表头节点的指针。
 * @return 返回链表的长度。如果链表为空，返回0。
 */
sys_int ds_linked_list_length(const LinkedList *pList);

/**
 * 在链表的指定位置插入一个新值。
 *
 * 如果插入位置是0，则新节点成为新的头节点。
 * 如果插入位置大于链表长度，则不插入节点。
 *
 * @param pList 指向链表头节点指针的指针，允许修改头节点。
 * @param index 插入的目标位置（基于0的索引）。
 * @param value 要插入的新值。
 * @return 成功插入返回1，否则返回0。
 */
sys_int ds_linked_list_insert(LinkedList **pList, sys_int index, sys_int value);

/**
 * 从链表中删除指定位置的节点，并返回被删除节点的数据。
 *
 * @param pList 指向链表头节点指针的指针，以允许修改头节点。
 * @param index 要删除的节点的位置（基于0的索引）。
 * @param outData 指向int的指针，用于存储被删除节点的数据。
 * @return 如果成功删除节点，返回1；如果位置无效或链表为空，返回0。
 */
sys_int ds_linked_list_delete(LinkedList **pList, sys_int index, sys_int *outData);

/**
 * 释放整个链表的内存。
 *
 * @param pList 指向链表头节点的指针。
 */
void ds_linked_list_destory(LinkedList *pList);
#endif //__DS_SINGLY_LINKED_LIST_H__