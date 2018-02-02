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

static unsigned int n;
static int a;
static int b;

void parse_input()
{
	unsigned int count = 0;
	int c;
	char buffer[n];

	while ((c = getchar()) != EOF) {
		
		buffer[count++] = c;
		// printf("Putting '%c' at position %u\n", c, count-1);

		if (count == n || c == EOF) {
			for (size_t i = 0; i < count; i++) {
				putchar(buffer[(a*i + b) %n]);
				buffer[(a*i + b) % n] = '\0';
			}
			count = 0;
		}
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
