#ifndef MACROS_H_
#define MACROS_H_

/*
 *  全局宏定义以及数据元素类型定义
 *    ---- by U201610136 朱晓光 校际交流1601班
 */


#ifndef STATUS_VALUES
#define STATUS_VALUES
/* Page 10 */
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       -3  // 与其他有意义值错开，如 ListLength() 为
                        // 空表时的返回值
#define INFEASABLE  -1
#define OVERFLOW    -2
#endif

#ifndef ELEMTYPE
#define ELEMTYPE
/* 数据元素类型定义 */
typedef int status;
typedef struct _ElemType {
    size_t  id;
    char    data;
} ElemType;
#endif

#endif
