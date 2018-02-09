#include <stdio.h>
#include <limits.h>

#include "num.h"

int main(int argc, char** argv)
{
	if (argc != 1) {
		fprintf(stderr, "Usage: %s", argv[0]);
		return 1;
	}

	Num* test = numCreate("123413241412");
	numPrint(test, stdout);

	printf("\n\n%d\n", numGetDigit(test, 3));
	printf("\n\n%d\n", numGetDigit(test, (long long)INT_MAX + 3));

	numDestroy(test);

	return 0;
}
