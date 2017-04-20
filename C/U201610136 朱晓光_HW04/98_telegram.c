#include <stdio.h>

// online ver.
#define CHANGE(c)   ( (c) % 2 )
// report ver.
// #define CHANGE(c)   0


/* alterCase:
 *   lower case --> upper case
 *   upper case --> lower case
 *   non-alphabetic --> original
 */
char alterCase(char);


void main(void) {

    unsigned N;

    scanf("%u", &N); getchar();



    char current;
    unsigned char change_flag;


    for (; N > 0; --N) {

        // get flag from first char
        current = getchar();
        change_flag = CHANGE(current);

        // dealing with every char
        for (; current != '\n'; current = getchar()) {

            switch (change_flag) {

                case 0: {
                    putchar(current);
                    break;
                }

                case 1: {
                    putchar(alterCase(current));
                    break;
                }

                default: {
                    puts("This message should not appear!");
                    return;
                }

            }   // end of switch

        }

        // output the final \n
        putchar('\n');


    }   // end of main loop



}




char alterCase(char c) {

    if (c<='Z' && c>='A') {
        return c - 'A' + 'a';
    }
    else if (c<='z' && c>='a') {
        return c - 'a' + 'A';
    }
    else {
        return c;
    }

}
