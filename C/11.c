#include "stdio.h"



int main(void) {

    int total_count;
    unsigned short x, m, n;

    unsigned short mask = 0;
    unsigned short i;   // loop var



    scanf("%d", &total_count);
    if (total_count < 0) { puts("negative input!"); return 0; }



    for (; total_count > 0; --total_count) {

        scanf("%hu %hu %hu", &x, &m, &n);

        if (m>15)    { puts("m out of range!"); ++total_count; continue; }
        if (n>16-m)  { puts("n out of range!"); ++total_count; continue; }
        // and of course they are both above 0 (for they're unsigned)


        // make a mask
        mask = 1U << m;
        for (i=0; i<n; ++i) {
            mask |= mask << 1;
        }
        // printf("%hu\n", mask);



        printf("%hu\n", (x&mask)<<(16-m-n));

    }

    return 0;
}
