#include <stdio.h>
#include <stdlib.h>
#define isLowerCase(c)  ( ((c)<='z' && (c)>='a') ? 1 : 0 )
void lowerToUpper(char *c) { *c = *c + 'A' - 'a'; }
void capitalize(char *str) {
    if (!str) { return; }
    // first char
    if (isLowerCase(*str)) { lowerToUpper(str); }
    for (++str; *str; ++str) {
        if (*(str-1)==' ' && isLowerCase(*str)) { lowerToUpper(str); }
    }
    return;
}
void main(void) {
    char str[81] = {0};
    char *buf = str;
    for (; (*buf=getchar()) != '\n'; ++buf) ;
    *buf = 0;
    capitalize(str);
    printf("%s\n", str);
    FILE *fp;
    #ifdef __WIN32__
    fp = fopen(".\\test", "w+");
    #elif linux
    fp = fopen("./test", "w+");
    #else
    puts("OS type not recognized!");
    exit(-1);
    #endif
    fputs(str, fp);
    fclose(fp);
}
