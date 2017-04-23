#include <stdio.h>
#include <string.h>



// parallel structure - imitating behaviours of dict in Python
char Student_name[100][21] = {'\0'};
unsigned char Student_grade[100] = {0};



void main(void) {

    unsigned N;
    scanf("%u", &N); getchar();

    unsigned idx, n;    // loop var
    char ctmp[21]; unsigned char uctmp;


    // get Student_name & Student_grade
    for (idx = 0; idx < N; ++idx) {
        // Thank God there's no spaces in names...
        scanf("%s %hhu", *(Student_name+idx), (Student_grade+idx));
        getchar();      // swallow '\n'
    }


    // sort
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



    // formatted output
    for (idx = 0; idx < N; ++idx) {
        printf("%-20s %hhu\n", Student_name[idx], Student_grade[idx]);
    }


    // Task 1 completed
    putchar('\n');



////////////////////////////////


    // search grade
    unsigned M;
    unsigned char search_cont[100] = {0};
    // regulation
    scanf("%u", &M); getchar();
    if (M > N) {
        puts("There isn't that much students here!");
        return;
    }


    // input search data
    for (idx = 0; idx < M; ++idx) {
        scanf("%hhu", (search_cont+idx));
        getchar();
    }


    // find and output
    for (n = 0; n < M; ++n) {

        for (
            idx = 0;
            idx<N || (puts("Not found!"), 0);   // utilizing the optimation alg.
            ++idx
        ) {
            if (Student_grade[idx] == search_cont[n]) {
                printf("%-20s %hhu\n", Student_name[idx], Student_grade[idx]);
                break;
            }
        }

    }   // end of search loop


    // 苟利国家生死以，岂因祸福避趋之！

    return;
}
