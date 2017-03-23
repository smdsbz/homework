/******************************************************************************
文 件 名    U201610136\ 朱晓光_HW02.c
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题1.1
截止日期    2017年3月3日

简述：
    本程序将无符号长整型译为其对应的IP地址
******************************************************************************/



#include "stdio.h"

// 无符号长整型位数（made static）
#define LEN     32
// 即 00000000 00000000 00000000 11111111
#define MASK    255UL




int main(void) {

    int total_count;    // 数据总组数
    unsigned long current;  // 存储当前输入数据
    char i; // 循环控制变量


    scanf("%d", &total_count);
    // 限制 - 输入的数据组数必须大于0
    if (total_count < 0) { puts("negative count!"); return 0; }


    for (; total_count > 0; --total_count) {

        // 每次循环输入一次 - 一行输入一行输出
        scanf("%ld", &current);



        // 笨办法 - 从左至右依次输出

        printf("%ld.", (current&MASK));

        // 输出一次，加工一次数据 - mask不动
        current >>= 8;
        printf("%ld.", (current&MASK));

        current >>= 8;
        printf("%ld.", (current&MASK));

        current >>= 8;
        printf("%ld\n", (current&MASK));

    }



    return 0;
}
