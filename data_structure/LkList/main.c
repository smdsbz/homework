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
#define ERROR       -3  // 与其他有意义值错开，如 LkList_length() 为
                        // 空表时的返回值
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
status LkList_destroy(LkList *L);
status LkList_clear(LkList *L);
status LkList_empty(LkList L);
int LkList_length(LkList L);
status LkList_getElem(LkList L, int idx, ElemType *rst);
status LkList_traverse(LkList L);


/* Main */
int main(int argc, const char *argv[]) {
  LkList L = NULL;
  int op = 1;
  while (op) {
    system("cls"); printf("\n\n");  // PLATFORM: Win only

    /* 操作选择提示 */
    printf("   Menu for Linear Table On Sequence Structure\n");
    printf("-------------------------------------------------\n");
    printf("       1. IntiaList       7. LocateElem\n");
    printf("       2. DestroyList     8. PriorElem\n");
    printf("       3. ClearList       9. NextElem\n");
    printf("       4. ListEmpty      10. ListInsert\n");
    printf("       5. ListLength     11. ListDelete\n");
    printf("       6. GetElem        12. ListTrabverse\n");
    printf("\n");
    printf("--------------------- EXTRA ---------------------\n");
    printf("      13. SaveList       14. LoadList\n");
    printf("      15. SelectList\n");
    printf("\n");
    printf("       0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~12]:");
    scanf("%d", &op);

    /* 执行操作 */
    switch (op) {
      case 1: {
        if (LkList_init(&L) == OK) { printf("线性表创建成功！\n"); }
        else { printf("线性表创建失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 2: {
        if (LkList_destroy(&L) == OK) { printf("线性表销毁成功！\n"); }
        else { printf("线性表销毁失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 3: {
        if (LkList_clear(&L) == OK) { printf("线性表置空成功！\n"); }
        else { printf("线性表置空失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 4: {
        int ret = LkList_empty(L);
        if (ret == TRUE) { printf("线性表为空表。\n"); }
        else if (ret == FALSE) { printf("线性表非空。\n"); }
        else { printf("获取线性表状态失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 5: {
        int ret = LkList_length(L);
        if (ret != ERROR) { printf("线性表表长为 %d 。", ret); }
        else { printf("获取线性表表长失败！\n"); }
        getchar(); getchar();
        break;
      }

      case 10: {
        int key; ElemType val;
        printf("请输入要插入元素的位序： "); scanf("%d", &key);
        printf("请输入要插入元素的值： "); scanf("%d", &val);
        int ret = LkList_insert(L, key, val);
        if (ret == OK) { printf("成功插入元素！\n"); }
        else { printf("插入元素失败！\n"); }
        getchar(); getchar();
        break;
      }

      case 12: {
        if (LkList_traverse(L) == OK) { /* pass */ ; }
        else { /* pass */ ;}
        getchar(); getchar();
        break;
      }
      case 0: { break; }
    } // switch
  } // while


  return 0;
}



status
LkList_init(LkList *L) {
  if (*L) { printf("已有挂载的线性表！\n"); return ERROR; }
  *L = (LkList)malloc(sizeof(LNode));  // 申请头节点空间
  if (!(*L)) { printf("内存空间不足！\n"); return ERROR; }
  (*L)->data = 0;    // 头节点存放表长
  (*L)->next = NULL;
  return OK;
}


status
LkList_destroy(LkList *L) {
  LkList cur = *L;
  if (!cur) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 清理空间
  LkList nxt = cur->next; // 保存被清空元素后继的地址
  for (; nxt; cur = nxt, nxt = nxt->next) { free(cur); }
  // 此时 next == NULL ，已清空到表尾
  *L = NULL;
  return OK;
}


status
LkList_clear(LkList *L) {
  if (LkList_destroy(L) == OK && LkList_init(L) == OK) { return OK; }
  else { return ERROR; }
}


status
LkList_empty(LkList L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (L->next) { return FALSE; }
  else { return TRUE; }
}


int
LkList_length(LkList L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // size_t cnt = 0;
  // for (L = L->next; L; cnt++) { L = L->next; }  // 跳过表头节点
  // return (int)cnt;
  return L->data; // HACK: 表头节点存放表长
}


status
LkList_getElem(LkList L, int idx, ElemType *rst) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (idx < 1 || idx > LkList_length(L)) {
    printf("输入的位序大小不合法！\n");
    return ERROR;
  }
  for (; idx > 0; idx--) { L = L->next; }
  *rst = L->data;
  return OK;
}


status
LkList_insert(LkList L, int key, ElemType val) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if ((LkList_length(L) == 0 && key != 1)
      || (LkList_length(L) != 0
          && (key < 1 || key > LkList_length(L)))) {
    printf("输入的位序大小不合法！\n");
    return ERROR;
  }
  // 先修改表长，下面 L 不再指向表头节点
  L->data += 1;
  // 获取要添加位置元素的前驱（由 L 指向）
  for (; key > 1; key--) { L = L->next; }
  // 为新的数据元素分配空间
  LkList new_node = (LkList)malloc(sizeof(LNode));
  if (!new_node) { printf("内存空间不足！\n"); return ERROR; }
  // 将新节点加入链表
  new_node->next = L->next;
  L->next = new_node;
  // 给新元素赋值
  new_node->data = val;
  return OK;
}


status
LkList_traverse(LkList L) {
  if (!L) { printf("线性表还没有被创建！\n");  return ERROR; }
  // 遍历并输出
  printf(" ------------- All Elements -------------\n    ");
  for (L = L->next; L; L = L->next) {
    printf("%d ", L->data);
  }
  printf("\n ----------------- End ------------------\n");
  return OK;
}
