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
	numPrint(blank_test, stdout);
	numDestroy(blank_test);

	printf("\n");

	// Leading Zeros
	Num * zero_test = numCreate("000123");
	numPrint(zero_test, stdout);
	numDestroy(zero_test);

	printf("\n");

	Num * bad_val = numCreate("tstes112321fdas");
	numDestroy(bad_val);

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

	// BIG addition
	Num * big_num_one = numCreate("2570906032674836362493098841827039250513722520868666904498196035555315023364249");
	Num * big_num_two = numCreate("23501800604186922700076639428968353822086810802999803164890312934792162058881");

	numPrint(big_num_one, stdout);
	printf("\n");
	numPrint(big_num_two, stdout);
	printf("\n");
	sum = numAdd(big_num_one, big_num_two);
	numPrint(sum, stdout);

	numDestroy(big_num_one);
	numDestroy(big_num_two);

	printf("\n");

	// Multiplicaiton
	// for x, y in ((0, 123), (1,2), (29, 112), (37**50, 39**48)):
	Num * factor_a = numCreate("1");
	Num * factor_b = numCreate("2");

	Num * product = numMultiply(factor_a, factor_b);
	numPrint(product, stdout);
	printf("\n");

	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);

	factor_a = numCreate("0");
	factor_b = numCreate("123");

	product = numMultiply(factor_a, factor_b);
	numPrint(product, stdout);
	printf("\n");

	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);

	factor_a = numCreate("29");
	factor_b = numCreate("112");

	product = numMultiply(factor_a, factor_b);
	numPrint(product, stdout);
	printf("\n");

	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);

	factor_a = numCreate("2570906032674836362493098841827039250513722520868666904498196035555315023364249");
	factor_b = numCreate("23501800604186922700076639428968353822086810802999803164890312934792162058881");

	product = numMultiply(factor_a, factor_b);
	numPrint(product, stdout);
	printf("\n");

	numDestroy(factor_a);
	numDestroy(factor_b);
	numDestroy(product);
	return 0;
}
