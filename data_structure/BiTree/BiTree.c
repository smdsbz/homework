/*
 *    二叉树相关函数具体实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./BiTree.h"
#include "./Stack.h"


status
InitBiTree(BiTree *T) {
  if (*T) { printf("已有挂载的二叉树！\n"); return ERROR; }
  if ( (*T = (BiTree)malloc(sizeof(BiNode))) == NULL ) {
    printf("内存空间不足！\n");
    return ERROR;
  }
  (*T)->data.id = 0;
  (*T)->data.data = '\0';
  (*T)->lchild = NULL;
  (*T)->rchild = NULL;
  return OK;
}


status
DestroyBiTree(BiTree *T) {
  if (ClearBiTree(*T) != OK) { return ERROR; }
  free(*T);
  *T = NULL;
  return OK;
}


status
ClearBiTree(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); }
  if (T->lchild == NULL) { return OK; }
  BiTree T_bak = T;
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  while (!Stack_empty(S) || T) {
    if (T) { Stack_push(S, T); T = T->lchild; }
    else {
      // T = Stack_pop(S);
      // printf("%c", T->data.data);
      // T = T->rchild;
      T = Stack_top(S)->rchild;
      free(Stack_pop(S));
    }
  }
  Stack_destroy(&S);
  T_bak->lchild = NULL;
  return OK;
}


status
CreateBiTree(BiTree T, const char definition[]) {
  if (!T) { printf("二叉树没有被创建！\n"); return ERROR; }
  if (T->lchild) { printf("已有挂载的二叉树！\n"); return ERROR; }
  if (definition[0] == ' ') {
    printf("数据输入格式有错误！\n");
    return ERROR;
  }
  Stack S = NULL; Stack_init(&S);
  BiTree  new_node = NULL;
  size_t elem_id = 1;   // 元素 id，用于查找元素的 key
  // 添加根节点至树林中
  if (!InitBiTree(&new_node)) { return ERROR; };
  new_node->data.id = elem_id++;
  new_node->data.data = definition[0];
  T->lchild = new_node;
  // 根节点进栈
  Stack_append(S, new_node);
  size_t curr_elem = 2; // definition 标示
  while (definition[curr_elem - 1]) {
    // - 输入空树
    if (definition[curr_elem - 1] == ' ') { // 输入空树
      if (curr_elem % 2) {  // 右子树为空，出队列
        Stack_pop(S);
      }
      curr_elem++;
      continue;
    }
    // - 输入非空
    // 创建新节点
    new_node = NULL;
    if (!InitBiTree(&new_node)) { return ERROR; }
    new_node->data.id = elem_id++;
    new_node->data.data = definition[curr_elem - 1];
    Stack_append(S, new_node);
    // 添加到树中
    if (Stack_empty(S)) { // - 输入错误
      printf("数据输入格式有误！\n");
      Stack_destroy(&S);
      DestroyBiTree(&T);
      return ERROR;
    }
    if (curr_elem % 2 == 0) {  // - 添加到左子树
      Stack_top(S)->lchild = new_node;
    } else {  // - 添加到右子树
      Stack_top(S)->rchild = new_node;
      Stack_pop(S);
    }
    // 新节点进队列
    curr_elem++;
  }
  Stack_destroy(&S);
  T->data.id = elem_id - 1; // HACK: 根节点 id 存放节点总个数
  return OK;
}


status
BiTreeEmpty(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
  if (T->lchild) { return FALSE; }
  return TRUE;
}


status
_PostOrderTraverse_RecursionBlock(BiTree T) {
  if (!T) { return ERROR; }
  _PostOrderTraverse_RecursionBlock(T->lchild);
  _PostOrderTraverse_RecursionBlock(T->rchild);
  printf("%c", T->data.data);
  return OK;
}


status
PostOrderTraverse(BiTree T) {
  if (!T) { return ERROR; }
  if (!T->lchild) { return ERROR; }
  _PostOrderTraverse_RecursionBlock(T->lchild);
  return OK;
}


status
PreOrderTraverse(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！"); return ERROR; }
  if (T->lchild == NULL) { printf("二叉树为空树！\n"); return ERROR; }
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  Stack_push(S, T);
  while (!Stack_empty(S)) {
    printf("%c", T->data.data);
    if (T->lchild && T->rchild) { // - 分岔节点
      Stack_push(S, T);
      T = T->lchild;  // 先遍历左子树
      continue;
    }
    if (T->lchild) { T = T->lchild; continue; }
    if (T->rchild) { T = T->rchild; continue; }
    // if (T->lchild || T->rchild)
    // - 叶子节点
    T = Stack_pop(S)->rchild;  // 后遍历右子树
  }
  printf("\n");
  Stack_destroy(&S);
  return OK;
}


status
_ReassignIDsInLevelOrder(BiTree T) {
  if (!T) { printf("二叉树没有被创建！\n"); return ERROR; }
  if (T->lchild == NULL) { return OK; }
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  size_t curr_id = 1;
  // 根节点进栈
  Stack_append(S, T);
  while (!Stack_empty(S)) {
    // 执行访问操作
    Stack_top(S)->data.id = curr_id++;
    // 左右子树进栈
    if (Stack_top(S)->lchild) {
      Stack_append(S, Stack_top(S)->lchild);
    }
    if (Stack_top(S)->rchild) {
      Stack_append(S, Stack_top(S)->rchild);
    }
    Stack_pop(S); // 当前节点出队列
  }
  Stack_destroy(&S);
  T->data.id = curr_id - 1;
  return OK;
}


status
InOrderTraverse(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); }
  if (T->lchild == NULL) { printf("二叉树为空树！\n"); }
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  while (!Stack_empty(S) || T) {
    if (T) { Stack_push(S, T); T = T->lchild; }
    else {
      T = Stack_pop(S);
      printf("%c", T->data.data);
      T = T->rchild;
    }
  }
  printf("\n");
  Stack_destroy(&S);
  return OK;
}


status
LevelOrderTraverse(BiTree T) {
  if (!T) { printf("二叉树没有被创建！\n"); return ERROR; }
  if (T->lchild == NULL) { printf("二叉树为空树！\n"); return OK; }
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  // 根节点进栈
  Stack_append(S, T);
  while (!Stack_empty(S)) {
    // 执行访问操作
    printf("%c", Stack_top(S)->data.data);
    // 左右子树进栈
    if (Stack_top(S)->lchild) {
      Stack_append(S, Stack_top(S)->lchild);
    }
    if (Stack_top(S)->rchild) {
      Stack_append(S, Stack_top(S)->rchild);
    }
    Stack_pop(S); // 当前节点出队列
  }
  Stack_destroy(&S);
  printf("\n");
  return OK;
}


int
_BiTreeDepth_RecursionBlock(BiTree cur) {
  if (!cur) { return 0; }
  int ldepth = _BiTreeDepth_RecursionBlock(cur->lchild);
  int rdepth = _BiTreeDepth_RecursionBlock(cur->rchild);
  if (ldepth < rdepth) { return rdepth + 1; } // 返回时 +1，即加上当前节点这一层
  return ldepth + 1;
}


int
BiTreeDepth(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！"); return ERROR; }
  if (T->lchild == NULL) { printf("二叉树为空树！\n"); return ERROR; }
  T = T->lchild;
  return _BiTreeDepth_RecursionBlock(T) - 1;  // 返回时 -1，因为根节点也算了一次
}


BiTree
Root(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); }
  return T->lchild; // 包含返回 NULL 的情况
}


BiTree
_GetNodeAddressByKey(BiTree T, size_t key) {
  if (!T) { printf("二叉树还没有被创建！\n"); return NULL; }
  if (T->lchild == NULL) { printf("二叉树为空树\n"); return NULL; }
  T = T->lchild;
  if (T->data.id == key) { return T; } // 根即是要查找的节点
  Stack S = NULL; Stack_init(&S);
  Stack_push(S, T);
  while (!Stack_empty(S)) {
    if (T->lchild && T->rchild) { // - 分岔节点
      Stack_push(S, T);
      T = T->lchild;  // 先遍历左子树
      if (T->data.id == key) { break; }
      else { continue; }
    }
    if (T->lchild) {
      T = T->lchild;
      if (T->data.id == key) { break; }
      else { continue; }
    }
    if (T->rchild) {
      T = T->rchild;
      if (T->data.id == key) { break; }
      else { continue; }
    }
    // if (T->lchild || T->rchild)
    // - 叶子节点
    T = Stack_pop(S)->rchild;  // 后遍历右子树
    if (T && T->data.id == key) { break; }
  }
  Stack_destroy(&S);
  if (T && T->data.id == key) { return T; }
  else { return NULL; }
}


char
Value(BiTree T, size_t key) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return ERROR; }
  return node->data.data;
}


status
Assign(BiTree T, size_t key, char val) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return ERROR; }
  node->data.data = val;
  return OK;
}


BiTree
Parent(BiTree T, size_t key) {
  if (!T) { printf("二叉树还没有被创建！\n"); return NULL; }
  if (T->lchild == NULL) { printf("二叉树为空树\n"); return NULL; }
  if (T->lchild->data.id == key) { printf("根节点无双亲节点！\n"); return NULL; }
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  Stack_push(S, T);
  while (!Stack_empty(S)) {
    if ((T->lchild && T->lchild->data.id == key)
        || (T->rchild && T->rchild->data.id == key)) { return T; }
    if (T->lchild && T->rchild) { // - 分岔节点
      Stack_push(S, T);
      T = T->lchild;  // 先遍历左子树
      continue;
    }
    if (T->lchild && T->lchild->data.id != key) { T = T->lchild; continue; }
    if (T->rchild && T->rchild->data.id != key) { T = T->rchild; continue; }
    if ((T->lchild && T->lchild->data.id == key)
        || (T->rchild && T->rchild->data.id == key)) { return T; }
    // - 叶子节点
    T = Stack_pop(S)->rchild;  // 后遍历右子树
  }
  Stack_destroy(&S);
  return NULL;
}


BiTree
LeftChild(BiTree T, size_t key) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return NULL; }
  return node->lchild;
}


BiTree
RightChild(BiTree T, size_t key) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return NULL; }
  return node->rchild;
}


BiTree
LeftSibling(BiTree T, size_t key) {
  BiTree parent = Parent(T, key);
  if (parent == NULL) { printf("未找到节点！\n"); return NULL; }
  // 可能的情况：
  // - parent->lchild == NULL：那么双亲的右孩子为 key，返回 NULL
  // - parent->lchlid->data.id == key：已经是左孩子了，返回 NULL
  if (parent->lchild && parent->lchild->data.id == key) { return NULL; }
  return parent->lchild;
}


BiTree
RightSibling(BiTree T, size_t key) {
  BiTree parent = Parent(T, key);
  if (parent == NULL) { printf("未找到节点！\n"); return NULL; }
  // 可能的情况：
  // - parent->rchild == NULL：那么双亲的左孩子为 key，返回 NULL
  // - parent->rchlid->data.id == key：已经是右孩子了，返回 NULL
  if (parent->rchild && parent->rchild->data.id == key) { return NULL; }
  return parent->rchild;
}


status
InsertChild(BiTree T, size_t key, int LR, const char definition[]) {
  if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
  if (!T->lchild) { printf("二叉树为空树！\n"); return ERROR; }
  BiTree c = NULL; InitBiTree(&c);
  if (CreateBiTree(c, definition) != OK) { DestroyBiTree(&c); return ERROR; }
  if (c->lchild->rchild) {
    printf("要插入的子树右子树不为空！\n");
    DestroyBiTree(&c); return ERROR;
  }
  BiTree elem = _GetNodeAddressByKey(T, key);
  if (LR == 0) {  // 插入左子树
    c->lchild->rchild = elem->lchild;
    elem->lchild = c->lchild;
  } else if (LR == 1) { // 插入右子树
    c->lchild->rchild = elem->rchild;
    elem->rchild = c->lchild;
  }
  // 释放子树的头节点
  free(c);
  _ReassignIDsInLevelOrder(T);
  return OK;
}


status
DeleteChild(BiTree T, size_t key, int LR) {
  if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
  if (!T->lchild) { printf("二叉树为空树！\n"); return ERROR; }
  BiTree elem = _GetNodeAddressByKey(T, key);
  if (LR == 0) {
    if (!elem->lchild) { printf("该节点没有左孩子！\n"); return ERROR; }
    DestroyBiTree(&(elem->lchild));
  }
  else if (LR == 1) {
    if (!elem->rchild) { printf("该节点没有右孩子！\n"); return ERROR; }
    DestroyBiTree(&(elem->rchild));
  }
  else { return ERROR; }
  return OK;
}


status
SaveBiTree(FILE *fp, BiTree T) {
  if (!fp) { return ERROR; }
  if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
  fprintf(fp, "%lu\n", T->data.id); // 第一行存放总节点数
  T = T->lchild;
  Stack S = NULL; Stack_init(&S);
  // 根节点进栈
  Stack_append(S, T);
  while (!Stack_empty(S)) {
    // 执行访问操作
    fprintf(fp, "%c", Stack_top(S)->data.data);
    // 左右子树进栈
    if (Stack_top(S)->lchild) {
      Stack_append(S, Stack_top(S)->lchild);
    }
    if (Stack_top(S)->rchild) {
      Stack_append(S, Stack_top(S)->rchild);
    }
    Stack_pop(S); // 当前节点出队列
  }
  Stack_destroy(&S);
  return OK;
}


status
LoadBiTree(FILE *fp, BiTree *T) {
  if (!fp) { return ERROR; }
  if (*T) { printf("已有挂载的二叉树！\n"); return ERROR; }
  if (InitBiTree(T) != OK) { return ERROR; }
  fscanf(fp, "%lu", &(*T)->data.id);
  char buffer[100] = { '\0' };
  fgetc(fp);  // 吞掉空行
  size_t curr_elem = 0;
  while ((buffer[curr_elem++] = (char)fgetc(fp)) != EOF) { ; }
  buffer[curr_elem - 1] = '\0';
  // 检查文件完整性
  if ((*T)->data.id != strlen(buffer)) {
    printf("文件损坏！\n");
    DestroyBiTree(T); return ERROR;
  }
  if (CreateBiTree(*T, buffer) == OK) { return OK; }
  else { printf("从文件读取失败！\n"); return ERROR; }
}


status
SelectBiTree(BiTree pool[], BiTree *T, size_t *curr_tree, size_t tgt) {
  if (tgt > 20) { printf("输入的位序不合法！\n"); return ERROR; }
  pool[*curr_tree] = *T;
  *curr_tree = tgt - 1;
  *T = pool[*curr_tree];
  return OK;
}
