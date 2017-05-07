#include <stdio.h>
#define N   20  // real
#define M   10  // frac
//////////////////////////////////////
typedef struct {
    char   num[N+M];    // 数据
    // unsigned        magnitude;  // 小数点位数：已确定，不需要
} MyFloat;
//////////////////////////////////////
/* TODO: 由于题目声明了数据位数相同，且占满给定位数，故不考虑其他情况 */
/* 如：无数位对齐 */
void getMyFloat(MyFloat *num) {
    unsigned i = 0;
    char buf;   // 防止吞'\n'时干扰别的内存区域
    while ((buf = getchar() - '0') != '\n' - '0') {
        num->num[i] = buf;
        // 用下一位数据覆盖小数点
        if (num->num[i] == '.' - '0') { continue; }
        else { ++i; }
    }
}
void addMyFloat(MyFloat a, MyFloat b) {
    char nums[N+M+1] = {0};
    int i = M + N - 1;
    char carry = 0;
    for (; i >= 0; --i) {
        nums[i+1] = a.num[i] + b.num[i] + carry;
        if (nums[i+1] >= 10) {
            carry = 1;
            nums[i+1] -= 10;
        }
        else {
            carry = 0;
        }
    }
    if (carry) { nums[0] = 1; }
    else { nums[0] = 0; }
    // output
    i = 0;
    if (nums[0] == 0) { ++i; }
    for (; i < M+N+1; ++i) {
        printf("%hhd", nums[i]);
        if (i == N) { putchar('.'); }
    }
    putchar('\n');

}
//////////////////////////////////////
int main(int argc, char const *argv[]) {
    MyFloat a, b;
    getMyFloat(&a);
    getMyFloat(&b);
    addMyFloat(a, b);
    return 0;
}
