#include <stdio.h>
//////////////////////////////////////////////////
/*****  Class Definition  *****/
/***    Class Members      ***/
typedef struct MyStruct {
    int     _some_number;
    void    (*f)(struct MyStruct *);
    struct MyStruct *   self;
} MyClass;
/***    Class Functions    ***/
MyClass __init_MyClass__(
    int a, void (*func)(MyClass *)
) {
    /*  Class Init Function
        Returns the desired class object
    */
    MyClass obj;
    obj._some_number = a;
    obj.f = func;
    return obj;
}
void func(MyClass *self) {
    /* Some Other Function */
    scanf("%d", &(self->_some_number));
    puts("Hello, World!");
    printf("self._some_number = %d\n", self->_some_number);
    return;
}
///////////////////////////////////////////////////
void main(void) {
    /* Instantiating Class Object */
    MyClass Object = __init_MyClass__(42, func);
    Object.self = &Object;
    // Instantiation Finished
    Object.f(&Object);
}
