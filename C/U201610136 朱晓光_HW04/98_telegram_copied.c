#include<stdio.h>



#define change      c%2



void func(char c) {
    if (c>='A' && c<='Z')
    c = 'a' + c - 'A';
    else if (c>='a' && c<='z')
    c = 'A' + c - 'a';
    putchar(c);
}



void main(void) {

    char c;
    int i, k;


    scanf("%d\n", &k);



    for (i = 0; i < k; i++) {


        c = getchar();

        if (change == 0) {
            do {
                if(c!='\n')
                putchar(c);
                else {
                    putchar(c);
                    break;
                }
            } while ((c = getchar()) != EOF);
        }

        else if (change == 1) {
            do {
                if(c!='\n')
                func(c);
                else {
                    putchar(c);
                    break;
                }
            } while ((c = getchar()) != EOF);
        }

    }


}
