/*
 *    二叉树相关函数具体实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#include <stdio.h>
#include <stdlib.h>
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
  *T = NULL;
  return OK;
}


status
ClearBiTree(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); }
  if (T->lchild == NULL) { printf("二叉树已经为空树！\n"); }
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
  T_bak->lchild = NULL;
  return OK;
}


//status
//InsertChild(BiTree T, BiNode *elem, int LR, BiTree c) {
//  if (!T) { printf("二叉树没有被创建！\n"); return ERROR; }
//  if (!elem) { printf("传入的节点为空！\n"); return ERROR; }
//  if (c->rchild) { printf("要添加的子树右子树不为空！\n"); return ERROR; }
//  if (LR == 0) {  // 插入左子树
//    c->rchild = elem->lchild;
//    elem->lchild = c;
//  } else if (LR == 1) { // 插入右子树
//    c->rchild = elem->rchild;
//    elem->rchild = c;
//  }
//  return OK;
//}



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
  // 添加根节点至树林中
  if (!InitBiTree(&new_node)) { return ERROR; };
  new_node->data.id = 1;
  new_node->data.data = definition[0];
  T->lchild = new_node;
  // 根节点进栈
  Stack_append(S, new_node);
  size_t curr_elem = 2; // 层次遍历位序指示
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
    new_node->data.id = curr_elem;
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
  return OK;
}


status
BiTreeEmpty(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
  if (T->lchild) { return FALSE; }
  return TRUE;
}



// status
// PostOrderTraverse(BiTree T) {
//   if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
//   if (T->lchild == NULL) { printf("二叉树为空树！\n"); return ERROR; }
//   T = T->lchild;
//   Stack S = NULL; Stack_init(&S);
//   Stack_push(S, T); // 头节点进栈
//   while (!Stack_empty(S)) { // 外层循环，一次遍历一个分支
//     // - 中间节点
//     while (T->lchild || T->rchild) {
//       Stack_push(S, T); // 后续遍历，最后访问节点
//       if (T->lchild) { T = T->lchild; continue; } // 先左
//       if (T->rchild) { T = T->rchild; continue; } // 后右
//     }
//     // - 叶节点
//     printf("%c", T->data.data);
//     // -- 叶节点为双亲的右孩子
//     while (T == Stack_top(S)->rchild) {
//       printf("%c", Stack_top(S)->data.data);
//       T = Stack_pop(S);
//     }
//     // -- 叶节点为双亲的左孩子
//     if (T == Stack_top(S)->lchild) {
//       // --- 双亲有右子树，则继续遍历右子树
//       if (Stack_top(S)->rchild) { T = Stack_top(S)->rchild; continue; }
//       // --- 双亲无右子树，一路回溯至分叉节点，即有右子树的节点
//       while (T->rchild == NULL) { // NOTE: 条件同样对叶节点成立
//         printf("%c", Stack_top(S)->data.data);
//         T = Stack_pop(S);
//       } // 现在 T 左子树遍历完成，右子树等待遍历，且有 T == Stack_top(S)
//       T = T->rchild;  // 继续遍历 Stack_top(S) 的右子树
//     }
//   }
//   return OK;
// }

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
    if (T->lchild) {
      T = T->lchild;
      continue;
    }
    if (T->rchild) {
      T = T->rchild;
      continue;
    } // if (T->lchild || T->rchild)
    // - 叶子节点
    T = Stack_pop(S)->rchild;  // 后遍历右子树
  }
  printf("\n");
  return OK;
}


status
_InOrderTraverse_RecursionBlock(BiTree T) {
  if (!T) { return ERROR; }
  _InOrderTraverse_RecursionBlock(T->lchild);
  printf("%c", T->data.data);
  _InOrderTraverse_RecursionBlock(T->rchild);
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
    // 当前节点出队列
    Stack_pop(S);
  }
  Stack_destroy(&S);
  printf("\n");
  return OK;
}


// int
// _BiTreeDepth_RecursionBlock(BiTree cur) {
//   if (!cur) { return 0; }
//   int ldepth = _BiTreeDepth_RecursionBlock(cur->lchild);
//   int rdepth = _BiTreeDepth_RecursionBlock(cur->rchild);
//   if (ldepth < rdepth) { return rdepth; }
//   return ldepth;
// }
//
// int
// BiTreeDepth(BiTree T) {
//   if (!T) { printf("二叉树还没有被创建！"); return ERROR; }
//   if (T->lchild == NULL) { printf("二叉树为空树！\n"); return ERROR; }
//   T = T->lchild;
//   return _BiTreeDepth_RecursionBlock(T);
// }
