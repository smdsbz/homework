#include "stdio.h"
// #include "stdlib.h"
// #include "time.h"


#define DICE_MAX    6




//////////////////////////////////////////////////////////////

/* Generate random number using the seed given */
unsigned char _throw(unsigned short);

/* Get score */
unsigned char getScore(unsigned short a, unsigned short b, unsigned long n) {
    return _throw(a+n-1) + _throw(b+n-1);
}

/* Judge whether lost the first round - if lose, return True */
unsigned char lose_on_first(unsigned char score) {
    if (score==2 || score==3 || score==12) { return 1; }
    else { return 0; }
}


//////////////////////////////////////////////////////////////

void main(void) {

    unsigned short N;   // total
    scanf("%hu", &N); getchar();



    unsigned short a, b;    // two seeds



    unsigned long i = 1;   // loop var
    unsigned char score;    // judging number


    for (; N; --N) {

        scanf("%hu %hu", &a, &b); getchar();
        // input regulation
        if (a>10000 || b>10000) { puts("Invalid Input!"); break; }



        // first throw
        score = getScore(a, b, 1);

        // win on first
        if (score == 7 || score == 11) { puts("success!"); continue; }
        // fail on first
        else if (lose_on_first(score)) { puts("fail!"); continue; }

        else {
            unsigned short latter_score;
            for (i=2; ; ++i) {
                latter_score = getScore(a, b, i);
                // fail latter
                if (latter_score == 7) { puts("fail!"); break; }
                // success latter
                else if (latter_score == score) { puts("success!"); break; }
            }
        }


    }   // end of main loop


}




//////////////////////////////////////////////////////////////

unsigned char _throw(unsigned short seed) {

    unsigned char sum = 0;

    for (; seed; seed /= 10) {
        sum += seed % 10;
    }

    sum = sum % DICE_MAX + 1;

    return sum;

}
