#include "stdio.h"






void main(void) {



    int i, o;


    while (
        scanf("%d", &i),
        getchar(),
        i != 0
    ) {

        for (o = 0; i != 0; i/=10) {
            o = (o * 10)  +  (i % 10);
        }
        printf("%d\n", o);
    }




}
