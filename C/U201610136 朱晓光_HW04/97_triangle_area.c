#include <stdio.h>
#include <math.h>
#define S(a, b, c)          ( (a)+(b)+(c) ) >> 1
#define AREA(s, a, b, c)    sqrt( (s) * ((s)-(a)) * ((s)-(b)) * ((s)-(c)) )
void main(void) {
    unsigned a, b, c;
    while (
        scanf("%u %u %u", &a, &b, &c) == 3
    ) {
        getchar();
        printf(
            "%u %lf\n",
            S(a, b, c),
            AREA(S(a, b, c), a, b, c)
        );
    }
}
