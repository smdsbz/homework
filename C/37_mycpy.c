#include <stdio.h>


#define MAX_LEN     999


void mycpy(char *, char *, unsigned);

void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();

    unsigned n;

    char src[MAX_LEN] = {'\0'};
    char tgt[MAX_LEN] = {'\0'};

    for (; N != 0; --N) {

        // myGets
        for (
            n = 0;
            src[n] = getchar(), src[n] != '\n';
            ++n);


        // scanf("%s", src); getchar();
        // puts("src read");
        scanf("%u", &n); getchar();
        // puts("n read");
        mycpy(tgt, src, n);

        printf("%s\n", tgt);

    }


}



void mycpy(char *s, char *t, unsigned n) {

    s[n] = '\0';

    for (; n != 0; --n) {
        s[(int)n-1] = t[(int)n-1];
    }

}
