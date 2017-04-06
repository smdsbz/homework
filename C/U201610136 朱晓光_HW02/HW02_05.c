/******************************************************************************
文 件 名    HW02_05
作    者    朱晓光
班    级    计科校交1601
学    号    U201610136
邮    箱    694066681@qq.com, U201610136@hust.edu.cn
课    程    C语言程序设计
作 业 号    习题2.5

简述：
  求方程 f(x) = 3*x^3 - 4*x^2 - 5*x + 13 的近似根
******************************************************************************/



#include "stdio.h"


// 精度
#define EPSION     10e-6


/* 原函数 */
#define original(x)     ( 3*(x)*(x)*(x) - 4*(x)*(x) - 5*(x) + 13 )
/* 原函数的导数 */
#define derivative(x)   ( 9*(x)*(x)     - 8*(x)     - 5 )
/* 计算 X(k+1) */
#define yield(x)        ( x - original((x)) / derivative((x)) )



/*
 * 函数介绍：
 *     计算绝对值
 * 输入参数：
 *     double x: 原数
 * 输出参数：
 *     double x: 绝对值
 */
double myAbs(double x) {
    if (x > 0) { return x; }
    else { return -x; }
}



void main(void) {


    double a = -1.5;   // start point
    double previous, current = 0;   // storage

    previous = a;


    for (; myAbs(previous - current) > EPSION;) {
        // 当前数作为下一轮的比较值
        previous = current;
        // 用公式计算下一轮的比较值
        current = yield(previous);
    }

    printf("%lf\n", current);

}
