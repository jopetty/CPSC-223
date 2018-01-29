/*
 *  File:	encode.c
 *  Author:	Jackson Petty <jackson.petty@yale.edu>
 *  Date:	9 January 2018
 *
 *  Description:	This file implements all code required for Assignment 1 of CPSC 223b.
 */

#include <stdio.h>
#include <ctype.h>

#define SHORT_ENDING	("an")
#define LONG_ENDING	("o")

void parse_input(void)
{
	/*
	 *  Function parse_input()
	 *  ------------------------------------------
	 *  Prints out all non-letter characters as is,
	 *  and prints out processed versions of words.
	 *
	 *  Rules:
	 *   1. Move the first letter to the end.
	 *   2. Add "an" to ends of words of 3 letters
	 *      or less, or "o" to words of > 3 letters.
	 *   3. Make the resulting word match the case
	 *      of the initial word.
	 */	

	unsigned int count = 0;
	char first_char = 0;
	int c;

	while ((c = getchar()) != EOF) {

		if (isalpha(c)) {
			if (count == 1) {
				islower(first_char) ? putchar(tolower(c)) : putchar(toupper(c));
			} else {
				count ?	putchar(c) : (first_char = c);
			}
		} else {
			if (first_char) {
				(count == 1) ? putchar(first_char) 	 : putchar(tolower(first_char));
				(count > 3)  ? printf("%s", LONG_ENDING) : printf("%s", SHORT_ENDING);
				first_char = 0;
			}

			putchar(c);
		}

		if (first_char) {
			if (count < 4) { count++; } // In case count > MAX_INT
		} else {
			count = 0;
		}
	}

	if (count) { // If we never ecounter non-alphabetic characters, print out ending here
		(count == 1) ? putchar(first_char) 	 : putchar(tolower(first_char));
		(count > 3)  ? printf("%s", LONG_ENDING) : printf("%s", SHORT_ENDING);
	}
}

int main(int argc, char** argv)
{
	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return 1;
	}

	parse_input();

	return 0;
}

