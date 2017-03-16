#include "stdio.h"

int main(void) {

	enum month {
		January = 31, February = 28, March = 31,
		April = 30, May, June = 30, July,
		August = 31, September = 30, October,
		November = 30, December
	};

	int year;
	scanf("%d", &year);


	printf("January,%d\n", January);
	if ((!(year%4) && (year%100)) || !(year%400))	printf("February,%d\n", February+1);
	else	printf("February,%d\n", February);
	printf("March,%d\n", March);
	printf("April,%d\n", April);
	printf("May,%d\n", May);
	printf("June,%d\n", June);
	printf("July,%d\n", July);
	printf("August,%d\n", August);
	printf("September,%d\n", September);
	printf("October,%d\n", October);
	printf("November,%d\n", November);
	printf("December,%d\n", December);

	return 0;
}
