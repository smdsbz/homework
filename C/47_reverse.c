#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////

void getArray(int * array, unsigned count) {
    unsigned i = 0;
    for (; i < count; ++i) {
        scanf("%d", array+i); getchar();
    }
}



void printArray(int * array, unsigned count) {
    unsigned i = 0;
    for (; i < count; ++i) {
        printf("%d", array[i]);
        if (i == count-1) { putchar('\n'); }
        else { putchar(' '); }
    }
}


void reverseArray(int * array, unsigned count) {
    unsigned i = 0;
    for (; i < count/2; ++i) {
        // exchange
        *(array+count-1-i) += *(array+i);
        *(array+i) = *(array+count-1-i) - *(array+i);
        *(array+count-1-i) -= *(array+i);
    }
}



//////////////////////////////////////////////////

void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();



    unsigned count;
    unsigned i;         // loop var


    // int * array = NULL;
    int array[120] = {0};




    for (; N; --N) {

        scanf("%u", &count); getchar();

        // array = (int *)malloc(count * sizeof(int));

        getArray(array, count);

        // printArray(array, count);

        reverseArray(array, count);

        printArray(array, count);


        // for (; count; --count) {
        //     free(array+count-1);
        // }
    }


}
