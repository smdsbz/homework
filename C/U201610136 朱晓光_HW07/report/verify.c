#include <stdio.h>


char u[] = "UVWXYZ";
char v[] = "xyz";

struct T {
    int     x;
    char    c;
    char    *t;
} a[] = {{11, 'A', u}, {100, 'B', v}}, *p=a;



void main(void) {

    printf("%c\n", (++*p->t));

    // printf("%d\n", p->x);


}
