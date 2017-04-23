#include <stdio.h>




void printBits(int);




void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();



    int nums[120] = {0};

    unsigned i;


    for (i = 0; i < N; ++i) {
        scanf("%d", (nums + i));
    }


    for (i = 0; i < N; ++i) {
        printBits(nums[i]);
    }



}




void printBits(int dec) {

    int cur;

    for (cur = sizeof(int)*8-1; cur >= 0; --cur) {
        putchar( ( dec & (1<<cur) ) ? '1' : '0' );
    }

    putchar('\n');

}
