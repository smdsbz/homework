#include <stdio.h>
#include <stdlib.h>


#define isLeap(y)   ( ( (!((y)%4) && ((y)%100)) || !((y)%400) ) ? 1 : 0 )


typedef struct _date {
    int year;
    int month;
    int day;
} Date;



void initDate(Date *date) {
    scanf("%d %d %d",
          &date->year,
          &date->month,
          &date->day);
    return;
}



int countDays(Date date) {
    int sum = date.day;
    for (--date.month; date.month; --date.month) {
        switch (date.month) {
            case 12:    case 10:    case 8:
            case 7:     case 5:     case 3:
            case 1: { sum += 31; break; }
            case 11:    case 9:     case 6:
            case 4: { sum += 30; break; }
            case 2: {
                if (isLeap(date.year)) { sum += 29; }
                else { sum += 28; }
                break;
            }
            default: { puts("Fuck!!!"); exit(-1); }

        }
    }
    printf("%d\n", sum);
    return sum;
}



void main(void) {

    int n;
    scanf("%d", &n); getchar();

    Date date;

    for (; n; --n) {
        initDate(&date);
        countDays(date);
    }


    return;
}
