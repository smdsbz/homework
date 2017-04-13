#include "stdio.h"
long sum_fac(int);
void main(void)
{
    int k;
    for(k=1;k<6;k++)
         printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
}

/* original ver *
long sum_fac(int n)
{
    long s=0;
    int i;
    long fac=1;
    for(i=1;i<=n;i++) {
        fac*=i;
        s+=fac;
    }
    return s;
}
*/

/* OJ ver *
long sum_fac(int n) {

    static long sum = 0;
    static long tmp = 1;

    tmp *= n;
    sum += tmp;

    return sum;

}
*/

// /* 2nd task *
long sum_fac(int n)
{
    long s=0;
    int i;
    long fac=1;
    for(i=1;i<=n;i++) {
        fac*=i;
        s+=fac;
    }
    return s;
}
// */
