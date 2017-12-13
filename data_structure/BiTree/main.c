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
        buffer[read_cur] = '\0';  // 补上字符串结束符
        if (CreateBiTree(T, buffer) == OK) { printf("二叉树创建成功！\n"); }
        else { printf("二叉树创建失败！\n"); }
        getchar(); break; // 读取输入的时候已经吞过一个 '\n' 了
      }
      case 4: {
        if (ClearBiTree(T) == OK) { printf("二叉树清空成功！\n"); }
        else { printf("二叉树清空失败！\n"); }
        getchar(); break;
      }
      case 5: {
        status ret = BiTreeEmpty(T);
        if (ret == ERROR) { printf("获取二叉树状态失败！\n"); }
        else {
          if (ret == TRUE) { printf("二叉树为空树！\n"); }
          else if (ret == FALSE) { printf("二叉树不为空树！\n"); }
        }
        getchar(); break;
      }
      // case 6: {
      //   int ret = BiTreeDepth(T);
      //   if (ret == ERROR) { printf("获取二叉树深度失败！\n"); }
      //   else { printf("二叉树深度为 %d 。\n", ret); }
      //   getchar(); break;
      // }
      case 17: {
        if (PreOrderTraverse(T) == OK) { ; }
        else { printf("操作失败！\n"); }
        getchar(); break;
      }
      case 18: {
        if (InOrderTraverse(T) == OK) { ; }
        else { printf("操作失败！\n"); }
        getchar(); break;
      }
      case 19: {
        if (PostOrderTraverse(T) == OK) { ; }
        else { printf("操作失败！\n"); }
        getchar(); break;
      }
      case 20: {
        if (LevelOrderTraverse(T) == OK) { ; }
        else { printf("操作失败！\n"); }
        getchar(); break;
      }
      case 0: { break; }
      default: { getchar(); break; }
    } // switch

  } // while
} // main




#ifdef DEBUG
#undef DEBUG
#endif
