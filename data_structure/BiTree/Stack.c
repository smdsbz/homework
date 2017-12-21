/*
 *  辅助栈数据结构定义
 *
 *  重用 LkList 代码
 *  链表中第一个元素为栈顶，最后一个元素为栈底
 *    ---- by U201610136 朱晓光 校际交流1601班
 */

#include <stdio.h>
#include <stdlib.h>

#include "MACROS.h"
#include "BiTree.h"
#include "Stack.h"


/*
 * 函数名称：Stack_init
 * 函数参数：栈挂载点指针 L
 * 函数功能：初始化辅助栈，并令 L 指向该栈
 * 返回值：  成功初始化返回 OK，否则返回 ERROR
 */
status
Stack_init(Stack *L) {
  if (*L) { printf("已有挂载的线性表！\n"); return ERROR; }
  *L = (Stack)malloc(sizeof(SNode));  // 申请头节点空间
  if (!(*L)) { printf("内存空间不足！\n"); return ERROR; }
  (*L)->data = NULL;    // 头节点存放表长
  (*L)->next = NULL;
  return OK;
}


/*
 * 函数名称：Stack_destroy
 * 函数参数：栈指针 L
 * 函数功能：销毁栈 L，释放其空间
 * 返回值：  成功销毁返回 OK，否则返回 ERROR
 */
status
Stack_destroy(Stack *L) {
  Stack cur = *L;
  if (!cur) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 清理空间
  Stack nxt = cur->next; // 保存被清空元素后继的地址
  for (; nxt; cur = nxt, nxt = nxt->next) { free(cur); }
  // 此时 nxt == NULL ，cur 指向表尾
  free(cur);  // 释放表尾所占空间
  *L = NULL;
  return OK;
}


/*
 * 函数名称：Stack_empty
 * 函数参数：栈 L
 * 函数功能：判断 L 是否为空栈
 * 返回值：  若 L 是空栈则返回 TRUE，否则返回 FALSE
 */
status
Stack_empty(Stack L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (L->next) { return FALSE; }
  else { return TRUE; }
}


/*
 * 函数名称：Stack_length
 * 函数参数：栈 L
 * 函数功能：返回 L 的长度
 * 返回值：  返回栈 L 中元素的个数
 */
size_t
Stack_length(Stack L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  size_t ret = 0;
  for (L = L->next; L; L = L->next) { ret++; }
  return ret;
}


/*
 * 函数名称：Stack_getElem
 * 函数参数：栈 L，目标位序 idx，结果带回指针 rst
 * 函数功能：将 L 中第 idx 个元素赋值给 rst 带回
 * 返回值：  成功获取元素返回 OK，否则返回 ERROR
 */
status
Stack_getElem(Stack L, int idx, BiTree *rst) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (idx < 1 || idx > Stack_length(L)) {
    printf("输入的位序大小不合法！\n");
    return ERROR;
  }
  for (; idx > 0; idx--) { L = L->next; }
  *rst = L->data;
  return OK;
}


/*
 * 函数名称：Stack_top
 * 函数参数：栈 L
 * 函数功能：返回 L 的栈顶元素
 * 返回值：  栈 L 的栈顶元素
 */
BiTree
Stack_top(Stack L) {
  BiTree ret = NULL;
  Stack_getElem(L, 1, &ret);
  return ret;
}


/*
 * 函数名称：Stack_insert
 * 函数参数：栈 L，插入位置 key，插入值 val
 * 函数功能：在 L 的第 key 个位置之前插入值为 val 的节点
 * 返回值：  成功插入返回 OK，否则返回 ERROR
 */
status
Stack_insert(Stack L, int key, BiTree val) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if ((Stack_length(L) == 0 && key != 1)
      || (Stack_length(L) != 0
          && (key < 1 || key > Stack_length(L)))) {
    printf("输入的位序大小不合法！\n");
    return ERROR;
  }
  // 获取要添加位置元素的前驱（由 L 指向）
  for (; key > 1; key--) { L = L->next; }
  // 为新的数据元素分配空间
  Stack new_node = (Stack)malloc(sizeof(SNode));
  if (!new_node) { printf("内存空间不足！\n"); return ERROR; }
  // 将新节点加入链表
  new_node->next = L->next;
  L->next = new_node;
  // 给新元素赋值
  new_node->data = val;
  return OK;
}


/*
 * 函数名称：Stack_push
 * 函数参数：栈 L，压栈元素 val
 * 函数功能：将值为 val 的节点压入栈 L 中
 * 返回值：  成功压栈返回 OK，否则返回 ERROR
 */
status
Stack_push(Stack L, BiTree val) {
  if (!L) { return ERROR; }
  return Stack_insert(L, 1, val);
}


/*
 * 函数名称：Stack_append
 * 函数参数：栈 L，入队元素 val
 * 函数功能：将栈 L 看作队列，把 val 添加到队尾
 * 返回值：  成功入队返回 OK，否则返回 ERROR
 */
status
Stack_append(Stack L, BiTree val) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  while (L->next) { L = L->next; }
  if ( (L->next = (Stack)malloc(sizeof(SNode))) == NULL ) {
    printf("内存空间不足！\n"); return ERROR;
  }
  L->next->data = val; L->next->next = NULL;
  return OK;
}


/*
 * 函数名称：Stack_delete
 * 函数参数：栈 L，删除元素位序 key，结果带回指针 val
 * 函数功能：将栈 L 中第 key 个元素删除，并把其值赋给 val 带回
 * 返回值：  成功删除返回 OK，否则返回 ERROR
 */
status
Stack_delete(Stack L, int key, BiTree *val) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (key < 1 || key > Stack_length(L)) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  // 删除元素
  // - 寻找前驱
  Stack prev = L;
  for (; key > 1; key--) { prev = prev->next; }
  // - 值带出
  *val = prev->next->data;
  // - 释放空间
  L = prev->next->next; // 传进来的表头地址已经不会再用了
  free(prev->next);
  // - 重新链接链表
  prev->next = L;
  return OK;
}


/*
 * 函数名称：Stack_pop
 * 函数参数：栈 L
 * 函数功能：删除并返回栈 L 的栈顶元素
 * 返回值：  成功出栈返回出栈元素，否则返回 NULL
 */
BiTree
Stack_pop(Stack L) {
  BiTree ret = NULL;
  Stack_delete(L, 1, &ret);
  return ret; // 包含返回 NULL 的情况
}
