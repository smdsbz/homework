/*
 *  基于链式存储结构的线性表实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/* Page 10 */
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASABLE  -1
#define OVERFLOW    -2

/* 数据元素类型定义 */
typedef int status;
typedef int ElemType; // HACK: 头节点可以用于存放表长

// #define LIST_POOL_SIZE  20

/* Page 28 */
typedef struct _LNode {
  ElemType        data; // 数据域（头节点存放表长）
  struct _LNode  *next; // 下一个节点
} LNode;
typedef LNode *LkList;

/* Page 19 */
status LkList_init(LkList *L);
// status LkList_destroy(LkList L);
// status LkList_clear(LkList L);
// status LkList_empty(LkList L);
status LkList_traverse(LkList L);


/* Main */
int main(int argc, const char *argv[]) {
  LkList L = NULL;

  return 0;
}



status
LkList_init(LkList *L) {
  if (L) { printf("已有挂载的线性表！\n"); return ERROR; }
  *L = (LkList)malloc(sizeof(LNode));  // 申请头节点空间
  if (!L) { printf("内存空间不足！\n"); return ERROR; }
  (*L)->data = 0;    // 头节点存放表长
  (*L)->next = NULL;
  return OK;
}


// status
// LkList_traverse(LkList L)
