#include "stdio.h"


#define BITS_OF_INT     sizeof(int)*8



char i;     // loop variable




void print_bits(int);





int main(void) {

    /* user:
         int x: operatee
         int p: start position - counting from 0
         int n: range
     * internal:
         char i: loop variable
         unsigned int mask: a mask
     */

     int x, p, n;
     unsigned int mask = 0;

     scanf("%d %d %d", &x, &p, &n);

     if (p<0 || p>31)   { puts("star point out of range"); return 0; }
     if (n<1)   { puts("positive range number required"); return 0; }
     if (p+n > 32)  { puts("operate index out of range"); return 0; }



     // output original number
     print_bits(x);





     // modify mask
     for (; n>0; --n) {
         mask |= 1u << (p+n-1);
     }

    //  print_bits(mask);




     // output treated number
     print_bits(
         x ^ mask
     );


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
