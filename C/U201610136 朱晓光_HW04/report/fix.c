#include "stdio.h"
#define SUM (a+b)
#define DIF (a-b)
#define SWAP(a,b)  t=a,a=b,b=t
void main(void)
{
    int a, b, t;
    printf("Input two integers a, b:");
    scanf("%d,%d", &a,&b);
    printf("\nSUM=%d\n the difference between square of a and square of b is:%d",SUM, SUM*DIF);
    SWAP(a,b);
    printf("\nNow a=%d,b=%d\n",a,b);
}
