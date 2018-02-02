/*
 * File:	transpose.c
 * Author:	Jackson Petty <jackson.petty@yale.edu>
 * Date:	1 February 2018
 *
 * Description:	This file contains all code for Assignment 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ERR_ARG_NUM	1
#define ERR_MEM_ALC	2
#define ERR_NEG_VAL	3

static unsigned int n;
static int a;
static int b;

extern inline int modulo(int x, int y)
{
	return ((x % y) + y) % y;
}

int parse_input()
{
	unsigned int count = 0;
	int c;
	char* buffer = malloc(n * sizeof(int));

	if (buffer ==  NULL) {
		fprintf(stderr, "Unable to allocate memory for %d items.\n", n);
		return ERR_MEM_ALC;
	}

	memset(buffer, '\0', n*sizeof(int));

	while ((c = getchar()) != EOF) {
		
		buffer[count++] = c;

		if (count == n) {
			for (size_t i = 0; i < count; i++) {
				putchar(buffer[modulo((a*i+b),n)]);
				buffer[modulo((a*i+b),n)] = '\0';
			}
			count = 0;
		}
	}

	if (count) {
		for (size_t i = 0; i < n; i++) {
			putchar(buffer[modulo((a*i+b),n)]);
		}
	}

	free(buffer);
	buffer = NULL;

	return 0;
}

int main(int argc, char** argv)
{

	if (argc != 4) { 
		fprintf(stderr, "Wrong number of arguments supplied.\n");
		return ERR_ARG_NUM; 
	} else {
		if (atoi(argv[1]) < 1) { return ERR_NEG_VAL; } else { n = atoi(argv[1]); }
		a = atoi(argv[2]);
		b = atoi(argv[3]);
	
		return parse_input();
	}

	return 0;
}
