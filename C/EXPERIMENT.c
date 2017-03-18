#include "stdio.h"


#define BITS_OF_INT     sizeof(int)*8


short i;    // loop variable
int mask;   // mask



void print_bits(int);


int main(void) {

    print_bits(1 ^ 3);

    return 0;
}




void print_bits(int x) {

    unsigned int mask = 1 << (BITS_OF_INT - 1);

    for (i=0; i<BITS_OF_INT; ++i) {

        putchar( (x & mask) ? '1' : '0' );
        mask >>= 1;

        !((i+1)%8) && i<BITS_OF_INT-1 ? (putchar(' ')) : 0;

    }

    putchar('\n');
}
