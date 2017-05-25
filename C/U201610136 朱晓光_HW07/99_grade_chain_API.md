# 99_grade_chain.c

-------------------------------------

## API

### Courses

Course      |   Code
------------|------------
English     |   0
Math        |   1
Pysics      |   2
C           |   3

```C
#define COURSE_CNT      4
int getCourseCode(char const *name);
```
-------------------------------------

### Student Class

```C
typedef struct _Student {
    char    id[15];
    int     name[20];
    float   grades[COURSE_CNT];
    double  avg;
} Student;

Student * _initStudent(void);
void _printStudent(Student stu);
void _printStudentStat(Student *stu);
void _modifyStudent(Student *stu,
                    char const *course_name,
                    float new_score);
double _compareStudent(Student A, Student B);
void _freeStudent(Student *stu);
```
-------------------------------------

### Node Class
_wrapping the Student Class_

```C
typedef struct _Node {
    Student         *data;
    struct _Node    *next;
} Node;

Node * initStudents(int cnt);
void printStudents(Node *cur);
void printStudentsStat(Node *head);
void printStudentsAvg(Node *head);
Node * getNodeById(Node *head, char const *id);
void modifyChain(Node *head);
double compareNode(Node A, Node B);
void sortChainSwapData(Node *head, int cnt);
void sortChainChangeRoute(Node **headp);
void freeStudents(Node *cur);
```
