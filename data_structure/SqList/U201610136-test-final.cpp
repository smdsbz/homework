#include "stdafx.h"
#include "linear_list_unit_test.h"


/*********************************NOTICE****************************************/
/* 1. 所有函数中，在遇到异常情况时，如访问越界，对空表进行删除，未创建表时就对表操作等，
    请不要调用exit等函数退出程序，仅仅return，使本次操作无效化即可，不影响之后正确的操作。
   2. 在未调用InitiaList或者LoadList前，线性表L中数据域指针开始应该指向NULL，避免野指针。
   3. ElemType为int类型。
   4. 多表操作将手动进行测试，不纳入该测试系统中。
   5. 宏定义声明：
			#define OK 1
			#define FALSE -1
			#define ERROR -2
*/
/*******************************************************************************/



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
  if (idx == ERROR - 2) {
    printf("未找到元素值值为输入值的元素！\n");
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
  // idx = idx + 1 - 1;	// 类似于 PriorElem 中的操作，但恰好不改变元素值
  // 检查 `cur_e` 合法性
  if (idx == ERROR) {
    printf("未找到元素值值为输入值的元素！\n");
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
  /*
   *  配合 API 用的 wrapper
   */
  if (!fp) { return ERROR; }  // NOTE: **假设** 传进来的 fp 是已打开的文件
  if (!l.elem) { return ERROR; }
  fwrite(l.elem, sizeof(ElemType), l.length, fp);
  return OK;
}


/*
 * 函数名称：LoadList
 * 函数参数：文件指针 fp ，线性表 L 的地址
 * 函数功能：将 fp 指向文件中的数据，加载到线性表 L 中
 * 返回值：  加载成功返回 OK ，加载失败返回 ERROR
 */
status
LoadList(FILE *fp, SqList *l) {
  /*
   *  配合 API 用的 wrapper
   */
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
