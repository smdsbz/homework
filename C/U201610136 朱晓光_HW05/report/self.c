#include <stdio.h>
unsigned char str2int(char c) {
    return c - '0';
}
void getFromArray(char oper[], int * array) {
    unsigned char start = 0, end = 0;
    unsigned i;
    if (oper[0] != '[') {
        for (i = 0; oper[i]; ++i) {
            start += str2int(oper[i]);
        }
        printf("%4d\n", array[start]);
        return;
    }
    for (i = 1; oper[i] != ':'; ++i) {
        start += str2int(oper[i]);
    }
    for (++i; oper[i] != ']'; ++i) {
        end += str2int(oper[i]);
    }
    for (i = start; i < end-1; ++i) {
        printf("%4d", *(array + i%5) );
    }
    printf("%4d\n", *(array + i%5));
    return;
}
void main(void) {
    int array[5] = {1, 2, 3, 4, 5};
    char oper[10] = {'\0'};
    while (scanf("%s", oper), getchar(), oper[0] != 'q') {
        getFromArray(oper, array);
    }
}
