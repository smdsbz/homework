#include "stdio.h"

#undef swap
#define swap(x, y)  (y), (x)



void main(void) {

    unsigned int N;
    scanf("%u", &N), getchar();


    int x, y;


    for (; N != 0; --N) {

        scanf("%d %d", &x, &y);
        printf("%d %d\n", swap(x, y));


    }


}
