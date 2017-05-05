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



void swapNumbers(int *a, int *b) {
    *b += *a;
    *a = *b - *a;
    *b -= *a;
    return;
}


void bubbleSort(int *nums) {

    int *outer = nums, *inner = nums;

    for (; outer-nums > )


}





int main(int argc, char const *argv[]) {

    int nums[NUM_CNT] = {0};

    while (getNumbers(nums)) {





    }





    return 0;
}
