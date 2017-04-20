#include <stdio.h>
#include <string.h>



int isReversible(char *, unsigned, unsigned);
/* :param char *:   the string
 * :param unsigned: start index
 * :param unsigned: end index
 * :return int:     1 for yes, 0 for no
 */


void main(void) {

    unsigned N;     // total data count
    scanf("%u\n", &N);

    char s[81] = {'\0'};    // stores the input string


    for (; N != 0; --N) {

        // get string from user input
        scanf("%s", s); getchar();

        // output value
        switch (isReversible(s, 0, strlen(s)-1)) {
            case 0: {
                puts("No!");
                break;
            }
            case 1: {
                puts("Yes!");
                break;
            }
            default: {
                puts("This message should not appear!");
                break;
            }
        }   // end switch

    }   // end of main loop

}





int isReversible(char * s, unsigned start, unsigned end) {

    if (start >= end) {
        // gone over the whole string
        return 1;
    }
    else if (s[start] != s[end]) {
        // incompatible found
        return 0;
    }
    else {
        // next round
        return isReversible(s, start+1, end-1);
    }

}
