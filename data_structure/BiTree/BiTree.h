#ifndef BITREE_H_
#define BITREE_H_

/*
 *  二叉树的头文件
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
int BiTreeDepth(BiTree T);
/** 对节点操作 **/
BiTree Root(BiTree T);
char Value(BiTree T, size_t key);
status Assign(BiTree T, size_t key, char val);
BiTree Parent(BiTree T, size_t key);
/** 浏览树操作 **/
BiTree LeftChild(BiTree T, size_t key);
BiTree RightChild(BiTree T, size_t key);
BiTree LeftSibling(BiTree T, size_t key);
BiTree RightSibling(BiTree T, size_t key);
/** 更改树操作 **/
status InsertChild(BiTree T, size_t key, int LR, const char definition[]);
status DeleteChild(BiTree T, size_t key, int LR);
/** 遍历树操作 **/
status PreOrderTraverse(BiTree T);
status InOrderTraverse(BiTree T);
status PostOrderTraverse(BiTree T);
status LevelOrderTraverse(BiTree T);
/** 文件操作 **/
status SaveBiTree(FILE *fp, BiTree T);
status LoadBiTree(FILE *fp, BiTree *T);
/** 多表操作 **/
status SelectBiTree(BiTree pool[], BiTree *working_tree,
                    size_t *curr_tree, size_t tgt);

// #define DEBUG

#endif
