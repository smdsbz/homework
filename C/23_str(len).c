#include "stdio.h"



unsigned short myStrlen(char *);
/* return length of the string
 */



void main(void) {


    unsigned char   N;  // total count
    scanf("%hhu", &N); getchar();   // get total count


    char str[121] = {'\0'};     // buffer
    char * p = str;            // pointer


    for (; N != 0; --N) {



        // myGetS()
        for (
            p = str;

            *p = getchar(),
            *p != '\n';

            ++p
        ) {;}
        *p = '\0';




        // printf("%s\n", str);

        printf("%hu\n", myStrlen(str));

    }

}



unsigned short myStrlen(char * current) {
    // putchar(*current);
    if (*current == '\0') { return 0; }
    else { return myStrlen(current+1) + 1; }

}
