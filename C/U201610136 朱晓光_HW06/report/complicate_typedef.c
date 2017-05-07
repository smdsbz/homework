#include <stdio.h>
#include <string.h>
char * strstrpp(const char *a, const char *b) {
    return strstr(a, b) + 1;
}
typedef char *(*p[2])(const char *,const char *);
int main(int argc, char const *argv[]) {
    p some_func;
    some_func[0] = strstr;
    some_func[1] = strstrpp;
    char a[] = "Hello";
    char b[] = "ll";
    printf("%s\n", some_func[0](a, b));
    printf("%s\n", some_func[1](a, b));
    return 0;
}
