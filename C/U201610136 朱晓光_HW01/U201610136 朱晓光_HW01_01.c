/******************************************************************************
文 件 名    U201610136\ 朱晓光_HW01_01.c
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题1.1
截止日期    2017年3月3日

简述：
    本程序输出输入数据x二进制表示的从第m位开始向左的n位，并向左端靠齐
******************************************************************************/




#include "stdio.h"



int main(void) {

    int total_count;    // 数据总组数
    unsigned short x, m, n; // 输入数据单元

    unsigned short mask = 0;    // mask单元
    unsigned short i;   // 循环控制变量


    // 输入数据组数 - 并限制其不能小于0
    scanf("%d", &total_count);
    if (total_count < 0) { puts("negative input!"); return 0; }



    for (; total_count > 0; --total_count) {
        // 一行输入一行输出
        scanf("%hu %hu %hu", &x, &m, &n);

        // 限制m, n范围
        if (m>15)    { puts("m out of range!"); ++total_count; continue; }
        if (n>16-m)  { puts("n out of range!"); ++total_count; continue; }
        // 不需要判断它们是否小于0，因为它们都是无符号的


        // 制作mask
        mask = 1U << m; // mask起点
        for (i=0; i<n; ++i) {
            mask |= mask << 1;  // 一直拖到终点
        }   // endfor


        // 一行输入一行输出
        printf("%hu\n", (x&mask)<<(16-m-n));

    }   // endif

    return 0;
}
