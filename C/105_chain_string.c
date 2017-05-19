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
        // printf("%d\n", cnt);
        // // add one for \r
        // if (chain->c == '\n') { ++cnt; }
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




void insertReturn(Chain *node) {
    Chain *tmp;
    while (node->next != NULL) {
        tmp = node;                         // store previous location
        node = node->next;                  // move cursor
        if (tmp->c=='\n' && node->c=='\n') {
            /* tmp '\n' --> ^($new_node here)^ '\r' --> node '\n' --> (node->next) */
            Chain *new_node = (Chain *)malloc(sizeof(Chain));
            new_node->c = '\r';             // instert '\r' between consecutive '\n's
            new_node->next = node;          // connecting subsequent node
            tmp->next = new_node;           // connecting previous node
            // node = new_node->next;          // jump to the subsequent '\n'
        }
    }
}






//////////////////////////////////////////

void main(void) {

    Chain *chain = createChain();
    printChain(chain);

    putchar('\n');

    insertReturn(chain);

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
        // if (node->c == '\n') {
        //     *str = '\r';
        //     ++str;
        // }
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
    // TODO: works on Linux, but not on Windows
    free(str_start);

    return;
}
