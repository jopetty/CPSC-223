/*
 *  File:		num.c
 *  Author:		Jackson Petty <jackson.petty@yale.edu>
 *  Date:		1 February 2018
 *
 *  Description:	This file contains the implementation for num.h
 */

#include "num.h"

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAX_LEN	(UINT_MAX)	// Maximum number of digits
#define ASCII_OFFST	('0')		// Conversion from 'digit' to digit

struct num {
	/*
	 *  Struct num { length, digits }
	 *  -----------------------------
	 *  @member: length (size_t)
	 *  	Number of digits stored in the num.
	 *
	 *  @member: digits (uint8_t[NUM_MAX_LEN])
	 *  	Array of uint8_t, each storing a value in the range [0,9]. Digits 
	 * 	are stored in a little endian format, where digit[0] is the least 
	 * 	significant digit and digit[length - 1] is the most significant.
	 */

	size_t length;
	uint8_t digits[];
};

static Num * _numCreateWithLength(const size_t length)
{
	/*
	 *  Function _numCreateWithLength(l) -> n
	 *  -----------------------------
	 *  @param: l (const size_t)
	 *  	Number of digits in Num
	 *
	 *  @return: n (Num *)
	 *  	n is a Num with all 0s of length l
	 */

	Num *n = malloc(sizeof(*n) + length);

	if (!n) {
		fprintf(stderr, "Unable to allocate %zu bytes of memory.\n", length);
		return NULL;
	}

	memset(n->digits, 0, length);

	n->length = length;
	return n;
}

Num * numCreate(const char *s)
{
	/*
	 *  Function numCreate(s) -> n
	 *  -----------------------------
	 *  @param: s (const char *)
	 *  	The string of digits
	 *
	 *  @return: n (Num *)
	 *  	n is the result of parsing the string into digits; 
	 * 	eg, "1234" -> (4, 1234)
	 * 
	 *  Procedure:
	 * 	1. Leading zeros should not be counted
	 * 	2. If s contains non-digit characters, return a NULL pointer
	 * 	3. Result must be positive
	 * 	4. Empty string "" becomes (0, 0)
	 */

	size_t length = strlen(s);
	size_t start_position = length; // First non-zero digit in string

	for (size_t i = 0; i < length; i++) {
		if (!isdigit(s[i])) { return NULL; }
		if (s[i] != '0' && (start_position == length)) { start_position = i; }
	}

	Num *n = _numCreateWithLength(length - start_position);

	if (!n) {
		fprintf(stderr, "Unable to allocate memory for Num('%s').\n", s);
		return NULL;
	}

	for (size_t j = start_position; j < length; j++) {
		n->digits[length - (j + 1)] = (s[j] - ASCII_OFFST); // '1' -> 1, etc
	}

	return n;
}

void numDestroy(Num *n)
{
	/*
	 *  Function numDestroy(n)
	 *  -----------------------------
	 *  @param: n (Num *)
	 *  	A Num
	 * 
	 *  Checks to make sure n is not NULL, free()'s n and sets it to a NULL 
	 *  pointer to ensure attempts to use it afterwards cause a crash.
	 * 
	 *  Performance is O(1)
	 */

	if (n) {
		free(n);
		n = NULL;
	}
}

static inline uint8_t _numGetDigit(const Num *n, size_t i) 
{
	/*
	 *  Function _numGetDigit(n, i) -> d
	 *  -----------------------------
	 *  @param: n (Num *)
	 *  	A Num
	 *  @param: i (size_t)
	 *  	The digit number, in range [0, n->length - 1]
	 *
	 *  @return: d (uint8_t)
	 *  	ith most significant digit of x. If i is not in 
	 * 	range [0, n->length - 1], d = 0.
	 * 
	 *  Performance is O(1)
	 */

	if (i < n->length) {
		return n->digits[i];
	} else {
		return 0;
	}
}

int numGetDigit(const Num *n, int i)
{
	/*
	 *  Function numGetDigit(n, i) -> d
	 *  -----------------------------
	 *  @param: n (Num *)
	 *  	A Num
	 *  @param: i (int)
	 *  	The digit number, in range [0, n->length - 1]
	 *
	 *  @return: d (int)
	 *  	ith most significant digit of x. If i is not in 
	 * 	range [0, n->length - 1], d = 0.
	 * 
	 *  This is a wrapper for _numGetDigit, which permits indexing to a value
	 *  much higher that INT_MAX, and returns a uint8_t, since that is how the 
	 *  digits are stored internally. Since num.h specifies a specific prototype
	 *  for numGetDigit, we validate the arguments and pass to _numGetDigit().
	 */

	if (i >= 0) {
		return (int)_numGetDigit(n, (size_t)i);
	} else {
		return 0;
	}
}

Num * numAdd(const Num *x, const Num *y)
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

	size_t i = 0;
	uint_fast8_t tmp = 0;
	size_t max_length = 0;
	uint_fast8_t carry = 0;

	max_length = (x->length > y->length) ? x->length : y->length;

	Num *sum;
	if (max_length == NUM_MAX_LEN) {
		sum = _numCreateWithLength(max_length);
	} else {
		sum = _numCreateWithLength(max_length + 1);
	}

	while (i < max_length || carry) {
		tmp = numGetDigit(x, i) + numGetDigit(y, i) + carry;

		if (tmp >= 10) {
			carry = tmp / 10;
			tmp = tmp % 10;
		} else {
			carry = 0;
		}

		sum->digits[i++] = tmp;

		if (i == max_length && carry) { max_length++; }
	}

	// We've aleady incremented max_length if there was a carry
	sum->length = max_length;

	return sum;
}

static Num * _scalarMultiply(const Num *x, int lambda, int shift)
{
	/*
	 *  Function scalarMultiply(x, lambda, shift) -> n
	 *  -----------------------------
	 *  @param: x (Num *)
	 *  	The Num * which is to be multiplied by an integer scalar lambda.
	 *  @param: lambda (int)
	 *  	The scalar multiple coefficient
	 *  @param: shift
	 * 	The power of 10 associated with lambda
	 *
	 *  @return: n (Num *)
	 *  	n = lambda * 10^shift * x
	 */

	Num *sum = _numCreateWithLength(0);

	for (size_t i = 0; i < (size_t)lambda; i++) {
		Num *result = numAdd(sum, x);
		numDestroy(sum);
		sum = result;
	}

	Num *shifted_sum = _numCreateWithLength(sum->length + shift);

	for (size_t j = 0; j < sum->length; j++) {
		shifted_sum->digits[j + shift] = sum->digits[j];
	}

	numDestroy(sum);
	return shifted_sum;
}

Num * numMultiply(const Num *x, const Num *y) 
{
	/*
	 *  Function numMultiply(x, y) -> n
	 *  -----------------------------
	 *  @param: x (Num *)
	 *  	A Num * factor
	 *  @param: y (Num *)
	 *  	A Num * factor
	 *
	 *  @return: n (Num *)
	 *  	n = x * y
	 * 
	 *  This implements a naïve multiplication algortithm, iterating through 
	 * 	each digit of y, adding x together that many times, and then shifting 
	 * 	the sum by the place value of that digit (essentially, the grade-school
	 *	way to multiply numbers).
	 */

	if (!(x->length && y->length)) { return _numCreateWithLength(0); }

	size_t length = floorl(log10l(x->length) + log10l(y->length)) + 1;
	length = (length > NUM_MAX_LEN) ? NUM_MAX_LEN : length;

	Num *product = _numCreateWithLength(length);

	for (size_t i = 0; i < (size_t)(y->length); i++) {
		if (numGetDigit(y, i)) {
			// Explicitly create & destory stucts to prevent memory leaks
			Num *s_mult = _scalarMultiply(x, numGetDigit(y, i), i);
			Num *sum = numAdd(product, s_mult);
			numDestroy(product);
			numDestroy(s_mult);
			product = sum;
		}
	}

	return product;
}

void numPrint(const Num *n, FILE *f)
{
	/*
	 *  Function numPrint(n, f)
	 *  -----------------------------
	 *  @param: n (const Num *)
	 *  	A Num *
	 *  @param: f (FILE *)
	 *  	File to which number is written
	 */

	if (n->length) {
		for (size_t i = 0; i < (size_t)n->length; i++) {
			fprintf(f, "%d", _numGetDigit(n, n->length - (i + 1)));
		}

	} else {
		fprintf(f, "0");
	}
}
