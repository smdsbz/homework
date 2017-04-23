#include <stdio.h>



#define ROW     3
#define COL     4




int matrix[ROW][COL] = {0};



void entrMatrix(int [ROW][COL]);


void reprOriginal(int [ROW][COL]);
void reprTransposed(int [ROW][COL]);



void main(void) {

    entrMatrix(matrix);

    reprOriginal(matrix);

    putchar('\n');

    reprTransposed(matrix);

    return;
}




void entrMatrix(int m[ROW][COL]) {

    int i, j;

    for (j = 0; j < ROW; ++j) {

        for (i = 0; i < COL; ++i) {

            scanf("%d", *(m + j*COL + i));
            // getchar();      // swallow ' ' or '\n'

        }   // end of ROW

    }   // end of all

    return;
}



void reprOriginal(int m[ROW][COL]) {

    int i, j;

    for (j = 0; j < ROW; ++j) {

        for (i = 0; i < COL; ++i) {

            printf("%5d", **(m + j*COL + i));

        }   // end of ROW

        putchar('\n');

    }   // end of all

    return;
}




void reprTransposed(int m[ROW][COL]) {

    int i, j;

    for (i = 0; i < COL; ++i) {

        for (j = 0; j < ROW; ++j) {

            printf("%5d", **(m + j*COL + i));

        }   // end of COL

        putchar('\n');

    }   // end of all

    return;
}
