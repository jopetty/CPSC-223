#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>

#include "num.h"

#define ERR_BAD_NUM (NULL)
#define ERR_MEM_ALC	(1)
#define NUM_MAX_LEN	(INT_MAX)
#define ASCII_OFFST	(48)

// Note that since numGetDigit(n, digit) takes `digit` as an int, we know that
// there can never be more than INT_MAX digits
// We sacrifice storage efficiency for a constant size,
// Which makes implementing operations much much easier
struct num {
	int length;
	int digits[NUM_MAX_LEN];
};

Num * numCreate(const char * s)
{
	// If we encountered a non-zero digit, we can start from that point
	// and disregard all the leading zeros. If not, we treat input as 
	// an empty string to get a Num of length 0
	int start_pos = -1;
	size_t length = strlen(s);

	for (size_t i = 0; i < length; i++) {
		if (!isdigit(s[i])) { return ERR_BAD_NUM; }
		if (s[i] != '0' && (start_pos < 0)) { start_pos = i; }
	}

	if (start_pos < 0) { start_pos = length; }

	Num * n = malloc(sizeof(*n));
	assert(n);

	for (size_t j = start_pos; j < length; j++) {
		n->digits[length - (j + 1)] = (s[j] - ASCII_OFFST);
	}

	n->length = length - start_pos;
	return n;
}

void numDestroy(Num * n)
{
	if (n) {
		free(n);
		n = NULL;
	}
}

int numGetDigit(const Num * n, int i)
{
	if (i < n->length && i >= 0) {
		return n->digits[i];
	} else {
		return 0;
	}
}

Num * numAdd(const Num * x, const Num * y)
{
	/*
	 *  Function numAdd(x, y) -> n
	 *  -----------------------------
	 *  @param: x (Num *)
	 *  	A Num
	 *  @param: y (Num *)
	 *  	A Num
	 *
	 *  @return: n (Num *)
	 *  	n = x + y
	 */

	int tmp = 0;
	size_t i = 0;
	int carry = 0;
	size_t max_length = 0;

	Num * sum = numCreate("");

	max_length = (x->length > y->length) ? x->length : y->length;

	while (i < max_length || carry) {
		tmp = numGetDigit(x, i) + numGetDigit(y, i) + carry;

		if (tmp >= 10) {
			carry = tmp / 10;
			tmp = tmp % 10;
		} else {
			carry = 0;
		}

		sum->digits[i++] = tmp;

		if (i == max_length && carry) {
			max_length++;
		}
	}

	sum->length = max_length;

	return sum;
}

static Num * scalarMultiply(const Num * x, int lambda, int shift)
{
	/*
	 *  Function scalarMultiply(x, lambda, shift) -> n
	 *  -----------------------------
	 *  @param: x (Num *)
	 *  	The Num * which is to be multiplied by an integer
	 * 		scalar lambda
	 *  @param: lambda (int)
	 *  	The scalar multiple coefficient
	 *  @param: shift
	 * 		The power of 10 associated with lambda
	 *
	 *  @return: n (Num *)
	 *  	n = lambda * 10^shift * x
	 */

	Num * sum = numCreate("");

	for (size_t i = 0; i < (size_t)lambda; i++) {
		Num * result = numAdd(sum, x);
		numDestroy(sum);
		sum = result;
	}

	for (size_t j = 0; j < (size_t)shift; j++) {
		for (size_t k = 0; k < (size_t)(sum->length); k++) {
			sum->digits[sum->length - k] = sum->digits[sum->length - k - 1];
		}
		sum->digits[0] = 0;
		sum->length++;
	}

	return sum;
}

Num * numMultiply(const Num *x, const Num *y) 
{
	Num * product = numCreate("");

	if (x->length == 0 || y->length == 0) {
		return product;
	}

	for (size_t i = 0; i < (size_t)(y->length); i++) {
		if (numGetDigit(y, i)) { // don't bother if y[i] is zero
			Num * s_mult = scalarMultiply(x, numGetDigit(y, i), i);
			Num * sum = numAdd(product, s_mult);
			numDestroy(product);
			product = sum;
			numDestroy(s_mult);
		}
	}

	return product;
}

void numPrint(const Num * n, FILE * f)
{
	if (n->length == 0) {
		fprintf(f, "0");
	} else {
		for (size_t i = 0; i < (size_t)n->length; i++) {
			fprintf(f, "%d", numGetDigit(n, n->length - (i+1)));
		}
	}
}

void showNumber(const Num * n) 
{
	printf("{ %d : ", n->length);
	numPrint(n, stdout);
	printf(" }\n");
}
