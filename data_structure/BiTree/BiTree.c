/*
 *    二叉树相关函数具体实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./BiTree.h"
#include "./Stack.h"


/*
 * 函数名称：InitBiTree
 * 函数参数：二叉树的头节点 T 的指针
 * 函数功能：初始化二叉树
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：DestroyBiTree
 * 函数参数：二叉树的头节点 T 的指针
 * 函数功能：销毁二叉树
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
DestroyBiTree(BiTree *T) {
  if (ClearBiTree(*T) != OK) { return ERROR; }
  free(*T);
  *T = NULL;
  return OK;
}


/*
 * 函数名称：ClearBiTree
 * 函数参数：二叉树的头节点 T
 * 函数功能：置空二叉树
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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
      T = Stack_top(S)->rchild;
      free(Stack_pop(S));
    }
  }
  Stack_destroy(&S);
  T_bak->lchild = NULL;
  return OK;
}


/*
 * 函数名称：CreateBiTree
 * 函数参数：二叉树的头节点 T，要创建的二叉树的层次遍历序列 definition
 * 函数功能：创建二叉树
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：BiTreeEmpty
 * 函数参数：二叉树的头节点 T
 * 函数功能：判断二叉树是否为空树
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
BiTreeEmpty(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); return ERROR; }
  if (T->lchild) { return FALSE; }
  return TRUE;
}


/*
 * 函数名称：_PostOrderTraverse_RecursionBlcok
 * 函数参数：二叉树的头节点 T
 * 函数功能：递归调用自身来对二叉树进行后序遍历
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
_PostOrderTraverse_RecursionBlock(BiTree T) {
  if (!T) { return ERROR; }
  _PostOrderTraverse_RecursionBlock(T->lchild);
  _PostOrderTraverse_RecursionBlock(T->rchild);
  printf("%c", T->data.data);
  return OK;
}


/*
 * 函数名称：PostOrderTraverse
 * 函数参数：二叉树的头节点 T
 * 函数功能：输出二叉树的后序遍历序列
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
PostOrderTraverse(BiTree T) {
  if (!T) { return ERROR; }
  if (!T->lchild) { return ERROR; }
  _PostOrderTraverse_RecursionBlock(T->lchild);
  return OK;
}


/*
 * 函数名称：PreOrderTraverse
 * 函数参数：二叉树的头节点 T
 * 函数功能：输出二叉树的先序遍历序列
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：_ReassignIDsInLevelOrder
 * 函数参数：二叉树的头节点 T
 * 函数功能：根据二叉树的层次遍历顺序对二叉树节点重新进行编号
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：InOrderTraverse
 * 函数参数：二叉树的头节点 T
 * 函数功能：输出二叉树的中序遍历序列
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：LevelOrderTraverse
 * 函数参数：二叉树的头节点 T
 * 函数功能：输出二叉树的层次遍历序列
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：_BiTreeDepth_RecursionBlock
 * 函数参数：子树节点 cur
 * 函数功能：递归调用自身来求该节点子树的深度+1
 * 返回值：  返回左右子树深度+1
 */
int
_BiTreeDepth_RecursionBlock(BiTree cur) {
  if (!cur) { return 0; }
  int ldepth = _BiTreeDepth_RecursionBlock(cur->lchild);
  int rdepth = _BiTreeDepth_RecursionBlock(cur->rchild);
  if (ldepth < rdepth) { return rdepth + 1; } // 返回时 +1，即加上当前节点这一层
  return ldepth + 1;
}


/*
 * 函数名称：BiTreeDepth
 * 函数参数：二叉树的头节点 T
 * 函数功能：求二叉树的深度
 * 返回值：  操作成功返回树高，否则返回 ERROR
 */
int
BiTreeDepth(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！"); return ERROR; }
  if (T->lchild == NULL) { printf("二叉树为空树！\n"); return ERROR; }
  T = T->lchild;
  return _BiTreeDepth_RecursionBlock(T) - 1;  // 返回时 -1，因为根节点也算了一次
}


/*
 * 函数名称：Root
 * 函数参数：二叉树的头节点 T
 * 函数功能：获得二叉树的根节点地址
 * 返回值：  操作成功返回根节点地址，否则返回 NULL
 */
BiTree
Root(BiTree T) {
  if (!T) { printf("二叉树还没有被创建！\n"); return NULL; }
  return T->lchild; // 包含返回 NULL 的情况
}


/*
 * 函数名称：_GetNodeAddressByKey
 * 函数参数：二叉树的头节点 T，所求节点在层次遍历序列中的位序 key
 * 函数功能：获得所求节点的地址
 * 返回值：  操作成功返回所求节点地址，否则返回 NULL
 */
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


/*
 * 函数名称：Value
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key
 * 函数功能：获得所求节点储存的数据
 * 返回值：  操作成功返回所求节点储存的数据，否则返回 '\0'
 */
char
Value(BiTree T, size_t key) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return ERROR; }
  return node->data.data;
}


/*
 * 函数名称：Assign
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key，新值 val
 * 函数功能：将对应节点的数据更新为 val
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
Assign(BiTree T, size_t key, char val) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return ERROR; }
  node->data.data = val;
  return OK;
}


/*
 * 函数名称：Parent
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key
 * 函数功能：求对应节点的双亲节点
 * 返回值：  操作成功返回双亲节点地址，否则返回 NULL
 */
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


/*
 * 函数名称：LeftChild
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key
 * 函数功能：求对应节点的左孩子
 * 返回值：  操作成功返回所求节点的地址，否则返回 NULL
 */
BiTree
LeftChild(BiTree T, size_t key) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return NULL; }
  return node->lchild;
}


/*
 * 函数名称：RightChild
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key
 * 函数功能：求对应节点的右孩子
 * 返回值：  操作成功返回所求节点的地址，否则返回 NULL
 */
BiTree
RightChild(BiTree T, size_t key) {
  BiTree node = _GetNodeAddressByKey(T, key);
  if (node == NULL) { printf("未找到节点！\n"); return NULL; }
  return node->rchild;
}


/*
 * 函数名称：LeftSibling
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key
 * 函数功能：求对应节点的左兄弟
 * 返回值：  操作成功返回所求节点的地址，否则返回 NULL
 */
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


/*
 * 函数名称：RightSibling
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key
 * 函数功能：求对应节点的右兄弟
 * 返回值：  操作成功返回所求节点的地址，否则返回 NULL
 */
BiTree
RightSibling(BiTree T, size_t key) {
  BiTree parent = Parent(T, key);
  if (parent == NULL) { printf("未找到节点！\n"); return NULL; }
  if (parent->rchild && parent->rchild->data.id == key) { return NULL; }
  return parent->rchild;
}


/*
 * 函数名称：InsertChild
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key，
 *          插入位置标识 LR，插入子树的层次遍历序列 definition
 * 函数功能：将由 definition 所代表的二叉树，插入到 T 中 key 元素的子树中
 *          （ LR 为 0 时插入到左子树，为 1 时插入到右子树）
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：DeleteChild
 * 函数参数：二叉树的头节点 T，节点在层次遍历序列中的位序 key，删除位置标识 LR
 * 函数功能：删除 T 中 key 元素的子树
 *          （ LR 为 0 时删除左子树，为 1 时删除右子树）
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：SaveBiTree
 * 函数参数：文件指针 fp，二叉树的头节点 T
 * 函数功能：将二叉树 T 保存到由 fp 指向的文件中
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：LoadBiTree
 * 函数参数：文件指针 fp，二叉树的头节点 T 的指针
 * 函数功能：将由 fp 指向的文件中二叉树加载到 T 上
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
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


/*
 * 函数名称：SelectBiTree
 * 函数参数：树头节点数组 pool，操作树的头节点 T 的指针，
 *          操作树在 pool 中的位置 curr_tree，切换目标树 tgt
 * 函数功能：将 T 指向的二叉树保存到 pool 对应位置上，并让 T 指向由 tgt 说明的树
 * 返回值：  操作成功返回 OK，否则返回 ERROR
 */
status
SelectBiTree(BiTree pool[], BiTree *T, size_t *curr_tree, size_t tgt) {
  if (tgt > 20) { printf("输入的位序不合法！\n"); return ERROR; }
  pool[*curr_tree] = *T;
  *curr_tree = tgt - 1;
  *T = pool[*curr_tree];
  return OK;
}
