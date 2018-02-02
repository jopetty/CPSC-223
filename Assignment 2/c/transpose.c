/*
 * File:	transpose.c
 * Author:	Jackson Petty <jackson.petty@yale.edu>
 * Date:	1 February 2018
 *
 * Description:	This file contains all code for Assignment 2
 */

#include <stdio.h>
#include <stdlib.h>

static unsigned int n;
static int a;
static int b;

void parse_input()
{
	unsigned int count = 0;
	int c = 0;

	while ((c = getchar()) != EOF && count++ < n) {
		putchar(c);
	}
}

int main(int argc, char** argv)
{

	if (argc != 4) { 
		fprintf(stderr, "Wrong number of arguments supplied.\n");
		return 1; 
	} else {
		n = atoi(argv[1]);
		a = atoi(argv[2]);
		b = atoi(argv[3]);

		parse_input();
	}

	return 0;
}
