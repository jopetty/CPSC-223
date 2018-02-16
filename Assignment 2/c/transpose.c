/*
 *  File:		transpose.c
 *  Author:		Jackson Petty <jackson.petty@yale.edu>
 *  Date:		1 February 2018
 *
 *  Description:	This file contains all code for Assignment 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_ARG_NUM	(1) // Wrong number of arguments
#define ERR_MEM_ALC	(2) // Unable to allocate memory for buffer
#define ERR_NEG_VAL	(3) // n < 1

static inline int modulo(long long x, unsigned int y)
{
	/*
	 *  Function modulo(x, y) -> z
	 *  -----------------------------
	 *  @param: x (long long)
	 *  	x cannot always fit into an integer, so we
	 *  	must cast it up to a long long to prevent
	 *  	overflow
	 *  @param: y (unsigned int)
	 *  	y will always be able to fit into an
	 *  	integer. Since y <- n always, we can assume
	 *  	that it is unsigned.
	 *
	 *  @return: z (long long)
	 *  	z = x mod y
	 */

	return ((x % y) + y) % y;
}

int parse_input(unsigned int n, int a, int b)
{
	/*
	 *  Function parse_input(void) -> status_code
	 *  -----------------------------
	 *  @param: void
	 *  	No arguments should be passed
	 *
	 *  @return: status_code (int)
	 *  	Return error code if failed, or 
	 *  	zero if successful.
	 *
	 *  	0 => Success
	 *  	2 => ERR_MEM_ALC
	 */

	char* buffer = malloc(n * sizeof(int));

	if (!buffer) {
		fprintf(stderr, "Unable to allocate memory for %d items.\n", n);
		return ERR_MEM_ALC;
	}

	int c;
	size_t output;
	unsigned int count = 0;

	memset(buffer, '\0', n * sizeof(int));

	while ((c = getchar()) != EOF) {
		
		buffer[count++] = c;

		if (count == n) {
			for (size_t i = 0; i < count; i++) {
				output = modulo(((long long)a * i + b), n);
				putchar(buffer[output]);
				buffer[output] = '\0';
			}
			count = 0;
		}
	}

	if (count) { // length of stdin is not a multiple of n
		for (size_t i = 0; i < n; i++) {
			putchar(buffer[modulo(((long long)a * i + b), n)]);
		}
	}

	free(buffer);
	buffer = NULL;

	return 0;
}

int main(int argc, char** argv)
{
	unsigned int n;
	int a;
	int b;

	if (argc != 4) { 
		fprintf(stderr, "Usage: %s n a b\n", argv[0]);
		return ERR_ARG_NUM; 
	} else {
		if (atoi(argv[1]) < 1) { 
			fprintf(stderr, "n must be greater than or equal to 1.\n");
			return ERR_NEG_VAL; 
		} else { 
			n = atoi(argv[1]); 
		}
		a = atoi(argv[2]);
		b = atoi(argv[3]);
	
		return parse_input(n, a ,b);
	}
}
