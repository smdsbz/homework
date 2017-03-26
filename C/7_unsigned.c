#include "stdio.h"

void main(void) {

    unsigned char N;    // total data count
    scanf("%hhu", &N);

    
    unsigned short cur; // current data
    // unsigned short rst; // result

    for (; N != 0; --N) {

        scanf("%hu", &cur);

        printf("%hu\n",
                (cur&0xf000)>>12 | (cur&0x000f)<<12 | (cur&0x0ff0)
              );

    }

}
