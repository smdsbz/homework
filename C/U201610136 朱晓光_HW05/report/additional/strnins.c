#include <stdio.h>
unsigned myStrlen(char s[]) {
    unsigned i;
    for (i = 0; s[i]; ++i) ;
    return i;
}
char * strnins(char s[], char t[], unsigned n) {
    if (n > myStrlen(s)) { return NULL; }
    unsigned i, j = myStrlen(t);
    // 挪动s中n之后的元素
    for (i = myStrlen(s)-1; i >= n; --i) {
        s[i+j] = s[i];
    }
    // 在挪出来的空位中填充t
    for (i = n; t[i-n]; ++i) {
        s[i] = t[i-n];
    }
    return s;
}
void main(void) {
    char s[20] = "abcdefg", t[20] = "123";
    puts(strnins(s, t, 2));
}
