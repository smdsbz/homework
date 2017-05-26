#include <stdio.h>
int main()
{


    int a = 0x80000000;
    printf("os is%d\t%d\n",a,sizeof(int));
    union ut
    {
        short s;
        char c[2];
    } u;
    if(sizeof(short) == 2)
    {
        u.s = 0x0102;
        if(u.c[0] == 1 && u.c[1] == 2)
        {
            printf("big enidan\n");
        }
        else if(u.c[0] == 2 && u.c[1] == 1)
        {
            printf("little endian.\n");
        }
        return 0;
    }
    return 0;
}
