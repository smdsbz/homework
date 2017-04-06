#include "stdio.h"



void hailstone(int);
/* calculate and display hailstones
     using the number(int) given
 */


int degrade(int *);


void main(void) {


    int n;  // seed


    while (
        scanf("%d", &n),
        getchar(),
        n                   // exit loop if n == 0
    ) {

        hailstone(n);

    }


}



void hailstone(int n) {

    int i = 1;  // positoning
    int m = n;  // local copy

    for (; m; ++i) {
        printf("%5u", m);
        if ( (i%6) == 0 ) { putchar('\n'); }
        degrade(&m);
    }

    putchar('\n');
    if ( (i)%6 ) { putchar('\n'); }

}



int degrade(int * m) {
    if (*m == 1) {
        // end calc
        *m = 0;   // exit code
    }
    else if (*m % 2) {
        // odd
        *m = 3 * *m + 1;
    }
    else {
        // even
        *m = *m / 2;
    }
    return *m;   // extensive api
}
