#include "stdio.h"


unsigned char month[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};



void main(void) {


    unsigned char count;

    int y, m, d;      // year, month, day

    for (
        scanf("%hhu", &count), getchar();
        count != 0;
        --count
    ) {


        scanf("%d %d %d", &y, &m, &d);
        getchar();


        if (
            (  ( (y%4 == 0) && y%100 ) || (y%400 == 0)  )  &&  ( (m!=1) && (m!=2) )
        ) {
            d++;
        }

        // printf("%d %d %d\n", y, m, d);


        for (; m > 1; --m) {
            d += month[m-2];
        }




        printf("%d\n", d);


    }   // end of while


    // while ( scanf("%d %d %d", &y, &m, &d) == EOF ) { puts("EOF entered!"); }




}
