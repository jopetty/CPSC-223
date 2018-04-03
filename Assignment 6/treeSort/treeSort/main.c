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

void tests() {
	char * rand100in = "[[[[[[[]]][][[][][[][]]]][[][]][[]][[[][][][]][[][]]][[[[[]][]][[[[][]][]]][][]][][[[][]]][]]][][[[[]][][]][]]][[][][[]]][[[[[[]][]][]][[]][[[]]][]][[[[]][]][[]][][[][[[]]]][]][[[][[[[]][][]][]][]]]]]";
	char * rand100out = "[[[[[[[[[][]][]]][[[]][]][][]][[[][]]][][]][[[[][]][][]][[[]]][]][[[][][][]][[][]]][[][]][[]]][[[[]][][]][]][]][[[[[[]]][]][[[]][]][[]][][]][[[[[]][]][]][[[]]][[]][]][[[[[[]][][]][]][][]]]][[[]][][]]]";
	
	size_t length = strlen(rand100in);
	Node * tree = parseTree(rand100in, 1, length - 1);
	sortTree(tree);
	printTree(tree);
	fellTree(tree);
	printf("\n#######################\n");
	Node * oTree = parseTree(rand100out, 1, length - 1);
	sortTree(oTree);
	printTree(oTree);
	fellTree(oTree);

	
}

int main(int argc, const char * argv[]) {
//	
//	tests();
	
	if (argc != 1) {
		fprintf(stderr, "Usage: %s", argv[0]);
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
