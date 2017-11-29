/*
 *  基于链式存储结构的线性表实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


/****************************************************

          ░░░░░░░█▐▓▓░████▄▄▄█▀▄▓▓▓▌█
          ░░░░░▄█▌▀▄▓▓▄▄▄▄▀▀▀▄▓▓▓▓▓▌█
          ░░░▄█▀▀▄▓█▓▓▓▓▓▓▓▓▓▓▓▓▀░▓▌█
          ░░█▀▄▓▓▓███▓▓▓███▓▓▓▄░░▄▓▐█▌
          ░█▌▓▓▓▀▀▓▓▓▓███▓▓▓▓▓▓▓▄▀▓▓▐█
          ▐█▐██▐░▄▓▓▓▓▓▀▄░▀▓▓▓▓▓▓▓▓▓▌█▌
          █▌███▓▓▓▓▓▓▓▓▐░░▄▓▓███▓▓▓▄▀▐█
          █▐█▓▀░░▀▓▓▓▓▓▓▓▓▓██████▓▓▓▓▐█
          ▌▓▄▌▀░▀░▐▀█▄▓▓██████████▓▓▓▌█▌
          ▌▓▓▓▄▄▀▀▓▓▓▀▓▓▓▓▓▓▓▓█▓█▓█▓▓▌█▌
          █▐▓▓▓▓▓▓▄▄▄▓▓▓▓▓▓█▓█▓█▓█▓▓▓▐█

*****************************************************/



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

#define LIST_POOL_SIZE  20

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
status LkList_insert(LkList L, int i, ElemType e);
status LkList_delete(LkList L, int i, ElemType *e);
int LkList_locateElem(LkList L, ElemType e);
status LkList_priorElem(LkList L, ElemType cur, ElemType *pre_e);
status LkList_nextElem(LkList L, ElemType cur, ElemType *next_e);
status LkList_writeToFile(FILE *fp, LkList L);
status LkList_readFromFile(FILE *fp, LkList *L);
status LkList_selectList(LkList *L, LkList pool[], int *cur, int tgt);


/* Main */
int main(int argc, const char *argv[]) {
  LkList list_pool[LIST_POOL_SIZE] = { NULL };
  int current_list = 0;
  LkList L = list_pool[current_list];

  int op = 1;
  while (op) {
    system("clear"); printf("\n\n");  // PLATFORM: *nix / PowerShell

    /* 操作选择提示 */
    printf("   Menu for Linear Table On Linked Structure\n");
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
    printf("    请选择你的操作[0~15]:");
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
      case 6: {
        int index; ElemType result;
        printf("请输入元素位序： "); scanf("%d", &index);
        int ret = LkList_getElem(L, index, &result);
        if (ret == OK) { printf("该元素的值为 %d 。\n", result); }
        else { printf("获取元素值失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 7: {
        int target;
        printf("请输入要查找元素的值： "); scanf("%d", &target);
        int ret = LkList_locateElem(L, target);
        if (ret == 0) { printf("该元素不在线性表中！\n"); }
        else { printf("该元素在线性表中的位序为 %d 。\n", ret); }
        getchar(); getchar();
        break;
      }
      case 8: {
        int current, previous;
        printf("请输入目标元素的直接后继的值： "); scanf("%d", &current);
        int ret = LkList_priorElem(L, current, &previous);
        if (ret == OK) { printf("目标元素值为 %d 。\n", previous); }
        else { printf("获取目标元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 9: {
        int current, next;
        printf("请输入目标元素的直接前驱的值： "); scanf("%d", &current);
        int ret = LkList_nextElem(L, current, &next);
        if (ret == OK) { printf("目标元素值为 %d 。\n", next); }
        else { printf("获取目标元素失败！\n"); }
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
      case 11: {
        int key; ElemType val;
        printf("请输入要删除元素的位序： "); scanf("%d", &key);
        int ret = LkList_delete(L, key, &val);
        if (ret == OK) { printf("成功删除元素，其值为 %d 。\n", val); }
        else { printf("删除元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 12: {
        if (LkList_traverse(L) == OK) { /* pass */ ; }
        else { /* pass */ ;}
        getchar(); getchar();
        break;
      }
      case 13: {
        FILE *fp; char filename[100];
        printf("请输入文件名： "); scanf("%s", filename);
        if ((fp = fopen(filename, "w")) == NULL) {
          printf("不能够创建文件！\n");
        } else {
          if (LkList_writeToFile(fp, L) == OK) {
            printf("成功写入文件！\n");
          } else { printf("写入文件失败！\n"); }
        }
        fclose(fp);
        getchar(); getchar();
        break;
      }
      case 14: {
        FILE *fp; char filename[100];
        printf("请输入文件名： "); scanf("%s", filename);
        if ((fp = fopen(filename, "r")) == NULL) {
          printf("不能够读取文件！\n");
        } else {
          if (LkList_readFromFile(fp, &L) == OK) {
            printf("成功从文件读取！\n");
          } else { printf("从文件读取失败！\n"); }
        }
        fclose(fp);
        getchar(); getchar();
        break;
      }
      case 15: {
        int index;
        printf("请输入要操作的表的位序： "); scanf("%d", &index);
        if (LkList_selectList(&L, list_pool, &current_list, index) == OK) {
          printf("切换工作表成功！\n");
        } else { printf("切换工作表失败！\n"); }
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
LkList_delete(LkList L, int key, ElemType *val) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (key < 1 || key > L->data) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  // 更改表长
  L->data -= 1;
  // 删除元素
  // - 寻找前驱
  LkList prev = L;
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


int
LkList_locateElem(LkList L, ElemType val) {
  // 合法性检测
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 遍历表寻找符合条件的元素
  int idx = 1;
  for (L = L->next; L && val != L->data; L = L->next) { idx++; }
  if (!L) { return 0; } // 遍历一遍没有找到符合条件的元素
  return idx;
}


status
LkList_priorElem(LkList L, ElemType cur_e, ElemType *pre_e) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 获取 `cur_e` 位序
  int cur_idx = LkList_locateElem(L, cur_e);
  if (cur_idx == 0) {
    printf("未找到元素值为输入值的元素！\n");
    return ERROR;
  }
  if (cur_idx == 1) {
    printf("元素值为输入值的元素是表中的第一个元素！\n");
    return ERROR;
  } else {  // 正常 - cur_idx >= 2
    // 遍历到该元素的前驱
    for (; cur_idx > 1; cur_idx--) { L = L->next; }
    *pre_e = L->data;
    return OK;
  }
}


status
LkList_nextElem(LkList L, ElemType cur_e, ElemType *nxt_e) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 获取 `cur_e` 位序
  int cur_idx = LkList_locateElem(L, cur_e);
  if (cur_idx == 0) {
    printf("未找到元素值为输入值的元素！\n");
    return ERROR;
  }
  if (cur_idx == L->data) {
    printf("元素值为输入值的元素是表中的最后一个元素！\n");
    return ERROR;
  } else {  // 正常
    // 遍历到该元素的后继
    for (; cur_idx >= 0; cur_idx--) { L = L->next; }
    *nxt_e = L->data;
    return OK;
  }
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


status
LkList_writeToFile(FILE *fp, LkList L) {
  if (!fp) { return ERROR; }
  if (!L) { printf("线性表还没有创建！\n"); return ERROR; }
  for (; L; L = L->next) {
    fwrite(&L->data, sizeof(ElemType), 1, fp);
  }
  return OK;
}


status
LkList_readFromFile(FILE *fp, LkList *L) {
  if (!fp) { return ERROR; }
  if ((*L)) { printf("已有挂载的线性表！\n"); return ERROR; }
  // 获取文件中表长
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp) / sizeof(ElemType) - 1; // 去掉表头节点
  fseek(fp, 0, SEEK_SET);
  // - 读取线性表，一次读一个
  // -- 读取表头，挂载线性表
  *L = (LkList)malloc(sizeof(LNode));
  if (!(*L)) { return ERROR; }
  fread(&( (*L)->data ), sizeof(ElemType), 1, fp);
  // -- 检查表头数据是否为表长
  if ((*L)->data != filesize) {
    printf("文件损坏！\n");
    free(*L); *L = NULL;
    return ERROR;
  }
  // -- 读取剩余部分
  LkList new_node = *L, prev_node;
  while (!feof(fp)) {
    prev_node = new_node;
    new_node->next = (LkList)malloc(sizeof(LNode));
    if (!new_node->next) { return ERROR; }
    new_node = new_node->next; new_node->next = NULL;
    fread(&new_node->data, sizeof(ElemType), 1, fp);
  }
  // 由于用 EOF 判断，所以会多读一个 0 进来，要删掉
  free(prev_node->next); prev_node->next = NULL;
  return OK;
}


status
LkList_selectList(LkList *L, LkList pool[], int *cur, int tgt) {
  if (tgt < 1 || tgt > LIST_POOL_SIZE) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  pool[*cur] = *L;
  *L = pool[tgt - 1];
  *cur = tgt - 1;
  return OK;
}
