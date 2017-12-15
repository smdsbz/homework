/*
 *  基于顺序存储结构的线性表实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */

#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

/* Page 10 */
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASABLE  -1
#define OVERFLOW    -2

/* 数据元素类型定义 */
typedef int status;
typedef int ElemType;

/* Page 22 */
#define LIST_INIT_SIZE  2
#define LIST_INC_SIZE   1

#define LIST_POOL_SIZE  20

/* 基于顺序存储结构的线性表数据结构定义 */
typedef struct _SqList {
  ElemType *elem;       // 指向线性存储区
  int       length;     // 表长
  int       list_size;  // 表容量
} SqList;

/* Page 19 */
status IntiaList(SqList *l);
status DestroyList(SqList *l);
status ClearList(SqList *l);
status ListEmpty(SqList l);
int ListLength(SqList l);
status GetElem(SqList l, int i, ElemType *e);
status LocateElem(SqList l, ElemType e);
status PriorElem(SqList l, ElemType cur, ElemType *pre_e);
status NextElem(SqList l, ElemType cur, ElemType *next_e);
status ListInsert(SqList *l, int i, ElemType e);
status ListDelete(SqList *l, int i, ElemType *e);
status ListTrabverse(SqList l);
/* 文件操作 */
status SaveList(FILE *fp, SqList l);
status LoadList(FILE *fp, SqList *l);
status SqList_writeToFile(SqList l, const char *filename);
status SqList_readFromFile(SqList *l, const char *path);
/* 多表操作 */
status SelectList(SqList *l, SqList pool[], int *cur, int idx);


/* Main */
int main(int argc, const char *argv[]) {
  // 初始化表池
  SqList list_pool[LIST_POOL_SIZE]; // 表池
  int current_list = 0; // 保存 L 在 list_pool 中的位置
  int i = 0;  // HACK: 重用下面的 `op` 来节省内存空间（不过也就 4 个字节。。
  for (; i < LIST_POOL_SIZE; i++) {
    list_pool[i].elem = NULL;
    list_pool[i].length = 0;
    list_pool[i].list_size = 0;
  }
  SqList L; L.elem = NULL; L.length = 0; L.list_size = 0;  // 初始化
  int op=1; // 操作表示符
  while (op) {
    puts("[LOG] before cls"); // HACK: 加上这一行可以解决在运行缓慢的
                              //       Win10 虚拟机中，功能函数正常返回后
                              //       可能卡死在 `system("cls")` 的问题。
                              //       至于具体原理我也不清楚，
                              //       反正它 **真的** 解决问题了
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
        int result = ListEmpty(L);
        if (result == TRUE) { printf("线性表为空表！\n"); }
        // NOTE: 由于 FALSE 和 ERROR 值均为 0 ，故当线性表还没有创建时，使用
        //       该功能将同时输出“线性表还没有被创建！”和“线性表不为空表！”
        else if (result == FALSE) { printf("线性表不为空表！\n"); }
        else { printf("操作失败！\n"); }
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
        int index; ElemType result; // 函数参数
        printf("请输入元素位序： "); scanf("%d", &index);
        int ret = GetElem(L, index, &result);  // 存取返回状态码
        if (ret == OK) { printf("该元素值为 %d 。\n", result); }
        else { printf("获取元素值失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 7: {
        int target;
        printf("请输入要查找的元素的值： "); scanf("%d", &target);
        int ret = LocateElem(L, target);
        if (ret == 0) { printf("该元素不在线性表中！\n"); }
        else { printf("该元素在线性表中的位序为 %d 。\n", ret); }
        getchar(); getchar();
        break;
      }
      case 8: {
        ElemType current, previous;
        printf("请输入目标元素的直接后继的值： "); scanf("%d", &current);
        int ret = PriorElem(L, current, &previous);
        if (ret == OK) { printf("目标元素值为 %d 。\n", previous); }
        else { printf("获取目标元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 9: {
        ElemType current, next;
        printf("请输入要目标元素的直接前驱的值： "); scanf("%d", &current);
        int ret = NextElem(L, current, &next);
        if (ret == OK) { printf("目标元素值为 %d 。\n", next); }
        else { printf("获取目标元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 10: {
        int key; ElemType value;
        printf("请输入要插入元素的位置： "); scanf("%d", &key);
        printf("请输入要插入元素的值： "); scanf("%d", &value);
        if (ListInsert(&L, key, value) == OK) { printf("成功插入元素！\n"); }
        else { printf("插入元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 11: {
        int key; ElemType value;
        printf("请输入要删除元素的位序： "); scanf("%d", &key);
        int ret = ListDelete(&L, key, &value);
        if (ret == OK) { printf("成功删除元素，其值为 %d 。\n", value); }
        else { printf("删除元素失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 12: {
        if (!ListTrabverse(L)) { printf("线性表是空表！\n"); }
        getchar(); getchar();
        break;
      }
      case 13: {
        char filename[100];
        printf("请输入文件名： "); scanf("%s", filename);
        if (SqList_writeToFile(L, filename) == OK) {
          printf("成功写入文件！\n");
        } else { printf("写入文件失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 14: {
        char filename[100];
        printf("请输入文件名： "); scanf("%s", filename);
        int ret = SqList_readFromFile(&L, filename);
        if (ret == OK) { printf("成功从文件读取！\n"); }
        else { printf("从文件读取失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 15: {
        int index;
        printf("请输入要操作的表的位序： "); scanf("%d", &index);
        if (SelectList(&L, list_pool, &current_list, index) == OK) {
          printf("切换操作表成功！\n");
        } else { printf("切换操作表失败！\n"); }
        getchar(); getchar();
        break;
      }
      case 0: { break; }  // 无效操作
      default: { break; }
    } // switch
  } // while

  printf("欢迎下次再使用本系统！\n");
  return 0; // 这里就不返回 OK 了，不然 shell 会判异常退出的
}


/*** 函数具体实现 ***/

/*
 * 函数名称：IntiaList
 * 函数参数：线性表 L 的指针
 * 函数功能：构造一个空的线性表
 * 返回值：  成功构造返回 OK ，否则返回 ERROR
 */
status
IntiaList(SqList *L) {
  if (L->elem) { printf("该线程下已有挂载的线性表！\n"); return ERROR; }
  L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L->elem) { return ERROR; }
  L->length = 0; L->list_size = LIST_INIT_SIZE;
#ifdef DEBUG
  L->length = 10; // 直接存入随机值（初始值）用作测试数据
  L->elem[2] = 1; L->elem[3] = 2; L->elem[4] = 5;
#endif
  return OK;
}


/*
 * 函数名称：ListTrabverse
 * 函数参数：线性表 L
 * 函数功能：依次访问并显示线性表中的每个元素
 * 返回值：  成功遍历返回 OK ，否则返回ERROR
 */
status
ListTrabverse(SqList L) {
  if (!L.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  int i;
  printf("\n-----------all elements -----------------------\n");
  for (i = 0; i < L.length; i++) { printf("%d ", L.elem[i]); }
  printf("\n------------------ end ------------------------\n");
  return L.length;
}


/*
 * 函数名称：DestroyList
 * 函数参数：线性表 L 的指针
 * 函数功能：销毁线性表
 * 返回值：  成功销毁返回 OK ，否则返回 ERROR
 */
status
DestroyList(SqList *l) {
  // 合法性检测
  if (!l->elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 释放空间
  free(l->elem);
  l->elem = NULL; l->length = 0; l->list_size = 0;
  return OK;
}


/*
 * 函数名称：ClearList
 * 函数参数：线性表 L 的指针
 * 函数功能：重置线性表
 * 返回值：  成功置空返回 OK ，否则返回 ERROR
 */
status
ClearList(SqList *l) {
  // 合法性检测
  if (!l->elem) {
    printf("线性表还没有被创建！\n");
    return ERROR;
  }
  // 直接将表大小置 0
  l->length = 0;
  // 减少空间占用
  if (l->list_size > LIST_INIT_SIZE) {
    free(l->elem);
    l->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!l->elem) { return ERROR; }
  }
  return OK;
}


/*
 * 函数名称：ListEmpty
 * 函数参数：线性表 L
 * 函数功能：判断线性表是否为空
 * 返回值：  若 L 为空表则返回 TRUE ，否则返回 FALSE
 *           判断失败返回 ERROR
 */
status
ListEmpty(SqList l) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (l.length) { return FALSE; }
  return TRUE;
}


/*
 * 函数名称：ListLength
 * 函数参数：线性表 L
 * 函数功能：计算线性表 L 中数据元素的个数
 * 返回值：  计算成功则返回 L 中数据元素的个数，计算失败返回 ERROR
 */
int
ListLength(SqList l) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 直接返回结构体中定义的表长
  return l.length;  // NOTE: 表长为零时返回 0 ，正好是 ERROR 的值，主函数无法区分！
}


/*
 * 函数名称：GetElem
 * 函数参数：线性表 L ，用 e 带回第 i 个数据元素的值
 * 函数功能：查找并用 e 带回第 i 个元素的值
 * 返回值：  查找成功则返回 OK ，否则返回 ERROR
 */
status
GetElem(SqList l, int idx, ElemType *e) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (idx > l.length || idx < 1) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  // 取出并赋值
  *e = l.elem[idx - 1];
  return OK;
}


/*
 * 函数名称：LocateElem
 * 函数参数：线性表 L ，相比对的元素值
 * 函数功能：查找 L 中数据值与 e 相同的元素所在的位序
 * 返回值：  成功则返回第一个与 e 相同的元素所在的位序，不存在则返回 0，
 *           否则返回 ERROR
 */
status
LocateElem(SqList l, ElemType e) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 遍历查找元素
  int idx = 1;  // 直接从 1 开始加，省得后面序列转位序还要加一
  for (; l.elem[idx - 1] != e; idx++) {
    if (idx > l.length) { return 0; }
  }
  // 找到了！返回！
  return idx;
}


/*
 * 函数名称：PriorElem
 * 函数参数：线性表 L ，查找的数据 cur_e ，其前驱值用 pre_e 带回
 * 函数功能：查找 L 中与 cur_e 相同的第一个数据，并用 pre_e 带回其前驱的值
 * 返回值：  操作成功则返回 OK ，否则返回 ERROR
 */
status
PriorElem(SqList l, ElemType cur_e, ElemType *pre_e) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 获取 `cur_e` 位序
  int idx = LocateElem(l, cur_e);  // NOTE: 重复了合法性检测
  idx -= 2; // 获取 `pre_e` 对基地址的偏移量
            // 第一个 -1 : 前一个元素
            // 第二个 -1 : 位序转偏移量
  // 检查 `cur_e` 合法性
  if (idx == -2) {
    printf("未找到元素值为输入值的元素！\n");
    return ERROR;
  }
  if (idx == -1) {
    printf("元素值为输入值的元素为表中第一个元素！\n");
    return ERROR;
  } else {  // 正常
    // 给 `pre_e` 赋值
    *pre_e = l.elem[idx];
    return OK;
  }
}


/*
 * 函数名称：NextElem
 * 函数参数：线性表 L ，查找的数据 cur_e ，其后继值用 next_e 带回
 * 函数功能：查找 L 中与 cur_e 相同的第一个数据，并用 next_e 带回其后继的值
 * 返回值：  操作成功则返回 OK ，否则返回 ERROR
 */
status
NextElem(SqList l, ElemType cur_e, ElemType *next_e) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 获取 `cur_e` 位序
  int idx = LocateElem(l, cur_e);
  // idx = idx + 1 - 1; // 类似于 PriorElem 中的操作，但恰好不改变元素值
  // 检查 `cur_e` 合法性
  if (idx == 0) {
    printf("未找到元素值为输入值的元素！\n");
    return ERROR;
  }
  if (idx == l.length) {
    printf("元素值为输入值的元素为表中最后一个元素！\n");
    return ERROR;
  } else {  // 正常
    // 给 `next_e` 赋值
    *next_e = l.elem[idx];
    return OK;
  }
}


/*
 * 函数名称：ListInsert
 * 函数参数：线性表 L 的地址，插入的位置 i ，插入的数据元素 e
 * 函数功能：在 L 的第 i 个位置之前插入新的数据元素 e
 *           若已插满，则按照分配增量，分配更大的空间，再插入
 * 返回值：  成功插入返回 OK ，否则返回 ERROR
 */
status
ListInsert(SqList *l, int i, ElemType e) {
  // 合法性检测
  if (!l->elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // - `i` 范围限制
  if ((l->length == 0 && i != 1)  // 空表
      || (l->length > 0 && (i < 1 || i > l->length))) {  // 非空表，`i`应有范围
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  // 空间是否已满？
  if (l->length == l->list_size) {
    // 扩充空间
    l->list_size += LIST_INC_SIZE;
    // 将数据移动到空间更宽裕的地方
    l->elem = (ElemType *)realloc(l->elem, l->list_size);
    if (!l->elem) { return OVERFLOW; }  // 检查
  }
  // 移动插入位置之后的所有元素
  i--;  // 转化为偏移量
  int bak_ptr = l->length - 1;
  for (; bak_ptr >= i; bak_ptr--) {
    l->elem[bak_ptr + 1] = l->elem[bak_ptr];
  }
  // 给目标位置赋值
  l->elem[i] = e;
  // 扩充可见表长
  l->length += 1;
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
ListDelete(SqList *l, int i, ElemType *e) {
  // 合法性检测
  if (!l->elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (i < 1 || i > l->length) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  // 删除元素值带出
  i--; l->length -= 1;
  *e = l->elem[i];
  // 删除位置后元素依次前移
  for (; i < l->length; i++) {
    l->elem[i] = l->elem[i + 1];
  }
  // 检查是否可以减小容量
  // HACK: 与上一步进行合并可以减小时间消耗
  if (l->list_size - l->length > LIST_INC_SIZE) {
    l->elem = (ElemType *)realloc(l->elem,
        (l->list_size - LIST_INC_SIZE) * sizeof(ElemType));
    if (!l->elem) { return ERROR; }
  }
  return OK;
}


/*
 * 函数名称：SaveList
 * 函数参数：文件指针 fp ，线性表 L
 * 函数功能：将 L 中的数据保存到 fp 指向的文件中
 * 返回值：  成功保存返回 OK ，否则返回 ERROR
 */
status
SaveList(FILE *fp, SqList l) {
  if (!fp) { return ERROR; }  // NOTE: **假设** 传进来的 fp 是已打开的文件
  if (!l.elem) { return ERROR; }
  fwrite(l.elem, sizeof(ElemType), l.length, fp);
  return OK;
}


status
SqList_writeToFile(SqList l, const char *filename) {
  // 合法性检测
  if (!l.elem) { printf("线性表还没有被创建！\n"); return ERROR; }
  // 创建文件
  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    printf("不能够创建文件！\n");
    return ERROR;
  }
  // 写入
  if (SaveList(fp, l) != OK) {
    /* pass */
    return ERROR;
  }
  fclose(fp); return OK;  // 释放句柄并返回
}


/*
 * 函数名称：LoadList
 * 函数参数：文件指针 fp ，线性表 L 的地址
 * 函数功能：将 fp 指向文件中的数据，加载到线性表 L 中
 * 返回值：  加载成功返回 OK ，加载失败返回 ERROR
 */
status
LoadList(FILE *fp, SqList *l) {
  if (!fp) { return ERROR; }
  if (l->elem) { return ERROR; }  // 不允许覆盖正挂载的表
  // 初始化挂载结构体
  // - 获取文件大小
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp) / sizeof(ElemType);
  fseek(fp, 0, SEEK_SET);
  // - 必要时创建空间
  if ((!l->elem) || l->length < filesize) { // 没有空间 或 空间太小
    if (l->elem) { free(l->elem); } // NOTE: 这个分支不会执行！
                                    //       已禁止覆盖挂载表的操作！
    l->elem = (ElemType *)malloc(filesize * sizeof(ElemType));
    if (!l->elem) { return ERROR; }
  }
  // 一次性读取文件内容
  l->length = filesize; l->list_size = filesize;
  fread(l->elem, sizeof(ElemType), filesize, fp);
  return OK;
}


status
SqList_readFromFile(SqList *l, const char *path) {
  // 检查是否已有表挂载
  if (l->elem) { printf("已有挂载的线性表！\n"); return ERROR; }
  // 打开文件
  FILE *fp;
  if ((fp = fopen(path, "r")) == NULL) {
    printf("不能够读取文件！\n");
    return ERROR;
  }
  // 读取
  if (LoadList(fp, l) != OK) {
    /* pass */
    return ERROR;
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
SelectList(SqList *l, SqList pool[], int *current_list, int idx) {
  // 合法性检测
  if (idx < 1 || idx > LIST_POOL_SIZE) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  idx--;  // 位序转偏移量
  // 向池中存储表数据
  pool[*current_list] = *l;
  // 加载目标表数据
  // NOTE: 由于 `L` 不是 malloc 出来的，不能直接改变其指向
  l->elem = pool[idx].elem;
  l->length = pool[idx].length;
  l->list_size = pool[idx].list_size;
  // 改动表指针
  *current_list = idx;
  return OK;
}
