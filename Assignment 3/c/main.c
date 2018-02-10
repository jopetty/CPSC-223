#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "num.h"

int main(int argc, char ** argv)
{
	if (argc != 1) {
		fprintf(stderr, "Usage: %s", argv[0]);
		return 1;
	}

	Num * test = numCreate("123413241412");
	numPrint(test, stdout);
	numDestroy(test);

	Num * blank_test = numCreate("");
	numPrint(blank_test, stdout);
	numDestroy(blank_test);

	Num * digit_test = numCreate("12345");
    assert(numGetDigit(digit_test, 0) == 5);
    assert(numGetDigit(digit_test, 3) == 2);
    assert(numGetDigit(digit_test, 17) == 0);
    assert(numGetDigit(digit_test, -12) == 0);
	numDestroy(digit_test);

	return 0;
}
