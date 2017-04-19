#include <stdio.h>
#include <string.h>


int isReversible(char *, unsigned, unsigned);


void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();

    char s[81] = {'\0'};
    // char flag = 1;


    for (; N != 0; --N) {

        scanf("%s", s); getchar();

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
        }

    }

}





int isReversible(char * s, unsigned start, unsigned end) {

    unsigned i;     // loop var

    if (start >= end) {
        return 1;
    }
    else if (s[start] != s[end]) {
        return 0;
    }
    else {
        return isReversible(s, start+1, end-1);
    }

}
