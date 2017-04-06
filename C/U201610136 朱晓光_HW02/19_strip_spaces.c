#include "stdio.h"


void main(void) {


    unsigned char N;    // total count
    scanf("%hhu", &N);
    getchar();

    char str[100] = {'\0'};     // stores user input - 99 chars + '\0'
    unsigned char fp = 0;       // pointer
    // unsigned char flag;         // space status flag




    for (; N != 0; --N) {

        for (
            fp = 0;
            ((str[fp]=getchar()) != '\n')  &&  fp<99;
            ++fp
        )   {
            continue;
        }


        str[++fp] = '\0';






        // check if user entered \n without any other characters
        if (str[0] != '\0') {

            putchar(str[0]);

            for (fp = 1; str[fp] != '\0'; ++fp) {

                // previous not space
                if (str[fp-1] != ' ') {
                    putchar(str[fp]);
                }
                // previous is space
                else {
                    // 1. current is visible
                    if (str[fp] != ' ') {
                        putchar(str[fp]);
                    }
                    else {
                        continue;
                    }
                }

            }   // end for

        }   // end if - end of output






    }   // end for - end of input





}
