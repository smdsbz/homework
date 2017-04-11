#include "stdio.h"

#undef Swap
#define Swap(x, y)  (y), (x)



void main(void) {

    // unsigned int N;
    unsigned int i;
    // scanf("%u", &N), getchar();


    int x, y;


    for (
        i = 1;
        scanf("%d %d", &x, &y) == 2;
        ++i
    ) {

        // scanf("%d %d", &x, &y);
        getchar();

        printf("Case %u:\n", i);
        printf("Before Swap:a=%d b=%d\n", x, y);
        printf("After Swap:a=%d b=%d\n", Swap(x, y));
        putchar('\n');


    }


}
