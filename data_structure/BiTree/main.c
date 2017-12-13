/*
 *  基于二叉链表的二叉树实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#include <stdio.h>
#include <stdlib.h>
#include "./BiTree.h"
#include "./Stack.h"


/* Main */
int main(int argc, const char *argv[]) {

  BiTree T = NULL;

  int op = 1;
  while (op) {
#if defined(__unix__) || defined(__linux__) || defined(__MACH__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
    printf("\n\n");

    /* 操作选择提示 */
    printf("   Menu for Binary Tree On Binary Tree Structure\n");
    printf("---------------------------------------------------\n");
    printf("       1. InitBiTree      2. DestroyBiTree\n");
    printf("       3. CreateBiTree    4. ClearBiTree\n");
    printf("       5. BiTreeEmpty     6. BiTreeDepth\n");
    printf("\n");
    printf("       7. Root            8. Value\n");
    printf("       9. Assign         10. Parent\n");
    printf("      11. LeftChild      12. RightChild\n");
    printf("      13. LeftSibling    14. RightSibling\n");
    printf("\n");
    printf("      15. InsertChild    16. DeleteChild\n");
    printf("\n");
    printf("      17. PreOrderTaverse\n");
    printf("      18. InOrderTraverse\n");
    printf("      19. PostOrderTraverse\n");
    printf("      20. LevelOrderTraverse\n");
    // printf("--------------------- EXTRA -----------------------\n");
    // printf("      13. SaveList       14. LoadList\n");
    // printf("      15. SelectList\n");
    printf("\n");
    printf("       0. Exit\n");
    printf("---------------------------------------------------\n");
    printf("    请选择你的操作[0~15]: ");
    scanf("%d", &op); getchar();

    /* 执行操作 */
    switch (op) {
      case 1: {
        if (InitBiTree(&T) == OK) { printf("二叉树初始化成功！\n"); }
        else { printf("二叉树创建失败！\n"); }
        getchar(); break;
      }
      case 2: {
        if (DestroyBiTree(&T) == OK) { printf("二叉树销毁成功！\n"); }
        else { printf("二叉树销毁失败！\n"); }
        getchar(); break;
      }
      case 3: {
        char buffer[100]; size_t read_cur = 1;
        printf("请输入二叉树的层次遍历： ");
        // 读取层次遍历，由于需要读取空格，不能用 scanf
        while ((buffer[0] = (char)getchar()) == '\n') { ; }
        while ((buffer[read_cur] = (char)getchar()) != '\n') { read_cur++; }
        buffer[read_cur] = '\0';
        #ifdef DEBUG
        printf("[LOG] buffer = '%s'\n", buffer);
        #endif
        if (CreateBiTree(T, buffer) == OK) { printf("二叉树创建成功！\n"); }
        else { printf("二叉树创建失败！\n"); }
        getchar(); break; // 读取输入的时候已经吞过一个 '\n' 了
      }

      case 20: {
        if (PostOrderTraverse(T) == OK) { ; }
        else { printf("操作失败！\n"); }
        getchar(); break;
      }
      case 0: { break; }
      default: { break; }
    } // switch

  } // while
} // main



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
  Stack S = NULL; Stack_init(&S);
  BiTree cur = *T;
  // 向栈中加入头节点
  Stack_push(S, cur);
  while (!Stack_empty(S)) {
    cur = Stack_top(S);
    // 遍历左子树
    while (cur->lchild) {
      cur = cur->lchild;
      Stack_push(S, cur);
    }
    // 遍历右子树
    while (cur->rchild) {
      cur = cur->rchild;
      Stack_push(S, cur);
    }
    // 执行访问操作，即销毁
    cur = Stack_pop(S); // 此后 Stack_top(S) 得到 cur 的双亲节点地址
    // - 双亲节点的孩子指针置空
    if (!Stack_empty(S)) {
      if (cur == Stack_top(S)->lchild) {
        Stack_top(S)->lchild = NULL;
      } else if (cur == Stack_top(S)->rchild) {
        Stack_top(S)->rchild = NULL;
      } else { return ERROR; }  // 这里啰嗦一下做个判断
    }
    free(cur);
  }
  Stack_destroy(&S);
  *T = NULL;
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
  if (definition[0] == ' ') {
    printf("数据输入格式有错误！\n");
    return ERROR;
  }
  Stack S = NULL; Stack_init(&S);
  // 添加根节点数据
  T->data.id = 1;
  T->data.data = definition[0];
  // 根节点进栈
  Stack_append(S, T);
  size_t curr_elem = 2; // 层次遍历位序指示
  while (definition[curr_elem - 1]) {
    // - 输入空树
    if (definition[curr_elem - 1] == ' ') {
      if (curr_elem % 2) {  // 右子树均为空，出队列
        Stack_pop(S);
      }
      curr_elem++;
      continue;
    }
    // - 输入非空
    // 创建新节点
    BiTree new_node = NULL;
    InitBiTree(&new_node);
    new_node->data.id = curr_elem;
    new_node->data.data = definition[curr_elem - 1];
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
    Stack_append(S, new_node);
    curr_elem++;
  }
  Stack_destroy(&S);
  return OK;
}


status
PostOrderTraverse(BiTree cur) {
  if (!cur) { printf("二叉树还没有被创建！\n"); return ERROR; }
  Stack S = NULL; Stack_init(&S);
  // 向栈中加入头节点
  Stack_push(S, cur);
  while (!Stack_empty(S)) {
    cur = Stack_top(S);
    // 遍历左子树
    while (cur->lchild) {
      cur = cur->lchild;
      Stack_push(S, cur);
    }
    // 遍历右子树
    while (cur->rchild) {
      cur = cur->rchild;
      Stack_push(S, cur);
    }
    // 执行访问操作
    printf("%c", Stack_pop(S)->data);
  }
  Stack_destroy(&S);
  return OK;
}

#ifdef DEBUG
#undef DEBUG
#endif
