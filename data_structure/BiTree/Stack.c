/*
 *  辅助栈数据结构定义
 *
 *  重用 LkList 代码
 *    链表中第一个元素为栈顶，最后一个元素为栈底
 */

#include <stdio.h>
#include <stdlib.h>

#include "MACROS.h"
#include "BiTree.h"
#include "Stack.h"


status
Stack_init(Stack *L) {
  if (*L) { printf("已有挂载的线性表！\n"); return ERROR; }
  *L = (Stack)malloc(sizeof(SNode));  // 申请头节点空间
  if (!(*L)) { printf("内存空间不足！\n"); return ERROR; }
  (*L)->data = NULL;    // 头节点存放表长
  (*L)->next = NULL;
  return OK;
}


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


// status
// Stack_clear(Stack *L) {
//   if (Stack_destroy(L) == OK && Stack_init(L) == OK) { return OK; }
//   else { return ERROR; }
// }


status
Stack_empty(Stack L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (L->next) { return FALSE; }
  else { return TRUE; }
}


size_t
Stack_length(Stack L) {
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  size_t ret = 0;
  for (L = L->next; L; L = L->next) { ret++; }
  return ret;
}


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


BiTree
Stack_top(Stack L) {
  BiTree ret;
  Stack_getElem(L, 1, &ret);
  return ret;
}


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


status
Stack_push(Stack L, BiTree val) {
  if (!L) { return ERROR; }
  return Stack_insert(L, 1, val);
}


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


status
Stack_delete(Stack L, int key, BiTree *val) {
  // 合法性检查
  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
  if (key < 1 || key > Stack_length(L)) {
    printf("输入地址格式不合法！\n");
    return ERROR;
  }
  // 更改表长
  // L->data -= 1;
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


BiTree
Stack_pop(Stack L) {
  BiTree ret;
  Stack_delete(L, 1, &ret);
  return ret;
}


// int
// Stack_locateElem(Stack L, BiTree val) {
//   // 合法性检测
//   if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
//   // 遍历表寻找符合条件的元素
//   int idx = 1;
//   for (L = L->next; L && val != L->data; L = L->next) { idx++; }
//   if (!L) { return 0; } // 遍历一遍没有找到符合条件的元素
//   return idx;
// }


//status
//Stack_priorElem(Stack L, BiTree cur_e, BiTree *pre_e) {
//  // 合法性检查
//  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
//  // 遍历链表找 cur_e 的前驱
//  Stack prev = L;
//  for (; prev->next && prev->next->data != cur_e;
//         prev = prev->next) { /* pass */ ; }
//  // 对找到的前驱进行判断
//  if (prev->next == NULL) { // - 没有找到
//    printf("未找到元素值为输入值的元素！\n");
//    return ERROR;
//  }
//  if (prev == L) {  // - cur_e 为表中第一个元素，
//                    //   即 prev 指向表头节点
//    printf("元素值为输入值的元素是表中的第一个元素！\n");
//    return ERROR;
//  }
//  // - 正常情况
//  *pre_e = prev->data;
//  return OK;
//}


//status
//Stack_nextElem(Stack L, BiTree cur_e, BiTree *nxt_e) {
//  // 合法性检查
//  if (!L) { printf("线性表还没有被创建！\n"); return ERROR; }
//  // 遍历链表找 cur_e
//  Stack curr = L->next;  // NOTE: curr 指向当前元素
//  for (; curr && curr->data != cur_e;
//         curr = curr->next) { /* pass */ ; }
//  // 对找到的元素进行判断
//  if (curr == NULL) { // - 没有找到
//    printf("未找到元素值为输入值的元素！\n");
//    return ERROR;
//  }
//  if (curr->next == NULL) { // - cur_e 为表中最后一个元素
//    printf("元素值为输入值的元素是表中的最后一个元素！\n");
//    return ERROR;
//  }
//  // - 正常情况
//  *nxt_e = curr->next->data;
//  return OK;
//}


//status
//Stack_traverse(Stack L) {
//  if (!L) { printf("线性表还没有被创建！\n");  return ERROR; }
//  // 遍历并输出
//  printf(" ------------- All Elements -------------\n    ");
//  for (L = L->next; L; L = L->next) {
//    printf("%c ", L->data->data);
//  }
//  printf("\n ----------------- End ------------------\n");
//  return OK;
//}


// status
// Stack_saveToFile(FILE *fp, Stack L) {
//   if (!fp) { return ERROR; }
//   if (!L) { printf("线性表还没有创建！\n"); return ERROR; }
//   for (; L; L = L->next) {
//     fwrite(&L->data, sizeof(BiTree), 1, fp);
//   }
//   return OK;
// }


// status
// Stack_loadFromFile(FILE *fp, Stack *L) {
//   if (!fp) { return ERROR; }
//   if ((*L)) { printf("已有挂载的线性表！\n"); return ERROR; }
//   // 计算文件中表长
//   fseek(fp, 0, SEEK_END);
//   size_t filesize = ftell(fp) / sizeof(BiTree) - 1; // 表头节点不计表长
//   rewind(fp);
//   //  读取线性表，一次读一个
//   // - 读取表头，挂载线性表
//   *L = (Stack)malloc(sizeof(SNode));
//   if (!(*L)) { return ERROR; }
//   fread(&( (*L)->data ), sizeof(BiTree), 1, fp);
//   // - 检查表头数据是否为表长
//   if ((*L)->data != filesize) {
//     printf("文件损坏！\n");
//     free(*L); *L = NULL;
//     return ERROR;
//   }
//   // - 读取剩余部分
//   Stack new_node = *L;
//   for (; filesize; filesize--) {
//     new_node->next = (Stack)malloc(sizeof(SNode));
//     if (!new_node->next) { return ERROR; }
//     new_node = new_node->next; new_node->next = NULL;
//     fread(&new_node->data, sizeof(BiTree), 1, fp);
//   }
//   return OK;
// }


// status
// Stack_selectStack(Stack *L, Stack pool[], int *cur, int tgt) {
//   if (tgt < 1 || tgt > Stack_POOL_SIZE) {
//     printf("输入地址格式不合法！\n");
//     return ERROR;
//   }
//   pool[*cur] = *L;
//   *L = pool[tgt - 1];
//   *cur = tgt - 1;
//   return OK;
// }
