#include <stdio.h>
int checkerboard[8] = {1, 1, 1, 1, 1, 1, 1, 1};
// no need for judging row - only one 'i' in a row
void printCheckerboard(void) {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 1; j <= 8; ++j) {
            putchar((checkerboard[i] == j) ? 'i' : '_');
            putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}
int judge(void) {
    int i, j;
    // column
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (checkerboard[i] == checkerboard[j] && i != j) {
                return 0;
            }
        }
    }
    // pos_diagonal
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (checkerboard[i]+j == checkerboard[j]+i && i != j) {
                return 0;
            }
        }
    }
    // neg_diagonal
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (checkerboard[j]+j == checkerboard[i]+i && i != j) {
                return 0;
            }
        }
    }
    return 1;
}
// simulating octal +1 and carry
int plusOne(int cur) {
    // exit status
    if (cur == -1) { return 0; }
    // no carry
    if (checkerboard[cur] != 8) {
        checkerboard[cur]++;
        return 1;
    }
    // carry
    else if (checkerboard[cur] == 8) {
        checkerboard[cur] = 1;
        // pass value directly
        switch (plusOne(cur-1)) {
            case 0: { return 0; }
            case 1: { return 1; }
            default: { puts("This should not show!"); return -1; }
        }
    }
}
void main(void) {
    int count = 0;
    // no need to judge the first case
    while (plusOne(7)) {
        if (judge()) {
            printCheckerboard();
            ++count;
        }
    }
    printf("total: %d case(s)\n", count);
}
