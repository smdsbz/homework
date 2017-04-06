/******************************************************************************
文 件 名    HW02_04
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题2.4

简述：
  HTML风格空格处理
******************************************************************************/

#include "stdio.h"


void main(void) {


    unsigned char N;    // total count
    // 输入总数据组数
    scanf("%hhu", &N);
    getchar();

    char str[100] = {'\0'};     // stores user input - 99 chars + '\0'
    unsigned char fp = 0;       // pointer


    for (; N != 0; --N) {


        // 用重写的 gets() 读入一行字符串
        for (
            fp = 0;
            ((str[fp]=getchar()) != '\n')  &&  fp<99;
            ++fp
        )   {
            continue;
        }
        // 字符串以空字符结尾
        str[++fp] = '\0';


        // 若用户什么也没输入就直接回车，则结束本次循环
        if (str[0] != '\0') {

            // 第一个字符总是要输出的
            putchar(str[0]);

            // 遍历整个字符串
            for (fp = 1; str[fp] != '\0'; ++fp) {

                // 如果前一个字符不是空格 -> 输出当前字符
                if (str[fp-1] != ' ') {
                    putchar(str[fp]);
                }
                // 如果前一个字符是空格：
                else {
                    // 1. 当前字符不是空格 -> 输出
                    if (str[fp] != ' ') {
                        putchar(str[fp]);
                    }
                    // 2. 当前字符是空格 -> 不输出
                    else {
                        continue;
                    }
                }

            }   // end for

        }   // end if - end of output loop



    }   // end for - end of main loop





}
