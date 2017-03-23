#include<stdio.h>
void main( )
{
    int a, b, t;
    printf("Input two integers:");
    scanf("%d %d",&a,&b);
	b += a, a = b - a, b -= a;
    printf("\na=%d,b=%d",a,b);
}

