#include <stdio.h>



// int _isOther(char);
// int _isNumeric(char);
// int _isAlpha(char);

/* other    -->     'o'
 * number   -->     'n'
 * alpha    -->     'a'
 */
char charType(char);



unsigned other_count, number_count[10], alpha_count;


void main(void) {

    char cur;


    while (
        cur = getchar(),
        cur != '#'
    ) {

        switch (charType(cur)) {
            case 'o': {
                ++other_count;
                break;
            }
            case 'n': {
                ++number_count[cur-'0'];
                break;
            }
            case 'a': {
                ++alpha_count;
                break;
            }
        }

    }


    // result - number
    for (cur = 0; cur < 10; ++cur) {    // reusing cur
        printf("Number %hhd: %u\n", cur, number_count[cur]);
    }
    // result - alpha
    printf("characters: %u\n", alpha_count);
    // result - other
    printf("other: %u\n", other_count);

}


char charType(char c) {

    if (c<='z' && c>='A') {
        return 'a';
    }
    else if (c<='9' && c>='0') {
        return 'n';
    }
    else {
        return 'o';
    }

}
