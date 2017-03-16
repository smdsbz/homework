#include "stdio.h"
#include "math.h"

#define BYTES_OF_INT sizeof(int)*8

const short DEBUG = 0;

// test function - print bits to terminal
void _print_bits(short *bits);




int main(void) {

    /* test use:
         int x: the number to be circled
         int n: times to circle
     * programme use:
         int i: loop control variable
         int t: temporary variable
         short bits[]: stores binaries
         short carry: carry-over flag
     */
    int x, n;
    int i, t;
    short bits[BYTES_OF_INT];
    short carry;


    scanf("%d %d", &x, &n);

    // move in one direction
    // regulate n into range(31)
    while (n<0) { printf("n must be over 0!\n"); return 0; }
    n %= BYTES_OF_INT;




    // decimal 2 binary - true
    bits[0] = x<0 ? 1 : 0;

    x = x<0 ? -x : x;
    for (i=BYTES_OF_INT-1; i>0; --i) {
        bits[i] = x%2;
        x /= 2;
    }

    _print_bits(bits);





    // true 2 two's complement
    if (bits[0] == 1) {

        // 1. one's complement - reverse every number except sign bit
        for (i=BYTES_OF_INT-1; i>0; --i) {
            bits[i] = bits[i] ? 0 : 1;
        }

        _print_bits(bits);


        // 2. two's complement - simply plus one
        // TODO: rather stupid method - doing it the Turing way
        carry = 1;
        for (i=BYTES_OF_INT-1; i>0 && carry; --i) {
            bits[i] = bits[i] ? 0 : (carry=0, 1);
        }
        // TODO: develop a BigDecimal tool out of this

        _print_bits(bits);

    }   // fi




    // circle round
    // INCLUDING SIGN BIT
    for (; n>0; --n) {
        t = bits[BYTES_OF_INT-1];
        for (i=BYTES_OF_INT-1; i>0; --i) {
            bits[i] = bits[i-1];
        }
        bits[0] = t;
    }

    _print_bits(bits);





    // complement 2 true - only negative ints
    if (bits[0] == 1) {

        // two's 2 one's
        carry = 1;
        for (i=BYTES_OF_INT-1; i>0 && carry; --i) {
            bits[i] = bits[i] ? (carry=0, 0) : 1;
        }

        _print_bits(bits);


        // one's 2 true
        for (i=1; i<BYTES_OF_INT; ++i) {
            bits[i] = bits[i] ? 0 : 1;
        }

        _print_bits(bits);
    }



    // true 2 decimal
    // number
    n = 0; t = 1;
    for (i=BYTES_OF_INT-1; i>0; --i) {
        n += t * bits[i];
        t <<= 1;
    }
    // sign
    if (bits[0] == 1) {
        n = -n;
    }




    printf("%d\n", n);

    return 0;
}






void _print_bits(short *bits) {
    if (DEBUG) {
        printf("\n");
        for (int i=0; i<BYTES_OF_INT; ++i) {
            printf("%d", bits[i]);
            if(!((i+1)%8)) printf("\n");
        }
        printf("\n");
    }
}
