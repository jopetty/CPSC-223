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
	int a[NUM_LENGTH];
};

struct num * numCreate(const char *s)
{
	struct num *n;
	
	n = malloc(sizeof(struct num) + NUM_LENGTH * sizeof(int));
	assert(n);

	// memset(n->a, 0, NUM_LENGTH * sizeof(int));
	size_t length = strlen(s);

	for (size_t i = 0; i < length; i++) {
		n->a[NUM_LENGTH - i] = (s[i] - ASCII_OFFST);
	}

	n->length = length;

	return n;
}

void numDestroy(struct num *n) {
	free(n);
}

int numGetDigit(const Num *n, int i) {
	assert(i >= 0);

	return n->a[NUM_LENGTH - i];
}

// Num * numAdd(const Num *x, const Num *y);

// Num * numMultiply(const Num *x, const Num *y);

void numPrint(const Num *n, FILE *f) {
	for (size_t i = 0; i < (size_t)n->length; i++) {
		fprintf(f, "%d", n->a[NUM_LENGTH - i]);
	}
}
