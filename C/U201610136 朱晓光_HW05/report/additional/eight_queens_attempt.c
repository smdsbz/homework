#include <stdio.h>


char chess_board[8][8] = {'\0'};


void showChessBoard(void) {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            putchar(
                chess_board[i][j] ? 'i' : '_'
            );
            putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}



int judge() {
    int i, j, flag = 0;
    // row
    for (i = 0; i < 8; flag = 0, ++i) {
        for (j = 0; j < 8; ++j) {
            flag += chess_board[i][j] ? 1 : 0;
            if (flag > 1) { return 0; }
        }
    }
    // column
    for (j = 0; j < 8; flag = 0, ++j) {
        for (i = 0; i < 8; ++i) {
            flag += chess_board[i][j] ? 1 : 0;
            if (flag > 1) { return 0; }
        }
    }
    // pos_diagonal
    for (i = 0; i < 8; flag = 0, ++i) {
        for (j = 0; j < 8; ++j) {
            flag += chess_board[j][(j+i)%8] ? 1 : 0;
            if (flag > 1) { return 0; }
        }
    }
    // neg_diagonal
    for (i = 7; i >= 0; flag = 0, --i) {
        for (j = 0; j < 8; ++j) {
            flag += chess_board[7-j][(j+i)%8] ? 1 : 0;
            if (flag > 1) { return 0; }
        }
    }
    // else
    return 1;
}


void move(int i, int j) {

}


void solution(void) {
    int i, j;

}


void main(void) {
    showChessBoard();
}
