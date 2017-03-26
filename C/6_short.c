#include "stdio.h"

void main(void) {

    unsigned char N;    // total data count
    scanf("%hhu", &N);


    short cur;

    for (; N != 0; --N) {

        scanf("%hd", &cur);


        putchar( (cur&0xff00) >> 8 );
        putchar(',');
        putchar( (cur&0x00ff) );
        putchar('\n');

    }

}
