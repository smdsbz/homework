#include <stdio.h>
void main(void)
{
int i,n,s=1;
  printf("Please enter s:");
  scanf("%d", &n);
  for (i=1; s<n; i++)
     s=s*i;
  printf("n=%d\n",i-1);
}
