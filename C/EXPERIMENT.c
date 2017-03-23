#include "stdio.h"

void main(void) {
    puts("Here's a third: ");
    float pocket = 1./3;
    printf("%f\n", pocket);


    puts("\nnow times it with 7 and then subtracts it with 2 like craaaaazy!");
    puts("(Note: in analog env, a third will still be a third)");

    unsigned long times_to_repeat = -1;
    printf("\nHow many times should I repeat this operation? ");
    scanf("%ld", &times_to_repeat);


    // start!
    for (; times_to_repeat != 0; --times_to_repeat) {
    	pocket *= 7;
    	pocket -= 2;
        printf("Clerk: Here's your bill: %f\n", pocket);
    }
    
    

}
