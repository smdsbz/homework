#include <stdio.h>
#include <stdlib.h>




void printTrimedLine(char * cur) {

    // empty line
    if (*cur == '\n') {
        return;
    }

    // line not empty
    putchar(*cur);
    for (cur += 1; *cur && *cur!='\n'; ++cur) {
        if (*cur != ' ') {
            putchar(*cur);
        }
        else {
            if (*(cur-1) != ' ') {
                putchar(*cur);
            }
        }
    }
    putchar('\n');
    return;
}



void main(void) {


    unsigned num_of_lines = 0;
    // char input_string[81] = {0};
    char * lines[100];
    unsigned char i;

    while (
        scanf("%u", &num_of_lines),
        getchar(),
        num_of_lines
    ) {



        for (i = 0; i < num_of_lines; ++i) {
            lines[i] = (char *)malloc(81);
            fgets(lines[i], 80, stdin);         // capture '\n' as well!
        }

        for (i = 0; i < num_of_lines; ++i) {
            printTrimedLine(lines[i]);
        }

        putchar('\n');

        for (i = 0; i < num_of_lines; ++i) {
            free(lines[i]);
        }


    }

}
