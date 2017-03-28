#include "stdio.h"


unsigned char month[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};



void main(void) {

    int y, m, d;      // year, month, day

    while ( scanf("%d %d %d", &y, &m, &d) != EOF ) {

        if (
            (  ( (y%4 == 0) && y%100 ) || (y%400 == 0)  )  &&  ( (m!=1) && (m!=2) )
        ) {
            d++;
        }

        getchar();
        // printf("%d %d %d\n", y, m, d);


        for (; m > 1; --m) {
            d += month[m-2];
        }




        printf("该日期是这一年中的第%d天\n", d);


    }   // end of while


    // while ( scanf("%d %d %d", &y, &m, &d) == EOF ) { puts("EOF entered!"); }




}
