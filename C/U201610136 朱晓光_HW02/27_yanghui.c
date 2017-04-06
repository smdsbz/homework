#include "stdio.h"



unsigned short combination(unsigned char, unsigned char);



void main(void) {


    unsigned char size;

    unsigned char i, j;     // loop var



    while (
        scanf("%hhu", &size),
        getchar(),
        size != 0 && size <= 12
    ) {

        for (i = 1; i <= size; ++i) {
            printf("%*d", (size-i)*2+1, 1);
            for (j = 1; j < i; ++j) {
                printf("%4hu", combination(i-1, j));
            }
            putchar('\n');
        }

        putchar('\n');
    }




}





unsigned short combination(unsigned char i, unsigned char j) {
    // printf("combination(%hhu,%hhu)\n", i, j);
    if (j == 0) { return 1; }
    else { return combination(i, j-1) * (i-j+1) / j; }
}
