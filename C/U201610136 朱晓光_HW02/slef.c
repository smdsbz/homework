#include "stdio.h"



#define SIZE    5


void print_array(int * storage) {
    unsigned char i = 0;
    for (i; i < SIZE; ++i) {
        printf("%d ", *(storage+i));
    }
    putchar('\n');
}



void selectSort(int * array) {

    unsigned char i, j;
    unsigned char min_index;

    for (i = 0; i < SIZE; ++i) {

        min_index = i;

        // get index of minimum number
        for (j = i; j < SIZE; ++j) {
            // if smaller, change min_index
            min_index = (array[j] < array[min_index]) ? j : min_index;
        }

        // swap if needed
        if (min_index > i) {
            array[i] += array[min_index];
            array[min_index] = array[i] - array[min_index];
            array[i] -= array[min_index];
        }

    }   // end of main loop

}



void main(void) {


    int storage[SIZE] = {0};
    unsigned char i;    // loop var
    int * left, right;  // pointer | marker


    printf("Give me %d integers to sort:\n", SIZE);

    // input
    for (i = 0; i < SIZE; ++i) {
        scanf("%d", storage+i);
        getchar();
    }


    puts("\nNow sorting...\n");

    selectSort(storage);

    puts("The moment of truth!\n");

    print_array(storage);
}
