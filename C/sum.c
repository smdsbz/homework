#include "stdio.h"

int main(void) {
	int S = 0;
	int i;
	for (i = 1; i < 101; i++) {
		S += i;
	}
	printf("%d\n", S);
	return 0;
}
