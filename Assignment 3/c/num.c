#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "num.h"

#define ERR_MEM_ALC	(1)
#define NUM_LENGTH	(INT_MAX)
#define ASCII_OFFST	(48)

// Note that since numGetDigit(n, digit) takes `digit` as an int, we know that
// there can never be more than INT_MAX digits
// We sacrifice storage efficiency for a constant size,
// Which makes implementing operations much much easier
struct num {
	int length;
	int digits[NUM_LENGTH];
};

struct num * numCreate(const char * s)
{
	struct num *n;
	
	n = malloc(sizeof(struct num) + NUM_LENGTH * sizeof(int));
	assert(n);

	// TOOD: Set all values to 0

	size_t length = strlen(s);

	for (size_t i = 0; i < length; i++) {
		n->digits[length - (i + 1)] = (s[i] - ASCII_OFFST);
	}

	n->length = length;

	return n;
}

void numDestroy(Num * n)
{
	free(n);
	n = NULL;
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
	int tmp = 0;
	size_t i = 0;
	int carry = 0;
	size_t max_length = 0;

	Num * sum = numCreate("");

	max_length = (x->length > y->length) ? x->length : y->length;

	while (i < max_length || carry) {
		tmp = numGetDigit(x, i) + numGetDigit(y, i) + carry;

		if (tmp > 10) {
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

// Num * numMultiply(const Num *x, const Num *y);

void numPrint(const Num * n, FILE * f)
{
	if (n->length == 0) {
		fprintf(f, "0");
	}
	else {
		for (size_t i = 0; i < (size_t)n->length; i++) {
			fprintf(f, "%d", numGetDigit(n, n->length - (i+1)));
		}
	}
}
