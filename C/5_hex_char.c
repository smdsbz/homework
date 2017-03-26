#include "stdio.h"

void main(void) {


    unsigned char N;
    scanf("%hhu", &N);


    char cur;


    for (; N != 0; --N) {
        getchar();
        scanf("%c", &cur);

        if (cur>='0' && cur<='9') {
            printf("%d\n", cur-'0');
        }
        else if (cur>='a' && cur<='f') {
            printf("%d\n", cur-'a'+10);
        }
        else if (cur>='A' && cur<='F') {
            printf("%d\n", cur-'A'+10);
        }
        else {
            printf("%d\n", (int)cur);
        }

    }


}
