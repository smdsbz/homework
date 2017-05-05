#include <stdio.h>


#define NUM_CNT     10



int getNumbers(int *nums) {
    unsigned i = 0;
    for (; i < NUM_CNT; ++i) {
        if (scanf("%d", nums+i) == 1) { getchar(); }
        else { goto end; }
    }
    return 1;
    end:
    return 0;
}


void putNumbers(int *nums) {
    unsigned i = 0;
    for (; i < NUM_CNT; ++i) {
        printf("%d", nums[i]);
        if (i == NUM_CNT-1) { putchar('\n'); }
        else { putchar('-'); putchar('>'); }
    }
}




/*
void swapNumbers(int *a, int *b) {
    *b += *a;
    *a = *b - *a;
    *b -= *a;
    return;
}
*/

void bubbleSort(int *nums) {

    int *outer = nums, *inner = nums;

    for (; outer-nums < NUM_CNT-1; ++outer) {
        for (inner = nums; inner-nums < NUM_CNT-(outer-nums)-1; ++inner) {
            if (*inner > *(inner+1)) {
                *(inner+1) += *inner;
                *inner = *(inner+1) - *inner;
                *(inner+1) -= *inner;
            }
        }
    }


}





int main(int argc, char const *argv[]) {

    int nums[NUM_CNT] = {0};

    while (getNumbers(nums)) {

        bubbleSort(nums);

        putNumbers(nums);

    }





    return 0;
}
