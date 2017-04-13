#include "stdio.h"
#include "second.h"
int * copy(int *);
void main(void) {
    int array[5] = {1, 2, 3, 4, 5};
    printf("%p -> %d\n", &array[2], array[2]);
    printf("%p -> %d\n", &copy(&array[1])[2], copy(&array[1])[2]);
}
