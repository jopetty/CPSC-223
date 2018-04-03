//
//  main.c
//  treeSort
//
//  Created by Jackson Petty on 3/25/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_BAD_ARGS	(3) // Incorrect number of arguments

int main(int argc, const char * argv[]) {
	
	if (argc != 1) {
		fprintf(stderr, "Usage: %s", argv[0]);
		exit(ERR_BAD_ARGS);
	}

	char * input = parseInput();

	size_t i = strlen(input);

	Node * tree = parseTree(input, 1, i - 1);

	sortTree(tree);
	printTree(tree);
	fellTree(tree);

	free(input);
	input = NULL;

	return EXIT_SUCCESS;
}
