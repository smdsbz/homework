#include "stdio.h"



/*
void main(void) {

    unsigned char score[3] = {0};

    unsigned char i, j;    // index num recorder

    char flag;



    while (
        (scanf("%hhu %hhu %hhu", score, score+1, score+2) != EOF)
    ) {

        getchar();  // absorbs '\n'

        for (i=0; i<3; ++i) {
            flag = 0;
            for (j=0; j<3; ++j) {
                flag += (score[i]>score[j]) ? 1 : -1;
            }
            printf("%hhd\n", flag);
        }





    }


}*/



void main(void) {

    char a, b, c;



    while (
        (scanf("%hhd %hhd %hhd", &a, &b ,&c) != EOF )
    ) {
        getchar();  // absorbs \n


        // TODO: where is your mathematics??
        if (
            (a<=b&&a>=c) || (a<=c&&a>=b)
        )   { printf("A:%hhd\n", a); }
        else if (
            (b<a&&b>=c) || (b<=c&&b>a)
        )   { printf("B:%hhd\n", b); }
        else if (
            (c<a&&c>b) || (c<b&&c>a)
        )   { printf("C:%hhd\n", c); }





    }   // end of while
}
