#include <stdio.h>


#define MAX_SIZE    20

void inputArray(int *, unsigned);
void outputArray(int *, unsigned);

void selectSort(int *, unsigned);



void main(void) {

    unsigned count;
    int array[MAX_SIZE] = {0};


    while (
        scanf("%u", &count),
        getchar(),
        count!=0 && count<=MAX_SIZE
    ) {

        inputArray(array, count);

        selectSort(array, count);

        outputArray(array, count);

    }

}



void inputArray(int * a, unsigned size) {
    // puts("[ Running ] inputArray");
    unsigned cnt = 0;
    for (; cnt < size; ++cnt) {
        scanf("%d", a+cnt);
        getchar();
    }

}



void outputArray(int * a, unsigned size) {
    // puts("[ Running ] outputArray");
    unsigned cnt = 0;
    for (; cnt < size-1; ++cnt) {
        printf("%d ", *(a+cnt));
    }
    printf("%d\n", *(a+cnt));

}



void selectSort(int * array, unsigned size) {
    // puts("[ Running ] selectSort");
    if (size == 1) { return; }

    unsigned max_index = 0;
    unsigned i = 1;

    // find index of max
    for (; i < size; ++i) {
        max_index = (array[i] > array[max_index]) ? i : max_index;
    }

    // reusing var i
    i = size - 1;

    // repositioning max number
        // swap only when not at its position
    if (max_index != i) {
        array[i] += array[max_index];
        array[max_index] = array[i] - array[max_index];
        array[i] -= array[max_index];
    }

    // sort remaining numbers
    selectSort(array, i);

}
