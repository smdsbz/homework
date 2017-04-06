/******************************************************************************
文 件 名    HW02_01
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题2.1

简述：
  打印杨辉三角形
******************************************************************************/


#include "stdio.h"



/* 函数原型：计算组合数 */
unsigned short combination(unsigned char, unsigned char);



void main(void) {


    unsigned char size;

    unsigned char i, j;     // loop var



    while (
        scanf("%hhu", &size),
        getchar(),
        size != 0 && size <= 12
    ) {

        // 第i行
        for (i = 1; i <= size; ++i) {

            // 第一个元素：1
            printf("%*d", (size-i)*2+1, 1);

            // 第一个元素之后的数字：用组合数公式计算
            for (j = 1; j < i; ++j) {
                printf("%4hu", combination(i-1, j));
            }

            // 该行结束
            putchar('\n');
        }

        // 两个图形之前空一行
        putchar('\n');
    }




}




/*
 * 函数介绍：
 *     计算组合数
 * 输入参数：
 *     unsigned char i: 选择个数
 *     unsigned char j: 总数
 * 输出参数：
 *     unsigned short: 对应的组合数
 */
unsigned short combination(unsigned char i, unsigned char j) {
    // printf("combination(%hhu,%hhu)\n", i, j);
    if (j == 0) { return 1; }
    else { return combination(i, j-1) * (i-j+1) / j; }
}
