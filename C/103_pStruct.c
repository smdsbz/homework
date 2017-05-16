#include <stdio.h>


struct Student{int num;char name[19]; double score;};

/////////////////////////////////////////////////////////

void initStudent(struct Student *stu) {
    scanf("%d %s %lf",
          &stu->num,
          stu->name,
          &stu->score);
    return;
}


void printStudent(struct Student stu) {
    printf("%d\t%-20s%lf\n",
           stu.num,
           stu.name,
           stu.score);
    return;
}

/////////////////////////////////////////////////////////

void main(void) {

    struct Student s[3];

    int n, i;

    scanf("%d", &n); getchar();

    for (; n; --n) {

        // without p
        for (i = 0; i < 3; ++i) {
            initStudent(&s[i]);
        }
        for (i = 0; i < 3; ++i) {
            printStudent(s[i]);
        }
        struct Student  *p = &s[0];
        for (; (p-&s[0]) < 3; ++p) {
            printStudent(*p);
        }




    }


}
