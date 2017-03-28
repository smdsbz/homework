#include "stdio.h"


void main(void) {



    int a, b;

    int attempt, final;



    while (1) {

        // input
        scanf("%d %d", &a, &b);

        // exit method
        if (a==0 && b==0)   break;

        // regulation: a < b
        if (a>b) {
            b += a;
            a = b - a;
            b -= a;
        }


        // max common divisor
        for (attempt=1; attempt<=a; ++attempt) {
            if ( !(a%attempt || b%attempt) ) {      // if both are 0 --> True
                final = attempt;
            }
        }
        printf("%d ", final);


        // min common multiple
        for (attempt=b;; ++attempt) {
            if ( !(attempt%a || attempt%b) ) {
                printf("%d\n", attempt);
                break;
            }
        }

    }   // end of while



}
