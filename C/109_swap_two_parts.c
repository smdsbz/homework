#include <stdio.h>



int verifyInputNumber(int x, int *tgt) {
    if (x<=1000 && x>=-1000) {
        *tgt = x;
        return 1;
    }
    else {
        return 0;
    }
}




void printQuery(int *q, unsigned end) {
    unsigned i = 0;
    for (; i < end-1; ++i) {
        printf("%d ", q[i]);
    }
    printf("%d\n", q[i]);
}




void swapQuery(int *, unsigned, unsigned);
/*  :param int *:       array position
    :param unsigned:    k
    :param unsigned:    n
    :return void:
*/



void main(void) {

    unsigned n, k;
    int u[60] = {0};

    unsigned i;     // loop var
    int buf;

    while (
        scanf("%u %u", &n, &k) == 2 &&
        0 < k &&
        k < n &&
        n <= 60
    ) {

        getchar();

        // input numbers - if not validate --> exit programme
        for (i = 0; i < n; ++i) {
            scanf("%d", &buf);
            if (verifyInputNumber(buf, u+i)) {;}
            else { return; }
        }

        // printQuery(u, n);

        // swap
        swapQuery(u, k, n);

        printQuery(u, n);


    }

}




void swapQuery(int * u, unsigned k, unsigned n) {

    int tmp[n];
    unsigned i;

    // fill second part
    for (i = n-k; i < n; ++i) {
        tmp[i] = u[i+k-n];
    }
    // fill first part
    for (i = 0; i < n-k; ++i) {
        tmp[i] = u[i+k];
    }
    // cover original query
    for (i = 0; i < n; ++i) {
        u[i] = tmp[i];
    }

}
