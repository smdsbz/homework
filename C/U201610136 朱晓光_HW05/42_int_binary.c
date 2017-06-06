#include <stdio.h>
void printBits(int, char *);
void main(void) {
    unsigned N;
    scanf("%u", &N); getchar();
    int nums[120] = {0};
    char strNums[sizeof(int)*8+1] = {'\0'};
    unsigned i;
    for (i = 0; i < N; ++i) {
        scanf("%d", (nums + i));
    }
    for (i = 0; i < N; ++i) {
        printBits(nums[i], strNums);
    }
}
void printBits(int dec, char *str) {
    int cur;
    for (cur = sizeof(int)*8-1; cur >= 0; --cur) {
        str[sizeof(int)*8-1-cur] = ( ( dec & (1<<cur) ) ? '1' : '0' );
    }
    str[sizeof(int)*8] = 0;
    printf("%s\n", str);
}
