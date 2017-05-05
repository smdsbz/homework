#include <stdio.h>


#define M   5       // course count (of each student)
#define N   5       // student count

//////////////////////////////////////

typedef struct {
    char            name[81];
    unsigned char   grade[M];   // this should be kept align with courses
    double          avg;
} Student;


typedef struct {
    char        name[81];
    double      avg;
} Course;


//////////////////////////////////////

Course  courses[M];
Student students[N];


//////////////////////////////////////

/* Student Operations */

/* 计算每个学生各门课程的平均成绩 */
double getAvgOfStudent(Student Sally) {
    unsigned i = 0;
    for (Sally.avg = 0.; i < M; ++i) {
        Sally.avg += Sally.grade[i];
    }

    Sally.avg /= M;

    printf("Average score of %s is %.2lf\n", Sally.name, Sally.avg);

    return Sally.avg;
}




/* Class Operations */

/* 计算全班每门课程的平均成绩 */
void getAvgOfClass(void) {

    unsigned each_course = 0, each_student = 0;

    for (; each_course < M; ++each_course) {

        courses[each_course].avg = 0.;

        for (each_student = 0; each_student < N; ++each_student) {
            courses[each_course].avg += students[each_student].grade[each_course];
        }   // student loop
        courses[each_course].avg /= M;

        printf("Average score of %s is %.2lf\n",
                courses[each_course].name,
                courses[each_course].avg);

    }       // course loop
}



/* 统计低于平均分的人数 */
void getStudentCountBelowAvg(void) {

    unsigned student_count = 0, each_student = 0, each_course = 0;

    for (; each_course < M; ++each_course, student_count = 0) {
        for (each_student = 0; each_student < N; ++each_student) {
            if (
                students[each_student].grade[each_course] < courses[each_course].avg
            ) { ++student_count; }
        }
        printf("Number of students lower than avg of %s is %u\n",
                courses[each_course].name, student_count);
    }       // course loop

}



/* 统计不及格人数 */
void getStudentCountFailed(void) {

    unsigned student_count = 0, each_student = 0, each_course = 0;

    for (; each_course < M; ++each_course, student_count = 0) {
        for (each_student = 0; each_student < N; ++each_student) {
            if (
                students[each_student].grade[each_course] < 60.0
            ) { ++student_count; }
        }
        printf("Number of students %s fail is %u\n",
                courses[each_course].name, student_count);
    }       // course loop

}



/* 统计dalao人数 */
void getStudentCountPerfect(void) {
    unsigned student_count = 0, each_student = 0, each_course = 0;

    for (; each_course < M; ++each_course, student_count = 0) {
        for (each_student = 0; each_student < N; ++each_student) {
            if (
                students[each_student].grade[each_course] >= 90.0
            ) { ++student_count; }
        }
        printf("Number of students %s perfect is %u\n",
                courses[each_course].name, student_count);
    }       // course loop

}



/////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {

    unsigned i, j;


    // input
    for (i = 0; i < M; ++i) {
        scanf("%s", courses[i].name);
    }


    for (i = 0; i < N; ++i) {

        scanf("%s", students[i].name);

        for (j = 0; j < M; ++j) {
            scanf("%hhu\n", &students[i].grade[j]);
        }
    }



    // output
    for (i = 0; i < N; ++i) {
        getAvgOfStudent(students[i]);
    }

    getAvgOfClass();

    getStudentCountBelowAvg();

    getStudentCountFailed();

    getStudentCountPerfect();



    return 0;
}
