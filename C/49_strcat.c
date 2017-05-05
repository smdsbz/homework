#include <stdio.h>

#define MAX_LEN     81
#define ROW_CNT     10


//////////////////////////////////////////////////

char * myGets(char *start) {
    char * cur = start;
    while (*cur = getchar(), *cur != '\n') { ++cur; }
    *cur = '\0';
    return start;
}



unsigned myStrlen(char *start) {
    char *cur = start;
    while (*cur) { ++cur; }
    return (unsigned int)(cur - start);
}



char * myStrcat(char *start, unsigned count) {
    unsigned i;
    char *a = start, *b = start;
    while (*a) { ++a; }
    // finished first line

    for (i = 1; i < count; ++i) {
        for (b = start + i * MAX_LEN; *b; ++b, ++a) {
            *a = *b;
        }
    }

    *a = 0;

    return start;
}


//////////////////////////////////////////////////

int main(int argc, char const *argv[]) {

    unsigned n, i;


    char strings[ROW_CNT][MAX_LEN] = {0};




    while (scanf("%u", &n), getchar(), n && n<ROW_CNT) {

        for (i = 0; i < n; ++i) {
            myGets(strings[i]);
        }

        myStrcat(*strings, n);

        printf("%s\n", *strings);



    }





    return 0;
}
