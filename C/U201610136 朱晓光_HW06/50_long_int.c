#include <stdio.h>




void num2Hexstr(char c) {
    /*  Print out directly

        ARGS:
            char c: a number
    */
    if (c<10 && c>=0) {
        putchar(c+'0');
    }
    else if (c>9 && c<16) {
        putchar(c+'A'-10);
    }
    else {
        puts("This should not show!!!");
        printf("%hhd", c);
    }
    return;
}




void printHex(char one_two) {
    /*  Print out two parts of the number
        ARGS:
            char one_two:   ****-****
    */
    num2Hexstr(
        (one_two >> 4) & 0x0F
    );
    putchar(' ');
    num2Hexstr(
        (one_two & 0x0F)
    );
    return;
}





void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();


    long num;       // ****-**** ****-**** ****-**** ****-****
    char * ruler;   // ****-****

    unsigned char i;


    for (; N; --N) {

        scanf("%ld", &num); getchar();

        for (i = 4, ruler = (char *)&num+3; i; --i, --ruler) {
            printHex(*ruler);
            if (i != 1) { putchar(' '); }
            else { putchar('\n'); }
        }

    }
}
