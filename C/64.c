#include "stdio.h"


short i;    // loop variable


void print_bits(short *bits);



int main(void) {

    /* user input:
         int x: operatee
         int p: start position (counting from 0)
         int n: range
     * internal:
         short bits[32]: stores x in binary
         short i: loop variable
         short carry: carry-over flag
     */

     int x, p, n;
     short bits[32];
     short carry;

     scanf("%d %d %d", &x, &p, &n);

     // restrictions
     if (n<0)    { printf("Undefined Behariour: negative input\n"); return 0; }
     if (p<0 || p>31 || (p+n)>32)   { printf("Undefined Behariour: index out of range\n"); return 0; }




     // decimal 2 binary - true
     bits[31] = x<0 ? 1 : 0;
     x = x<0 ? -x : x;
     for (i=0; i<31; ++i) {
         bits[i] = x%2;
         x /= 2;
     }

     puts("true:");
     print_bits(bits);




     // true 2 two's complement
     if (bits[31] == 1) {

         // 1. one's complement - reverse every number except sign bit
         for (i=0; i<31; ++i) {
             bits[i] = bits[i] ? 0 : 1;
         }

         puts("one's:");
         print_bits(bits);



         // 2. two's complement - simply plus one
         // TODO: rather stupid method - doing it the Turing way
         carry = 1;
         for (i=0; i<31 && carry; ++i) {
             bits[i] = bits[i] ? 0 : (carry=0, 1);
         }

         puts("two's");
         print_bits(bits);

     }   // fi









    print_bits(bits);






     // reverse
     for (; n; ++p, --n) {
         bits[p] = bits[p] ? 0 : 1;
     }

     print_bits(bits);



     return 0;
}






void print_bits(short *bits) {
    for (i=31; i>-1; --i) {
        printf("%d", bits[i]);
        if (!((i)%8) && i!=31) { printf(" "); }
        if (i == 0)    { printf("\n"); }
    }
}
