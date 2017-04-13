#include "stdio.h"


unsigned int result;

unsigned int commonDivisor(unsigned, unsigned);


void main(void) {


    unsigned int a, b;

    while (
        scanf("%u %u", &a, &b),
        getchar(),
        a!=0 && b!=0
    ) {

        result = 0;


        printf("%u\n", commonDivisor(a, b));

    }

}




unsigned int commonDivisor(unsigned a, unsigned b) {

    // regulation - a < b
    if (a > b) {
        b += a;
        a = b - a;
        b -= a;
    }


    if ( result == 0 ) { result = a; }


    if ( !(b%result) && !(a%result) ) { return result; }
    else { --result; return commonDivisor(a, b); }

}
