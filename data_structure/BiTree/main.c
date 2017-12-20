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

  BiTree tree_pool[20] = { NULL };
  size_t curr_tree = 0;
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
    printf("--------------------- EXTRA -----------------------\n");
    printf("      21. SaveTree       22. LoadTree\n");
    printf("      23. SelectTree\n");
    printf("\n");
    printf("       0. Exit\n");
    printf("---------------------------------------------------\n");
    printf("    请选择你的操作[0~23]: ");
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
      case 6: {
        int ret = BiTreeDepth(T);
        if (ret == ERROR) { printf("获取二叉树深度失败！\n"); }
        else { printf("二叉树深度为 %d 。\n", ret); }
        getchar(); break;
      }
      case 7: {
        BiTree ret = Root(T);
        if (ret == NULL) { printf("二叉树为空树！\n"); }
        else {
          printf("二叉树的根节点为 <BiNode Node_%lu : '%c' @ %p>\n",
                 ret->data.id, ret->data.data, ret);
        }
        getchar(); break;
      }
      case 8: {
        size_t key;
        printf("请输入要查找元素的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        char ret = Value(T, key);
        if (ret == '\0') { printf("查找失败！\n"); }
        else { printf("该元素值为 '%c'。\n", ret); }
        getchar(); break;
      }
      case 9: {
        size_t key; char val;
        printf("请输入要赋值元素的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        printf("请输入元素更改后的值： ");
        scanf("%c", &val); getchar();
        if (Assign(T, key, val) == OK) { printf("成功修改元素的值！\n"); }
        else { printf("操作失败！\n"); }
        getchar(); break;
      }
      case 10: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        BiTree ret = Parent(T, key);
        if (ret != NULL) {
          printf("该节点的双亲节点为 <BiNode Node_%lu : '%c' @ %p>\n",
                 ret->data.id, ret->data.data, ret);
        } else { printf("查找失败！\n"); }
        getchar(); break;
      }
      case 11: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        BiTree ret = LeftChild(T, key);
        if (ret != NULL) {
          printf("该节点的左孩子节点为 <BiNode Node_%lu : '%c' @ %p>\n",
                 ret->data.id, ret->data.data, ret);
        } else { printf("查找失败！\n"); }
        getchar(); break;
      }
      case 12: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        BiTree ret = RightChild(T, key);
        if (ret != NULL) {
          printf("该节点的右孩子节点为 <BiNode Node_%lu : '%c' @ %p>\n",
                 ret->data.id, ret->data.data, ret);
        } else { printf("查找失败！\n"); }
        getchar(); break;
      }
      case 13: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        BiTree ret = LeftSibling(T, key);
        if (ret != NULL) {
          printf("该节点的左兄弟节点为 <BiNode Node_%lu : '%c' @ %p>\n",
                 ret->data.id, ret->data.data, ret);
        } else { printf("查找失败！\n"); }
        getchar(); break;
      }
      case 14: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        BiTree ret = RightSibling(T, key);
        if (ret != NULL) {
          printf("该节点的右兄弟节点为 <BiNode Node_%lu : '%c' @ %p>\n",
                 ret->data.id, ret->data.data, ret);
        } else { printf("查找失败！\n"); }
        getchar(); break;
      }
      case 15: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        int LR = -1;
        while (LR != 0 && LR != 1) {
          printf("请选择要插入子树的位置 [0-左 | 1-右]： ");
          scanf("%d", &LR); getchar();
        }
        char buffer[100]; size_t read_cur = 1;
        printf("请输入要插入的子树的层次遍历： ");
        // 读取层次遍历，由于需要读取空格，不能用 scanf
        while ((buffer[0] = (char)getchar()) == '\n') { ; }
        while ((buffer[read_cur] = (char)getchar()) != '\n') { read_cur++; }
        buffer[read_cur] = '\0';  // 补上字符串结束符
        if (InsertChild(T, key, LR, buffer) == OK) { printf("成功插入！\n"); }
        else { printf("插入失败！\n"); }
        getchar(); break;
      }
      case 16: {
        size_t key;
        printf("请输入节点的层次遍历位序： ");
        scanf("%lu", &key); getchar();
        int LR = -1;
        while (LR != 0 && LR != 1) {
          printf("请选择要删除的子树 [0-左 | 1-右]： ");
          scanf("%d", &LR); getchar();
        }
        if (DeleteChild(T, key, LR) == OK) { printf("成功删除子树！\n"); }
        else { printf("删除子树失败！\n"); }
        getchar(); break;
      }
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
      case 21: {
        FILE *fp; char filename[100];
        printf("请输入文件名： "); scanf("%s", filename); getchar();
        if ((fp = fopen(filename, "w")) == NULL) {
          printf("不能够创建文件！\n");
        } else {
          if (SaveBiTree(fp, T) == OK) {
            printf("成功写入文件！\n");
          } else { printf("写入文件失败！\n"); }
        }
        fclose(fp); getchar(); break;
      }
      case 22: {
        FILE *fp; char filename[100];
        printf("请输入文件名： "); scanf("%s", filename); getchar();
        if ((fp = fopen(filename, "rb")) == NULL) {
          printf("不能够读取文件！\n");
        } else {
          if (LoadBiTree(fp, &T) == OK) {
            printf("成功从文件读取！\n");
          } else { printf("从文件读取失败！\n"); }
        }
        fclose(fp); getchar(); break;
      }
      case 23: {
        size_t tgt;
        printf("请输入要切换到的树的序号 [1-20]： ");
        scanf("%lu", &tgt); getchar();
        if (SelectBiTree(tree_pool, &T, &curr_tree, tgt) == OK) { printf("切换成功！\n"); }
        else { printf("切换失败！\n"); }
        getchar(); break;
      }
      case 0: { break; }
      default: { break; }
    } // switch

  } // while
} // main




#ifdef DEBUG
#undef DEBUG
#endif
