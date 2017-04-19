#include <stdio.h>



unsigned hex2dec(char *);


void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();


    char sHex[79] = {'\0'};
    // unsigned uDec = 0;


    for (; N != 0; --N) {

        scanf("0x%s", sHex); getchar();

        // puts(sHex);

        printf("%u\n", hex2dec(sHex));

    }


}



unsigned hex2dec(char * hex) {

    unsigned result = 0;
    unsigned char i;    // loop var

    for (i = 0; hex[i] != '\0'; ++i) {

        result <<= 4;

        if (hex[i]<='Z' && hex[i]>='A') {
            result += 10 + hex[i] - 'A';
        }
        else if (hex[i]<='z' && hex[i]>='a') {
            result += 10 + hex[i] - 'a';
        }
        else if (hex[i]<='9' && hex[i]>='0') {
            result += hex[i] - '0';
        }
        else {
            puts("This message should not appear!");
        }

    }

    return result;

}
