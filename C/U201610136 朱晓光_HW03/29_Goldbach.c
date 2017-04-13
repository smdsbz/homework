#include "stdio.h"
unsigned char isPrime(unsigned int);
void main(void) {
	puts("GOLDBACH'S CONJECTURE:");
	puts("Every even number n>=4 is the sum of two primes.");
    unsigned int begin, end;
    unsigned int i;
    while (
        scanf("%u %u", &begin, &end),
        getchar(),
        (begin!=0) && (begin>=6) && (end>=begin)
    ) {
        if ( begin % 2 ) { begin = begin / 2 * 2 + 2; }
        for (; begin <= end; begin+=2) {
            for (i = 2; i < begin; ++i) {
                if ( isPrime(i) && isPrime(begin-i) ) {
                    printf("%u=%u+%u\n", begin, i, begin-i);
                    break;
                }
            }
        }
        putchar('\n');
    }
}
unsigned char isPrime(unsigned x) {
    unsigned i = 2;
    unsigned max = x/2 + 1;
    for (; i <= max; ++i) {
        if ( !(x%i) ) { break; }
    }
    if (i==max+1) { return 1; }
    else { return 0; }
}

