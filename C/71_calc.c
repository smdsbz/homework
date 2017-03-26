#include "stdio.h"



void using_if_else(double, double, char);
void using_switch(double, double, char);




void main(void) {


    // unsigned char N = 4;    // total count - 4 by default
    // scanf("%hhu", &N);



    char t;        // process type
    double a, b;            // the two operands
    char oper;              // operator




    scanf("%c %lf %lf %c", &t, &a, &b, &oper);
    getchar();


    switch (t) {

        case '0': {
            using_if_else(a, b, oper);
            break;
        }

        case '1': {
            using_switch(a, b, oper);
            break;
        }

        case '2': {
            using_if_else(a, b, oper);
            using_switch(a, b, oper);
            break;
        }
    }   // end switch


    while ((t=getchar()) != EOF) {



        scanf("%lf %lf %c", &a, &b, &oper);
        getchar();

        switch (t) {

            case '0': {
                putchar('\n');
                using_if_else(a, b, oper);
                break;
            }

            case '1': {
                putchar('\n');
                using_switch(a, b, oper);
                break;
            }

            case '2': {
                putchar('\n');
                using_if_else(a, b, oper);
                using_switch(a, b, oper);
                break;
            }
        }   // end switch


    }





}







void using_if_else(double a, double b , char oper) {

    printf("After if-else processing,the result is : ");

    if (oper == '+') { printf("%.2lf\n", a+b); }

    else if (oper == '-') { printf("%.2lf\n", a-b); }

    else if (oper == '*') { printf("%.2lf\n", a*b); }

    else if (oper == '/') {
        if (b<1e-5 && b>-(1e-5)) {
        }
        else {
            printf("%.2lf\n", a/b);
        }
    }

    return;

}







void using_switch(double a, double b , char oper) {

    printf("After switch processing,the result is : ");


    switch (oper) {

        case '+': {
            printf("%.2lf\n", a+b); break;
        }

        case '-': {
            printf("%.2lf\n", a-b); break;
        }

        case '*': {
            printf("%.2lf\n", a*b); break;
        }

        case '/': {

            if (oper == '/') {
                if (b<10e-5 && b>-10e-5) {
                    printf("Zero Division Error!\n");
                    break;
                }
                else {
                    printf("%.2lf\n", a/b);
                    break;
                }
            }

        }   // end case '/'

        default: {
            printf("WTF???\n");
            break;
        }

    }   // end swtich

    return;


}
