#include "stdio.h"
void main(void)
{
    // add
    float a;
    // end
    float *p=&a;
    scanf("%f",p);
    printf("%f\n",*p);
}
