#include "stdio.h"

/*
* a RATHER memory-consuming AND CPU-time-consuming programme
*/




unsigned long Fib(signed char);



void main(void) {

    unsigned long tmp = 1, rst = 1;

    signed char n, i;



    // first run
    scanf("%hhd", &n);
    getchar();

    // exit method
    if (n == 0) { return; }
    else if (n < 3) { puts("Error!"); }
    else {
        for (i=0; i<n; ++i) {
            printf("%10lu", Fib(i+1));
            if ( ((i+1)%8==0) && (i+1)!=n ) { putchar('\n'); }
        }

        putchar('\n'); putchar('\n');
    }

    // end first run










    while ( scanf("%hhd", &n) != EOF ) {

        getchar();

        putchar('\n');

        // exit method
        if (n == 0) { break; }
        else if (n < 3) { puts("Error!"); continue; }




        for (i=0; i<n; ++i) {
            printf("%10lu", Fib(i+1));
            if ( ((i+1)%8==0) && (i+1)!=n ) { putchar('\n'); }
        }

        putchar('\n');


    }
}





unsigned long Fib(signed char idx) {

    if ( idx==1 || idx==2 ) {
        return 1;
    }
    else {
        return (Fib(idx-1) + Fib(idx-2));
    }

}
