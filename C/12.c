/******************************************************************************
文 件 名    HW01_01
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题1.1
截止日期    2017年3月3日

简述：
    本程序将无符号长整型译为IP地址
******************************************************************************/



#include "stdio.h"

// length of unsigned long int (made static)
#define LEN     32
// i.e. 00000000 00000000 00000000 11111111
#define MASK    255UL




int main(void) {

    int total_count;
    unsigned long current;
    char i; // loop var


    scanf("%d", &total_count);
    // regulation: count should be positive
    if (total_count < 0) { puts("negative count!"); return 0; }


    for (; total_count > 0; --total_count) {

        scanf("%ld", &current);

        printf("%ld.", (current&MASK));

        current >>= 8;
        printf("%ld.", (current&MASK));

        current >>= 8;
        printf("%ld.", (current&MASK));

        current >>= 8;
        printf("%ld\n", (current&MASK));

    }



    return 0;
}
