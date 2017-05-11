#include "stdio.h"
char *strcpy(char *,char *);
void main(void)
{
    char a[20],b[60]="there is a boat on the lake.";
    printf("%s\n",strcpy(a,b));

}
char *strcpy(char *s,char *t)
{
    // TODO: added line below
    char *original = s;
    while(*s++=*t++)
    ;
    // TODO: modified line below
    return (original);
}
