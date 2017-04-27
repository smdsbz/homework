#include<stdio.h>
#define M 10
#define N 3
int main(void)
{
    int a[M];
    int i, j, k;                        /* 这里j为报数，k用来给标记计数，i用来做遍历变量 */
    for (i = 0; i < M; i++)	{           /* 对圈中人按顺序编号1—M */
        a[i] = i + 1;
    }

    i = 0, j = 1;
    while (1) {
        if (a[i]) {                         /* a[i]非零 -> 仍在圈里 */
            if (j == N) {                   /* 数到3 */
                printf("%6d", a[i]);
                j = 1;                      /* j重置 */
                a[i] = 0;                   /* 做标记 */
                ++k;                        /* 计数器++ */
            }
            else {
                ++j;
            }
            if (k == M) { break; }
        }
        if (++i == M) { i = 0; }            /* 循环变量处理 - 不管当前元素在不在圈内，指针都要往前走 */
    }
    putchar('\n');
    return 0;
}
