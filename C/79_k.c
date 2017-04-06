#include "stdio.h"




int getNumberByIndex(unsigned int, unsigned char);
/* success: return the number specified by input
 * fail (i.e. index out of range): return -1
 */


void main(void) {


    unsigned int    n;      // the number
    unsigned char   k;      // start position


    while (
        scanf("%u %hhu", &n, &k) == 2
    ) {
        getchar();      // swallow \n


        printf("%hhd\n", getNumberByIndex(n, k));


    }



}



int getNumberByIndex(unsigned int n, unsigned char k) {

    for (; k > 1; --k) {
        n /= 10;
    }

    if (n) { return n % 10; }
    else { return -1; }

}
