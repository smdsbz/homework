#include "stdio.h"



#define PI      3.1415926


void main(void) {
    
    unsigned char N;    // total data count
    scanf("%hhu", &N);
    
    
    double r, h;


    for (; N != 1; --N) {

        scanf("%lf %lf", &r, &h);

        printf("%.6f %.6f\n", 
                2 * PI * r * (r + h),
                PI * r * r * h
              );

    }

}
