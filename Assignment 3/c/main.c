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

	printf("\n");

	// Checking if null Num is created correctly
	Num * blank_test = numCreate("");
	assert(numGetDigit(blank_test, 0) == 0);
	showNumber(blank_test);
	numDestroy(blank_test);

	// Leading Zeros
	Num * zero_test = numCreate("000123");
	showNumber(zero_test);
	numDestroy(zero_test);

	Num * bad_val = numCreate("tstes112321fdas");
	numDestroy(bad_val);

	// Checking if digits are stored correctly
	Num * digit_test = numCreate("12345");
	showNumber(digit_test);
	assert(numGetDigit(digit_test, 0) == 5);
	assert(numGetDigit(digit_test, 3) == 2);
	assert(numGetDigit(digit_test, 17) == 0);
	assert(numGetDigit(digit_test, -12) == 0);
	numDestroy(digit_test);

	// Addition
	Num * first_addened = numCreate("13");
	Num * second_addened = numCreate("8");
	Num * sum = numAdd(first_addened, second_addened);
	printf("8 + 13 = ");
	showNumber(sum);
	numDestroy(first_addened);
	numDestroy(second_addened);
	numDestroy(sum);

	first_addened = numCreate("99");
	second_addened = numCreate("13");
	sum = numAdd(first_addened, second_addened);
	printf("99 + 13 = ");
	showNumber(sum);
	numDestroy(first_addened);
	numDestroy(second_addened);
	numDestroy(sum);

	// BIG addition
	Num * big_num_one = numCreate("2570906032674836362493098841827039250513722520868666904498196035555315023364249");
	Num * big_num_two = numCreate("23501800604186922700076639428968353822086810802999803164890312934792162058881");
	sum = numAdd(big_num_one, big_num_two);
	showNumber(sum);

	numDestroy(big_num_one);
	numDestroy(big_num_two);

	// Multiplicaiton
	// for x, y in ((0, 123), (1,2), (29, 112), (37**50, 39**48)):
	Num * factor_a = numCreate("1");
	showNumber(factor_a);
	Num * factor_b = numCreate("2");
	Num * product = numMultiply(factor_a, factor_b);
	printf("1 * 2 = ");
	showNumber(product);
	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);

	factor_a = numCreate("0");
	factor_b = numCreate("123");
	product = numMultiply(factor_a, factor_b);
	printf("0 * 123 = ");
	showNumber(product);
	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);

	factor_a = numCreate("29");
	factor_b = numCreate("112");
	product = numMultiply(factor_a, factor_b);
	printf("29 * 112 = ");
	showNumber(product);
	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);

	factor_a = numCreate("2570906032674836362493098841827039250513722520868666904498196035555315023364249");
	factor_b = numCreate("23501800604186922700076639428968353822086810802999803164890312934792162058881");
	product = numMultiply(factor_a, factor_b);
	showNumber(product);
	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);
	return 0;
}
