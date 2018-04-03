//
//  tree.c
//  treeSort
//
//  Created by Jackson Petty on 3/25/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_BAD_NODE	(1)	// Node * is NULL
#define ERR_BAD_INPUT	(2) // Encountered an illegal character in input

#define BUFFER_SIZE	(512)	// Initial buffer size

// MARK: - Properties

struct node {
	size_t size;
	size_t height;
	Node * parent;
	Node * children[];
};

// MARK: - Static Functions

static Node * createNodeWithSize(size_t size) {
	
	Node * node = malloc(sizeof(*node) + size * sizeof(*node->children));
	if (NULL == node) {
		fprintf(stderr, "Fatal Error: Unable to create node.\n");
		exit(ERR_BAD_NODE);
	}
	
	node->height = 1;
	node->size = size;
	node->parent = NULL;
	for (size_t i = 0; i < size; i++) {
		node->children[i] = NULL;
	}
	
	return node;
}

/**
 Implements the selection sort algorithm.
 If time permits (it should), this should hopefully
 be replaced by a merge sort implementation.
*/

static int compareTrees(const void * treeA, const void * treeB) {
	const Node * const leftTree = *(Node **)treeA;
	const Node * const rightTree = *(Node **)treeB;
	
	return (int)(rightTree->height - leftTree->height);
}

// MARK: - Public Functions

/**
 Sorts a tree based on how many children each node has.
 Recursively calls itself on all non-trivial sub-trees.
 
 @param root	Pointer to the root node of a sub-tree.
*/
void sortTree(Node * root) {
	if (root->size > 1) {
		
		qsort(root->children, root->size, sizeof(Node *), compareTrees);
		
		for (size_t i = 0; i < root->size; i++) {
			sortTree(root->children[i]);
		}
	}
}

char * parseInput(void) {
	
	int c;
	size_t level = 0;
	size_t length = 0;
	size_t size = BUFFER_SIZE;

	char * buff = malloc(size * sizeof(char));
	
	while ((c = getchar()) != EOF) {
		
		if (c == '[') {
			level++;
		} else if (c == ']') {
			level--;
		} else {
			if (level == 0) {
				break;
			} else {
				free(buff);
				buff = NULL;
				exit(ERR_BAD_INPUT);
			}
		}
		
		if (length >= (size-1)) {
			size = ((length / BUFFER_SIZE) + 1) * BUFFER_SIZE;
			buff = realloc(buff, size);
		}
		
		buff[length++] = c;
	}
	
	buff[length] = '\0';
	
	if (length == 0) {
		free(buff);
		exit(EXIT_SUCCESS);
	}
	
	if (length % BUFFER_SIZE != 0) {
		buff = realloc(buff, size - (BUFFER_SIZE % length));
	}
	
	return buff;
}

Node * parseTree(const char * input, size_t start, size_t end) {
	
	char c;
	size_t size = 0;	// How many children does a node have
	size_t v_level = 0; // Vertical level of the tree
	
	for (size_t i = start ; i < end ; i++) {
		
		c = input[i];
		('[' == c) ? v_level++ : v_level--;
		if (v_level == 0) { size++; }
		
	}
	
	Node * root = createNodeWithSize(size);
	size_t locations[2];
	
	size = 0;
	for (size_t i = start ; i < end ; i++) {
		c = input[i];
		
		if ('[' == c) {
			if (v_level++ == 0) {
				locations[0] = i;
			}
		} else {
			if (--v_level == 0) {
				locations[1] = i;
				size++;
			}
		}
		
		if (v_level == 0) {
			root->children[size - 1] = parseTree(input, locations[0]+1, locations[1]);
			root->children[size - 1]->parent = root;
			root->height += root->children[size - 1]->height;
		}
		
	}
	
	return root;
}

void printTree(Node * tree) {
	
//	printf("\nNode has size of %d\n", tree->height);
	
	printf("[");
	
	for (size_t i = 0; i < tree->size; i++) {
		printTree(tree->children[i]);
	}
	
	printf("]");
}

void fellTree(Node * tree) {
	
	for (size_t i = 0; i < tree->size; i++) {
		fellTree(tree->children[i]);
	}

	free(tree);
	tree = NULL;
}
