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

void unitTests(void) {
	// Check for memory leaks
	char * smallInput = "[[[]d][]]";
	printf("Input:\t%s\n", smallInput);
	size_t i = strlen(smallInput);
	Node * tree = parseTree(smallInput, 1, i-1);
	sortTree(tree);
	printf("Output:\t");
	printTree(tree);
	fellTree(tree);
	
}

int main(int argc, const char * argv[]) {
	
	char * input = parseInput();

	size_t i = 0;
	while (input[i] != '\0') { i++; }

	Node * tree = parseTree(input, 1, i-1);
	sortTree(tree);

	printTree(tree);

	fellTree(tree);

	free(input);
	input = NULL;

//	unitTests();
	
	return EXIT_SUCCESS;
}
