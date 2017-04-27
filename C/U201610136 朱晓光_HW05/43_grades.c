#include <stdio.h>
#include <string.h>
unsigned char * divideSearch(unsigned char target, unsigned char *start, unsigned count);
char Student_name[100][21] = {'\0'};
unsigned char Student_grade[100] = {0};
void main(void) {
    unsigned N;
    scanf("%u", &N); getchar();
    unsigned idx, n;    // loop var
    char ctmp[21]; unsigned char uctmp;
    for (idx = 0; idx < N; ++idx) {
        scanf("%s %hhu", *(Student_name+idx), (Student_grade+idx));
        getchar();      // swallow '\n'
    }
    for (idx = 0; idx < N; ++idx) {
        for (n = 0; n < N-1-idx; ++n) {
            if (Student_grade[n] < Student_grade[n+1]) {
                uctmp = Student_grade[n+1];
                Student_grade[n+1] = Student_grade[n];
                Student_grade[n] = uctmp;
                strcpy(ctmp, *(Student_name+n+1));
                strcpy(*(Student_name+n+1), *(Student_name+n));
                strcpy(*(Student_name+n), ctmp);
            }
        }
    }
    for (idx = 0; idx < N; ++idx) {
        printf("%-20s %hhu\n", Student_name[idx], Student_grade[idx]);
    }
    putchar('\n');
////////////////////////////////
    unsigned M;
    unsigned char search_cont[100] = {0};
    scanf("%u", &M); getchar();
    if (M > N) {
        puts("There isn't that much students here!");
        return;
    }
    for (idx = 0; idx < M; ++idx) {
        scanf("%hhu", (search_cont+idx));
        getchar();
    }
    for (n = 0; n < M; ++n) {
        unsigned char * cur = divideSearch(search_cont[n], Student_grade, N);
        if (cur != NULL) {
            printf("%-20s %hhu\n", Student_name[cur-Student_grade], *cur);
        }
        else {
            puts("Not found!");
        }
    }   // end of search loop
    return;
}
unsigned char * divideSearch(unsigned char target, unsigned char *start, unsigned count) {
    unsigned char * pMiddle = start + (int)count/2;
    if (target == *pMiddle) { return pMiddle; }
    else if (count == 1) { return NULL; }
    else if (target > *pMiddle) { return divideSearch(target, start, count/2); }
    else if (target < *pMiddle) { return divideSearch(target, pMiddle, count - count/2); }
    else {
        puts("Unexpected operation!");
        return NULL;
    }
}
