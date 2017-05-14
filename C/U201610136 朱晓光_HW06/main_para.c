#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void _sort_asc(int *pArr, int n) {
    int i, j;
    for (i = 0; i < n-1; ++i) {
        for (j = 0; j < n-i-1; ++j) {
            if (pArr[j] > pArr[j+1]) {
                pArr[j+1] += pArr[j];
                pArr[j] -= pArr[j+1];
                pArr[j] *= -1;
                pArr[j+1] -= pArr[j];
            }
        }
    }
}
void _sort_des(int *pArr, int n) {
    int i, j;
    for (i = 0; i < n-1; ++i) {
        for (j = 0; j < n-i-1; ++j) {
            if (pArr[j] < pArr[j+1]) {
                pArr[j+1] += pArr[j];
                pArr[j] -= pArr[j+1];
                pArr[j] *= -1;
                pArr[j+1] -= pArr[j];
            }
        }
    }
}
int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n); getchar();
    int *pArr = (int *)malloc(n*sizeof(int));
    if (pArr == NULL) { puts("Fuck!!!"); exit(-1); }
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%d", pArr+i); getchar();
    }
    void (*sort)(int *, int) = _sort_asc;
    if (argc > 1) {
        if ( !strcmp("-d", argv[1]) ) {
            sort = _sort_des;
        }
        else { exit(-1); }
    }
    sort(pArr, n);
    for (i = 0; i < n; ++i) {
        printf("%8d", pArr[i]);
    }
    putchar('\n');
    for (i = 0; i < n; ++i) {
        free(pArr+i);
    }
    return 0;
}
