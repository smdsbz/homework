/******************************************************************************
文 件 名    HW02_03
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题2.3

简述：
  计算个人所得税
******************************************************************************/


#include "stdio.h"


/* 函数原型：使用if计算个人所得税 */
double using_if(double);
/* 函数原型：使用switch计算个人所得税 */
double using_switch(double);



void main(void) {

    double income;

    while (
        scanf("%lf", &income),
        getchar(),
        income != 0
    ) {
        // 输出对应的个人所得税
        printf("%lf\n", using_switch(income));
    }

}



/*
 * 函数介绍：
 *     用if计算个人所得税
 * 输入参数：
 *     double income: 收入
 * 输出参数：
 *     unsigned short: 个人所得税
 */
double using_if(double income) {

    double tax = 0;


    if (income > 5000) {
        tax += (income-5000)*0.25L;
        income = 5000;
    }
    if (income > 4000) {
        tax += (income-4000)*0.20L;
        income = 4000;
    }
    if (income > 3000) {
        tax += (income-3000)*0.15L;
        income = 3000;
    }
    if (income > 2000) {
        tax += (income-2000)*0.10L;
        income = 2000;
    }
    if (income > 1000) {
        tax += (income-1000)*0.05L;
        income = 1000;
    }
    else {
        tax = 0;
    }

    return tax;
}


/*
 * 函数介绍：
 *     用switch计算个人所得税
 * 输入参数：
 *     double income: 收入
 * 输出参数：
 *     unsigned short: 个人所得税
 */
double using_switch(double income) {

    double tax = 0;

    // TODO: 直接计算出结果表达式
    switch ((int)(income/1000)) {
        case 4: {
            tax = (income-4000)*0.20L + 1000*0.15L + 1000*0.10L + 1000*0.05L;
            break;
        }
        case 3: {
            tax = (income-3000)*0.15L + 1000*0.10L + 1000*0.05L;
            break;
        }
        case 2: {
            tax = (income-2000)*0.10L + 1000*0.05L;
            break;
        }
        case 1: {
            tax = (income-1000)*0.05L;
            break;
        }
        case 0: {
            tax = 0;
            break;
        }
        default: {
            tax = (income-5000)*0.25L + 1000*0.20L + 1000*0.15L + 1000*0.10L + 1000*0.05L;
            break;
        }
    }

    return tax;


}
