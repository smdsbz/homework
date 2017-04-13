#include <stdio.h>
#include "file2.h"
int x,y;
char ch;
void func1(void);
void main(void)
{
    x=10;
    y=20;
    ch=getchar();
    printf("in file1 x=%d,y=%d,ch is %c\n",x,y,ch);
    func1();
}
