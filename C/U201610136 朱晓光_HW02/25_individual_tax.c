#include "stdio.h"



double using_if(double);
double using_switch(double);





void main(void) {

    double income;


    while (
        scanf("%lf", &income),
        getchar(),
        income != 0
    ) {
        printf("%lf\n", using_if(income));
    }

}




double using_if(double income) {

    double tax = 0;


    if (income > 5000) {
        tax += (income-5000)*0.25L;
        income = 5000;
    }
    if (income > 4000) {
        tax += (income-4000)*0.20L;
        income = 4000;
    }
    if (income > 3000) {
        tax += (income-3000)*0.15L;
        income = 3000;
    }
    if (income > 2000) {
        tax += (income-2000)*0.10L;
        income = 2000;
    }
    if (income > 1000) {
        tax += (income-1000)*0.05L;
        income = 1000;
    }
    else {
        tax = 0;
    }

    return tax;
}
