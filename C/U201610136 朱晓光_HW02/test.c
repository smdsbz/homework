#include <stdio.h>
void main(void)
{ 
int i,n,s=1;
  printf("Please enter n:");
  scanf("%d", &n);
  
  /* using for
  for (i=1; i<=n; i++)
     s=s*i;
  */
  
  /* using while 
  i = 1;
  while (i <= n) {
  	s *= i;
  	++i;
  }
  */
  
  //* using do-while 
  i = 1;
  do {
  	s *= i;
  } while (++i, i <= n);
  //*/
  
  printf("%d! = %d",n,s);
}

