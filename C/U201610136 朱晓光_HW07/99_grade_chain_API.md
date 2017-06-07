# 99_grade_chain.c API Reference


## Courses Code
不同课程对应不同的课程代号

Course      |   Code
------------|------------
English     |   0
Math        |   1
Pysics      |   2
C           |   3

```C
#define COURSE_CNT      4   // 课程总数
int getCourseCode(char const *name);
/* 把字符串形式的课程名转化为对应的课程代号 */
```

-------------------------------------

## Student Class
底层结构`Student` - 之后会被`Node`结构封装

### Data Structure
```C
typedef struct _Student {
    char    id[15];             // 学号
    int     name[20];           // 姓名
    float   grades[COURSE_CNT]; // 所有课程的成绩
    double  avg;                // 平均成绩
} Student;
```

### Functions
```C
Student * _initStudent(void);
/* 初始化Student方法 */

void _printStudent(Student stu);
/* 格式化输出学生信息（每门课程的成绩） */

void _printStudentStat(Student *stu);
/* 格式化输出学生统计信息（平均成绩） */

void _modifyStudent(Student *stu,
                    char const *course_name,
                    float new_score);
/* 修改学生成绩方法 */

double _compareStudent(Student A, Student B);
/* 比较学生平均成绩方法 */

void _freeStudent(Student *stu);
/* 释放学生数据所占内存空间的方法 */
```

-------------------------------------

## Node Class
封装`Student`后的结构

### Data Structure
```C
typedef struct _Node {
    Student         *data;  // 指向Student数据域
                            // 方便交换数据域操作，而且逻辑更为清晰
    struct _Node    *next;  // 指向下一个Node节点
} Node;
```

### Functions
```C
Node * initStudents(int cnt);
/* 封装_initStudent() */

void printStudents(Node *cur);
/* 封装_printStudent() - 给出头节点指针，直接打印出所有学生的信息 */

void printStudentsStat(Node *head);
/* 封装_printStudentStat() - 同上，打印出所有学生的统计信息 */

void printStudentsAvg(Node *head);
/* 打印出所有学生的平均成绩 */

Node * getNodeById(Node *head, char const *id);
/* 通过学生学号获取对应的Node节点的方法 */

void modifyChain(Node *head);
/* 封装_modifyStudent() */

double compareNode(Node A, Node B);
/* 封装_compareStudent()*/

void sortChainSwapData(Node *head, int cnt);
/* 交换数据域的排序方法 */

void sortChainChangeRoute(Node **headp);
/* 交换Node节点顺序的排序方法 */

void freeStudents(Node *cur);
/* 封装_freeStudent()
    给出头节点指针，释放Node数据域（ie Student所占内存空间）以及Node本身所占内存空间
*/
```
