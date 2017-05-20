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

int getCourseCode(char const *name) {
    if (!strcmp(name, "English")) { return 0; }
    else if (!strcmp(name, "Math")) { return 1; }
    else if (!strcmp(name, "Physics")) { return 2; }
    else if (!strcmp(name, "C")) { return 3; }
    else { return -1; }
}

#define COURSE_CNT  4

//////////////////////////////////

/**** Student Class ****/

typedef struct _Student {
    char    id[15];
    char     name[20];
    float   grades[COURSE_CNT];
    double  avg;
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
           stu.grades[Physics],
           stu.grades[C]);
    return;
}


void _printStudentStat(Student *stu) {
    /*  ID NAME SUM AVG
    */
    double sum = 0;
    for (int i = 0; i < COURSE_CNT; ++i) {
        sum += stu->grades[i];
    }
    stu->avg = sum / COURSE_CNT;
    printf("%-15s%-20s%-10.2f%-10.2f\n",
           stu->id, stu->name,
           sum, (sum / COURSE_CNT));
    return;
}


double _compareStudent(Student Alice, Student Bob) {
    return (Alice.avg - Bob.avg);
}


void _modifyStudent(Student *stu,
                    char const *course_name,
                    float new_score) {
    stu->grades[getCourseCode(course_name)] = new_score;
    return;
}




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
    return head;
}


void printStudents(Node *cur) {
    /*  print out all Student records
    */
    printf("%-15s%-20s%-10s%-10s%-10s%-10s\n",
           "ID", "Name", "English", "Math", "Physics", "C");
    for (; cur; cur = cur->next) {
        _printStudent(*(cur->data));
        // if (cur->next == NULL) { break; }
    }
    putchar('\n');
}


void printStudentsStat(Node *head) {
    printf("%-15s%-20s%-10s%-10s\n",
           "ID", "Name", "SUM", "AVG");
    for (; head; head = head->next) {
        _printStudentStat(head->data);
    }
    putchar('\n');
    return;
}


void printStudentsAvg(Node *head) {
    printf("%-15s%-20s%-10s\n",
           "ID", "Name", "AVG");
    for (; head; head = head->next) {
        printf("%-15s%-20s%-10.2f\n",
               head->data->id,
               head->data->name,
               head->data->avg);
        // pass
    }
    putchar('\n');
    return;
}


Node * getNodeById(Node *head, char const *id) {
    Node *n = head;
    for (; n; n = n->next) {
        if (!strcmp(id, n->data->id)) { break; }    // node found
        if (n->next == NULL) { n = NULL; break; }   // end of chain
    }
    return n;
}


void modifyChain(Node *head) {
    /*  given the head of the chain
        will toggle input action
    */
    char id[15]; char course_name[20]; float new_score;
    scanf("%s %s %f", id, course_name, &new_score); getchar();
    _modifyStudent(getNodeById(head, id)->data,
                   course_name,
                   new_score);
    return;
}


double compareNode(Node A, Node B) {
    return _compareStudent(*(A.data), *(B.data));
}


void sortChainSwapData(Node *prev, int len) {
    int i, j;
    Node *head = prev;
    Node *subs;
    for (i = 0; i < len-1; ++i, prev = prev->next) {
        for (j = 0, subs = head; j < len-i-1; ++j, subs = subs->next) {
            if (compareNode(*subs, *(subs->next)) > 0) {
                Student *tmp = subs->data;   // ye only have to swap the data pointer
                subs->data = subs->next->data;
                subs->next->data = tmp;
                // puts("===================");
                // printStudentsAvg(head);
                // puts("===================");
            }
        }
    }
    return;
}


// void sortChainChangeRoute(...);


void freeStudents(Node *cur) {
    Node *pnode;
    while (cur) {
        pnode = cur;
        cur = cur->next;
        _freeStudent(pnode->data);    // free data storage
        free(pnode);                  // free Node
    }
    return;
}



///////////////////////////////////////////////////////////////////////


void main(void) {

    int cnt;
    scanf("%d", &cnt); getchar();


    Node *chain = initStudents(cnt);

    printStudents(chain);

    int change_cnt;
    scanf("%d", &change_cnt); getchar();

    for (; change_cnt; --change_cnt) {
        modifyChain(chain);
    }

    puts("Alter:");
    printStudents(chain);

    puts("SumAndAvg:");
    printStudentsStat(chain);

    puts("Sort:");
    sortChainSwapData(chain, cnt);
    printStudentsAvg(chain);


    freeStudents(chain);

    return;
}
