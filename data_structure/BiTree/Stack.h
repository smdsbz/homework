#ifndef STACK_H_
#define STACK_H_

/*
 *  基于二叉链表的二叉树实现
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#include "./MACROS.h"

typedef struct _Stack {
  BiTree          data;
  struct _Stack  *next;
} SNode, *Stack;

status Stack_init(Stack *);
status Stack_destroy(Stack *);
status Stack_empty(Stack);
size_t Stack_length(Stack);
status Stack_getElem(Stack, int, BiTree *);
BiTree Stack_top(Stack);
status Stack_insert(Stack, int, BiTree);
status Stack_push(Stack, BiTree);
status Stack_append(Stack, BiTree);
status Stack_delete(Stack, int, BiTree *);
BiTree Stack_pop(Stack);
status Stack_priorElem(Stack, BiTree, BiTree *);
status Stack_nextElem(Stack, BiTree, BiTree *);
status Stack_traverse(Stack);

#endif
