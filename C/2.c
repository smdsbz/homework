#include "stdio.h"

int main(void) {
    int a, flag;
    
    while(scanf("%d", &a) == 1) {
        
        flag = 0;
        
        if(!(a%5))  flag += 1;
        if(a == (a/3)*3)  flag += 1;
        
        if(flag == 2) { printf("1\n"); }
        else if(flag==0 || flag==1) { printf("0\n"); }
        else { printf("Don't mess up with my code!"); }
    }
    
    return 0;
}

