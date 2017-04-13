#include "stdio.h"
// #include "math.h"


unsigned char isPrime(unsigned int);


void main(void) {

    unsigned int begin, end;
    unsigned int i;


    while (
        scanf("%u %u", &begin, &end),
        getchar(),
        (begin!=0) && (begin>=6) && (end>=begin)
    ) {

        // regulation - begin must be even
        if ( begin % 2 ) { begin = begin / 2 * 2 + 2; }

        // using begin as the current number
        for (; begin <= end; begin+=2) {

            for (i = 2; i < begin; ++i) {
                if ( isPrime(i) && isPrime(begin-i) ) {
                    printf("%u=%u+%u\n", begin, i, begin-i);
                    break;
                }
            }

        }   // having reached the last number


        // end for this time
        putchar('\n');

    }
}




unsigned char isPrime(unsigned x) {

    unsigned i = 2;
    unsigned max = x/2 + 1;

    for (; i <= max; ++i) {
        if ( !(x%i) ) { break; }
    }

    // prime -> can't find from 2 to max - i should be i+1 now
    if (i==max+1) { return 1; }
    // not prime
    else { return 0; }

}
