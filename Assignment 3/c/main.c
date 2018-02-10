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

	// Checking if printNum works
	Num * test = numCreate("123413241412");
	numPrint(test, stdout);
	numDestroy(test);

	// Checking if null Num is created correctly
	Num * blank_test = numCreate("");
	assert(numGetDigit(blank_test, 0) == 0);
	numDestroy(blank_test);

	printf("\n");

	// Checking if digits are stored correctly
	Num * digit_test = numCreate("12345");
	numPrint(digit_test, stdout);
	assert(numGetDigit(digit_test, 0) == 5);
	assert(numGetDigit(digit_test, 3) == 2);
	assert(numGetDigit(digit_test, 17) == 0);
	assert(numGetDigit(digit_test, -12) == 0);
	numDestroy(digit_test);

	printf("\n");

	// Addition
	Num * first_addened = numCreate("13");
	Num * second_addened = numCreate("8");
	Num * sum = numAdd(first_addened, second_addened);
	numPrint(sum, stdout);
	numDestroy(first_addened);
	numDestroy(second_addened);
	numDestroy(sum);

	printf("\n");

	first_addened = numCreate("99");
	second_addened = numCreate("13");
	sum = numAdd(first_addened, second_addened);
	numPrint(sum, stdout);
	numDestroy(first_addened);
	numDestroy(second_addened);
	numDestroy(sum);

	printf("\n");

	return 0;
}
