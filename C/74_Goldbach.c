#include "stdio.h"





// Stupid Approach - 4 to 100? hard-core hack!!!
unsigned char prime[] = {
    2, 3, 5, 7, 11, 13, 17, 19,
    23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79,
    83, 89, 97
};

#define TOTAL_OF_PRIME  25



void main(void) {

    unsigned char total_count;
    scanf("%hhu", &total_count);



    unsigned char cur;      // stores current target


    unsigned char i, j;     // loop var
    unsigned char flag;



    for (; total_count != 0; --total_count) {

        scanf("%hhu", &cur);

        // user input regulation
        if (cur < 4 || cur > 100) {
            puts("Out of range! Try again!");
            ++total_count;
            continue;
        }


        flag = 1;


        for (i=0; i < TOTAL_OF_PRIME && flag; ++i) {
            for (j=0; j < TOTAL_OF_PRIME && flag; ++j) {

                if (cur == prime[i] + prime[j]) {
                    printf("%hhu=%hhu+%hhu\n", cur, prime[i], prime[j]);
                    flag = 0;
                }

            }   // end of second num
        }   // end of first num





    }   // endfor



}
