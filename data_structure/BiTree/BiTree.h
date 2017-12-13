#ifndef BITREE_H_
#define BITREE_H_

/*
 *  基于二叉链表的二叉树实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#include "./MACROS.h"

/* 数据结构定义 */
typedef struct _BiNode {
  ElemType        data;   // 数据元素
  struct _BiNode *lchild; // 左子树
  struct _BiNode *rchild; // 右子树
} BiNode, *BiTree;

/* 数据结构方法定义 */
/** 树基本操作 **/
status InitBiTree(BiTree *T);
status DestroyBiTree(BiTree *T);
status CreateBiTree(BiTree T, const char *definition);
status ClearBiTree(BiTree T);
status BiTreeEmpty(BiTree T);
unsigned int BiTreeDepth(BiTree T);
/** 对节点操作 **/
BiTree Root(BiTree T);
ElemType Value(BiTree T, BiNode elem);
status Assign(BiTree T, BiNode *elem, ElemType val);
BiTree Parent(BiTree T, BiNode elem);
/** 浏览树操作 **/
BiTree LeftChild(BiTree T, BiNode elem);
BiTree RightChild(BiTree T, BiNode elem);
BiTree LeftSibling(BiTree T, BiNode elem);
BiTree RightSibling(BiTree T, BiNode elem);
/** 更改树操作 **/
status InsertChild(BiTree T, BiNode *elem, int LR, BiTree c);
status DeleteChild(BiTree T, BiNode *elem, int LR);
/** 遍历树操作 **/
status PreOrderTaverse(BiTree T);
status InOrderTraverse(BiTree T);
status PostOrderTraverse(BiTree T);
status LevelOrderTraverse(BiTree T);

// #define DEBUG

#endif
