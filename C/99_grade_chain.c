#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True    1

//////////////////////////////////

enum Courses {
    English = 0,
    Math,
    Physics,
    C
};

#define COURSE_CNT  4

//////////////////////////////////

/**** Student Class ****/

typedef struct _Student {
    char    id[15];
    int     name[20];
    float   grades[COURSE_CNT];
} Student;



Student * _initStudent(void) {
    /*  create a Student record
        RETURN the pointer of the record
    */
    Student *stu = (Student *)malloc(sizeof(Student));
    scanf("%s", stu->id); getchar();
    scanf("%s", stu->name); getchar();
    for (int i = 0; i < COURSE_CNT; ++i) {
        scanf("%f", &(stu->grades[i])); getchar();
    }
    return stu;
}


void _printStudent(Student stu) {
    /*  print out a formated Student record
        NO RETURN
    */
    printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",
           stu.id, stu.name,
           stu.grades[English],
           stu.grades[Math],
           stu.grades[Pysics],
           stu.grades[C]);
    return;
}


// TODO: getStudentById(...) needed
// void modifyStudent(void) {
//
// }




void _freeStudent(Student *stu) {
    free(stu);
}

//////////////////////////////////////////////////

/**** Node Class ****/
// index of Student records

typedef struct _Node {
    Student         *data;
    struct _Node    *next;
} Node;


Node * initStudents(int cnt) {
    /*  create $cnt Student records wrapped by Node
        RETURN pointer of the chain's head
    */
    Node *head = (Node *)malloc(sizeof(Node));
    // init first Student
    head->data = _initStudent();
    head->next = NULL;
    --cnt;
    // init following Students
    for (Node *subs = head; cnt; --cnt) {
        subs->next = (Node *)malloc(sizeof(Node));  // create next Node
        subs = subs->next;      // move to next Node
        subs->next = NULL;
        subs->data = _initStudent();    // toggle data input
    }
}



void printStudents(Node *cur) {
    /*  print out all Student records
    */
    printf("%-15s%-20s%-10s%-10s%-10s%-10s\n",
           "ID", "Name", "English", "Math", "Physics", "C");
    for (; True; cur = cur->next) {
        _printStudent(*(cur->data));
        if (cur->next == NULL) { break; }
    }
    putchar('\n');
}



Student * getStudentById(char const *id) {

}




void freeStudents(Node *cur) {
    while (True) {
        _freeStudent(cur->data);    // free data storage
        free(cur);                  // free Node
        if (cur->next != NULL) { cur = cur->next; }
        else { break; }
    }
    return;
}
