#include "stdio.h"


// 精度
#define EPSION     10e-6


#define original(x)     ( 3*(x)*(x)*(x) - 4*(x)*(x) - 5*(x) + 13 )
#define derivative(x)   ( 9*(x)*(x)     - 8*(x)     - 5 )

#define yield(x)        ( x - original((x)) / derivative((x)) )




double myAbs(double x) {
    if (x > 0) { return x; }
    else { return -x; }
}



void main(void) {


    double a = -1.5;   // start point
    double previous, current = 0;   // storage

    // scanf("%lf", &a); getchar();
    previous = a;


    for (; myAbs(previous - current) > EPSION;) {
        previous = current;
        current = yield(previous);
    }

    printf("%lf\n", current);

}
