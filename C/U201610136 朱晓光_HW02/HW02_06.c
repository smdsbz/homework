/******************************************************************************
文 件 名    HW02_06
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题2.6

简述：
  选择排序
******************************************************************************/



#include "stdio.h"


// 需要排序的数字个数在这里修改
#define SIZE    5



/*
 * 函数介绍：
 *     打印数组
 * 输入参数：
 *     int *: 数组首元素地址
 * 输出参数：
 *     无
 */
void print_array(int * storage) {
    unsigned char i = 0;
    for (i; i < SIZE; ++i) {
        printf("%d ", *(storage+i));
    }
    putchar('\n');
}


/*
 * 函数介绍：
 *     选择排序（直接用指针操作源数据）
 * 输入参数：
 *     int *: 数组首元素地址
 * 输出参数：
 *     无
 */
void selectSort(int * array) {

    unsigned char i, j;
    unsigned char min_index;

    for (i = 0; i < SIZE; ++i) {

        min_index = i;

        // 获得剩余未排序序列中最小数的编号
        for (j = i; j < SIZE; ++j) {
            min_index = (array[j] < array[min_index]) ? j : min_index;
        }

        // 如果之后的序列中有比当前元素更小的，则交换
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


    printf("Give me %d integers to sort:\n", SIZE);

    // 输入
    for (i = 0; i < SIZE; ++i) {
        scanf("%d", storage+i);
        getchar();
    }


    puts("\nNow sorting...\n");

    // 排序
    selectSort(storage);

    puts("The moment of truth!\n");

    // 输出
    print_array(storage);

}
