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
#define ERROR       -3  // 与其他有意义值错开，如 ListLength() 为
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
status IntiaList(LkList *L);
status DestroyList(LkList *L);
status ClearList(LkList *L);
status ListEmpty(LkList L);
int ListLength(LkList L);
status GetElem(LkList L, int idx, ElemType *rst);
status ListTrabverse(LkList L);
status ListInsert(LkList L, int i, ElemType e);
status ListDelete(LkList L, int i, ElemType *e);
int LocateElem(LkList L, ElemType e);
status PriorElem(LkList L, ElemType cur, ElemType *pre_e);
status NextElem(LkList L, ElemType cur, ElemType *next_e);
status SaveList(FILE *fp, LkList L);
status LoadList(FILE *fp, LkList *L);
status SelectList(LkList *L, LkList pool[], int *cur, int tgt);


/* Main */
int main(int argc, const char *argv[]) {
  LkList list_pool[LIST_POOL_SIZE] = { NULL };
  int current_list = 0;
  LkList L = list_pool[current_list];

  int op = 1;
  while (op) {
    system("cls"); printf("\n\n");  // PLATFORM: Win

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
        if (IntiaList(&L) == OK) { printf("线性表创建成功！\n"); }
        else { printf("线性表创建失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 2: {
        if (DestroyList(&L) == OK) { printf("线性表销毁成功！\n"); }
        else { printf("线性表销毁失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 3: {
        if (ClearList(&L) == OK) { printf("线性表置空成功！\n"); }
        else { printf("线性表置空失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 4: {
        int ret = ListEmpty(L);
        if (ret == TRUE) { printf("线性表为空表。\n"); }
        else if (ret == FALSE) { printf("线性表非空。\n"); }
        else { printf("获取线性表状态失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 5: {
        int ret = ListLength(L);
        if (ret != ERROR) { printf("线性表表长为 %d 。\n", ret); }
        else { printf("获取线性表表长失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 6: {
        int index; ElemType result;
        printf("请输入元素位序： "); scanf("%d", &index);
        int ret = GetElem(L, index, &result);
        if (ret == OK) { printf("该元素的值为 %d 。\n", result); }
        else { printf("获取元素值失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 7: {
        int target;
        printf("请输入要查找元素的值： "); scanf("%d", &target);
        int ret = LocateElem(L, target);
        if (ret == 0) { printf("该元素不在线性表中！\n"); }
        else { printf("该元素在线性表中的位序为 %d 。\n", ret); }
        getchar(); getchar();
        break;
      }
      case 8: {
        int current, previous;
        printf("请输入目标元素的直接后继的值： "); scanf("%d", &current);
        int ret = PriorElem(L, current, &previous);
        if (ret == OK) { printf("目标元素值为 %d 。\n", previous); }
        else { printf("获取目标元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 9: {
        int current, next;
        printf("请输入目标元素的直接前驱的值： "); scanf("%d", &current);
        int ret = NextElem(L, current, &next);
        if (ret == OK) { printf("目标元素值为 %d 。\n", next); }
        else { printf("获取目标元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 10: {
        int key; ElemType val;
        printf("请输入要插入元素的位序： "); scanf("%d", &key);
        printf("请输入要插入元素的值： "); scanf("%d", &val);
        int ret = ListInsert(L, key, val);
        if (ret == OK) { printf("成功插入元素！\n"); }
        else { printf("插入元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 11: {
        int key; ElemType val;
        printf("请输入要删除元素的位序： "); scanf("%d", &key);
        int ret = ListDelete(L, key, &val);
        if (ret == OK) { printf("成功删除元素，其值为 %d 。\n", val); }
        else { printf("删除元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 12: {
        if (ListTrabverse(L) == OK) { /* pass */ ; }
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
          if (SaveList(fp, L) == OK) {
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
        if ((fp = fopen(filename, "rb")) == NULL) {
          printf("不能够读取文件！\n");
        } else {
          if (LoadList(fp, &L) == OK) {
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
        if (SelectList(&L, list_pool, &current_list, index) == OK) {
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


/*
 * 函数名称：IntiaList
 * 函数参数：线性表 L 的指针
 * 函数功能：构造一个空的线性表
 * 返回值：  成功构造返回 OK ，否则返回 ERROR
 */
status
IntiaList(LkList *L) {
  if (*L) { printf("已有挂载的线性表！\n"); return ERROR; }
  *L = (LkList)malloc(sizeof(LNode));  // 申请头节点空间
  if (!(*L)) { printf("内存空间不足！\n"); return ERROR; }
  (*L)->data = 0;    // 头节点存放表长
  (*L)->next = NULL;
  return OK;
}


/*
 * 函数名称：DestroyList
 * 函数参数：线性表 L 的指针
 * 函数功能：销毁线性表
 * 返回值：  成功销毁返回 OK ，否则返回 ERROR
 */
status
DestroyList(LkList *L) {
  LkList cur = *L;
  if (!cur) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 清理空间
  LkList nxt = cur->next; // 保存被清空元素后继的地址
  for (; nxt; cur = nxt, nxt = nxt->next) { free(cur); }
  // 此时 nxt == NULL ，cur 指向表尾
  free(cur);  // 释放表尾所占空间
  *L = NULL;
  return OK;
}


/*
 * 函数名称：ClearList
 * 函数参数：线性表 L 的指针
 * 函数功能：重置线性表
 * 返回值：  成功置空返回 OK ，否则返回 ERROR
 */
status
ClearList(LkList *L) {
  if (DestroyList(L) == OK && IntiaList(L) == OK) { return OK; }
  else { return ERROR; }
}


/*
 * 函数名称：ListEmpty
 * 函数参数：线性表 L
 * 函数功能：判断线性表是否为空
 * 返回值：  若 L 为空表则返回 TRUE ，否则返回 FALSE
 *           判断失败返回 ERROR
 */
status
ListEmpty(LkList L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (L->next) { return FALSE; }
  else { return TRUE; }
}


/*
 * 函数名称：ListLength
 * 函数参数：线性表 L
 * 函数功能：计算线性表 L 中数据元素的个数
 * 返回值：  计算成功则返回 L 中数据元素的个数，计算失败返回 ERROR
 */
int
ListLength(LkList L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  return L->data; // HACK: 表头节点存放表长
}


/*
 * 函数名称：GetElem
 * 函数参数：线性表 L ，用 e 带回第 i 个数据元素的值
 * 函数功能：查找并用 e 带回第 i 个元素的值
 * 返回值：  查找成功则返回 OK ，否则返回 ERROR
 */
status
GetElem(LkList L, int idx, ElemType *rst) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (idx < 1 || idx > ListLength(L)) {
    printf("输入的位序大小不合法！\n");
    return ERROR;
  }
  for (; idx > 0; idx--) { L = L->next; }
  *rst = L->data;
  return OK;
}


/*
 * 函数名称：ListInsert
 * 函数参数：线性表 L 的地址，插入的位置 i ，插入的数据元素 e
 * 函数功能：在 L 的第 i 个位置之前插入新的数据元素 e
 *           若已插满，则按照分配增量，分配更大的空间，再插入
 * 返回值：  成功插入返回 OK ，否则返回 ERROR
 */
status
ListInsert(LkList L, int key, ElemType val) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if ((ListLength(L) == 0 && key != 1)
      || (ListLength(L) != 0
          && (key < 1 || key > ListLength(L)))) {
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


/*
 * 函数名称：ListDelete
 * 函数参数：线性表 L 的地址，删除的位序 i ，带回数据的指针 e
 * 函数功能：删除 L 的第 i 个数据元素，用 e 返回其值
 *           若可以缩小分配增量所指明的空间，则重新分配更小的空间
 * 返回值：  成功删除返回 OK ，否则返回 ERROR
 */
status
ListDelete(LkList L, int key, ElemType *val) {
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


/*
 * 函数名称：LocateElem
 * 函数参数：线性表 L ，相比对的元素值
 * 函数功能：查找 L 中数据值与 e 相同的元素所在的位序
 * 返回值：  成功则返回第一个与 e 相同的元素所在的位序，不存在则返回 0，
 *           否则返回 ERROR
 */
int
LocateElem(LkList L, ElemType val) {
  // 合法性检测
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 遍历表寻找符合条件的元素
  int idx = 1;
  for (L = L->next; L && val != L->data; L = L->next) { idx++; }
  if (!L) { return 0; } // 遍历一遍没有找到符合条件的元素
  return idx;
}


/*
 * 函数名称：PriorElem
 * 函数参数：线性表 L ，查找的数据 cur_e ，其前驱值用 pre_e 带回
 * 函数功能：查找 L 中与 cur_e 相同的第一个数据，并用 pre_e 带回其前驱的值
 * 返回值：  操作成功则返回 OK ，否则返回 ERROR
 */
status
PriorElem(LkList L, ElemType cur_e, ElemType *pre_e) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 遍历链表找 cur_e 的前驱
  LkList prev = L;
  for (; prev->next && prev->next->data != cur_e;
         prev = prev->next) { /* pass */ ; }
  // 对找到的前驱进行判断
  if (prev->next == NULL) { // - 没有找到
    printf("未找到元素值为输入值的元素！\n");
    return ERROR;
  }
  if (prev == L) {  // - cur_e 为表中第一个元素，
                    //   即 prev 指向表头节点
    printf("元素值为输入值的元素是表中的第一个元素！\n");
    return ERROR;
  }
  // - 正常情况
  *pre_e = prev->data;
  return OK;
}


/*
 * 函数名称：NextElem
 * 函数参数：线性表 L ，查找的数据 cur_e ，其后继值用 next_e 带回
 * 函数功能：查找 L 中与 cur_e 相同的第一个数据，并用 next_e 带回其后继的值
 * 返回值：  操作成功则返回 OK ，否则返回 ERROR
 */
status
NextElem(LkList L, ElemType cur_e, ElemType *nxt_e) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 遍历链表找 cur_e
  LkList curr = L->next;  // NOTE: curr 指向当前元素
  for (; curr && curr->data != cur_e;
         curr = curr->next) { /* pass */ ; }
  // 对找到的元素进行判断
  if (curr == NULL) { // - 没有找到
    printf("未找到元素值为输入值的元素！\n");
    return ERROR;
  }
  if (curr->next == NULL) { // - cur_e 为表中最后一个元素
    printf("元素值为输入值的元素是表中的最后一个元素！\n");
    return ERROR;
  }
  // - 正常情况
  *nxt_e = curr->next->data;
  return OK;
}


/*
 * 函数名称：ListTrabverse
 * 函数参数：线性表 L
 * 函数功能：依次访问并显示线性表中的每个元素
 * 返回值：  成功遍历返回 OK ，否则返回ERROR
 */
status
ListTrabverse(LkList L) {
  if (!L) { printf("线性表还没有被创建！\n");  return ERROR; }
  // 遍历并输出
  printf(" ------------- All Elements -------------\n    ");
  for (L = L->next; L; L = L->next) {
    printf("%d ", L->data);
  }
  printf("\n ----------------- End ------------------\n");
  return OK;
}


/*
 * 函数名称：SaveList
 * 函数参数：文件指针 fp ，线性表 L
 * 函数功能：将 L 中的数据保存到 fp 指向的文件中
 * 返回值：  成功保存返回 OK ，否则返回 ERROR
 */
status
SaveList(FILE *fp, LkList L) {
  if (!fp) { return ERROR; }
  if (!L) { printf("线性表还没有创建！\n"); return ERROR; }
  for (; L; L = L->next) {
    fwrite(&L->data, sizeof(ElemType), 1, fp);
  }
  return OK;
}


/*
 * 函数名称：LoadList
 * 函数参数：文件指针 fp ，线性表 L 的地址
 * 函数功能：将 fp 指向文件中的数据，加载到线性表 L 中
 * 返回值：  加载成功返回 OK ，加载失败返回 ERROR
 */
status
LoadList(FILE *fp, LkList *L) {
  if (!fp) { return ERROR; }
  if ((*L)) { printf("已有挂载的线性表！\n"); return ERROR; }
  // 计算文件中表长
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp) / sizeof(ElemType) - 1; // 表头节点不计表长
  rewind(fp);
  //  读取线性表，一次读一个
  // - 读取表头，挂载线性表
  *L = (LkList)malloc(sizeof(LNode));
  if (!(*L)) { return ERROR; }
  fread(&( (*L)->data ), sizeof(ElemType), 1, fp);
  // - 检查表头数据是否为表长
  if ((*L)->data != filesize) {
    printf("文件损坏！\n");
    free(*L); *L = NULL;
    return ERROR;
  }
  // - 读取剩余部分
  LkList new_node = *L;
  for (; filesize; filesize--) {
    new_node->next = (LkList)malloc(sizeof(LNode));
    if (!new_node->next) { return ERROR; }
    new_node = new_node->next; new_node->next = NULL;
    fread(&new_node->data, sizeof(ElemType), 1, fp);
  }
  return OK;
}


/*
 * 函数名称：SelectList
 * 函数参数：线性表 L 的地址，多表数组 pool ，
 *           存放 L 在 pool 中位置的 current_list （0-下标）的地址，
 *           要切换到的线性表在 pool 中的位序 idx （1-下标）
 * 函数功能：切换工作表到 pool 中第 idx 个线性表
 * 返回值：  成功切换返回 OK ，否则返回 ERROR
 */
status
SelectList(LkList *L, LkList pool[], int *cur, int tgt) {
  if (tgt < 1 || tgt > LIST_POOL_SIZE) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  pool[*cur] = *L;
  *L = pool[tgt - 1];
  *cur = tgt - 1;
  return OK;
}
