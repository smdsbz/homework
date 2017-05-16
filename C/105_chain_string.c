#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////

typedef struct _chain {
    char    c;
    struct _chain   *next;
} Chain;

/////////////////////////////////////////

Chain * createChain(void) {
    /* return position of the end node */
    // start_node
    Chain *cur = (Chain *)malloc(sizeof(Chain));
    Chain *start = cur;
    cur->c = getchar();
    cur->next = NULL;
    // next ndoe
    char c;
    while ((c = getchar()) != EOF) {
        cur->next = (Chain *)malloc(sizeof(Chain));
        cur = cur->next;    // shift cur to the next node
        cur->c = c;
        cur->next = NULL;
    }
    return start;
}



void printChain(Chain *start) {
    while (start->next != NULL) {
        putchar(start->c);
        start = start->next;
    }
    putchar(start->c);
    putchar('\n');
}


int nodeCount(Chain *chain) {
    int cnt = 1;
    // add one for each char
    for (; chain->next != NULL; ++cnt) {
        // add one for \r
        if (chain->c == '\n') { ++cnt; }
        chain = chain->next;
    }
    // add one for \0
    ++cnt;
    return cnt;
}


void breakChain(Chain *start) {
    Chain *tmp = start;
    while (start->next != NULL) {
        tmp = start->next;
        free(start);
        start = tmp;
    }
    free(start);
}



//////////////////////////////////////////

void main(void) {

    Chain *chain = createChain();
    printChain(chain);

    putchar('\n');

    char *str_start = (char *)malloc(sizeof(char) * nodeCount(chain));
    Chain *node = chain; char *str = str_start;
    // first char
    if (node->c == '\n') {
        *str = '\r';
        ++str;
    }
    *str = node->c;
    // next char
    while (node->next != NULL) {
        node = node->next;
        ++str;
        if (node->c == '\n') {
            *str = '\r';
            ++str;
        }
        *str = node->c;
    }
    // end flag
    ++str;
    *str = '\0';

    breakChain(chain);

    printf("%s\n", str_start);

    // for (str = str_start; *str != '\0'; ++str) {
    //     // printf("Freeing %p\n", str);
    //     free(str);
    // }
    // free(str_start);

    return;
}
