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
	Node * parent;
	Node * children[];
};

// MARK: - Static Functions

static void swap(Node * array[], size_t i, size_t j) {
	Node * tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

static Node * createNodeWithSize(size_t size) {
	
	Node * node = malloc(sizeof(*node) + size * sizeof(*node->children));
	if (NULL == node) {
		fprintf(stderr, "Fatal Error: Unable to create node.\n");
		exit(ERR_BAD_NODE);
	}
	
//	fprintf(stderr, "Creating node with %zu children.\n", size);
	
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
static void sortChildren(Node * root) {
	
	size_t max;
	for (size_t i = 0; i < root->size - 1; i++) {
		
		max = i;
		for (size_t j = i+1; j < root->size; j++) {
			if (root->children[j]->size > root->children[max]->size) {
				max = j;
			}
		}
		
		if (max != i) { swap(root->children, i, max); }
	}
}

// MARK: - Public Functions

/**
 Sorts a tree based on how many children each node has.
 Recursively calls itself on all non-trivial sub-trees.
 
 @param root	Pointer to the root node of a sub-tree.
*/
void sortTree(Node * root) {
	if (root->size > 1) {
		sortChildren(root);
		
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
	
	char * newBuffer;
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
				fprintf(stderr, "Fatal Error: Illegal input stream.\n");
				exit(ERR_BAD_INPUT);
			}
		}
		
		// TODO: Fix buffer reallocation
		
//		if (++length >= (size - 1)) {
//			size =((length / BUFFER_SIZE) + 1) * BUFFER_SIZE;
//			newBuffer = malloc(size * sizeof(*newBuffer));
//			memcpy(newBuffer, buff, length);
//			buff = newBuffer;
//			free(newBuffer);
//			newBuffer = NULL;
//		}
		
		buff[length++] = c;
	}
	
	buff[length] = '\0';
	
//	if (length % BUFFER_SIZE != 0) {
//		newBuffer = malloc(length * sizeof(*newBuffer));
//		memcpy(newBuffer, buff, length);
//		buff = newBuffer;
//		free(newBuffer);
//		newBuffer = NULL;
//	}
	
	return buff;
}

Node * parseTree(const char * input, size_t start, size_t end) {
	
	char c;
	size_t size = 0;	// How many children does a node have
	size_t v_level = 0; // Vertical level of the tree
	
//	printf("Input:\t");
	
	for (size_t i = start ; i < end ; i++) {
		
		c = input[i];
		('[' == c) ? v_level++ : v_level--;
		if (v_level == 0) { size++; }
//		printf("%c",c);
		
	}
//	printf("\n");
	
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
		}
		
	}
	
	return root;
	
}

void printTree(Node * tree) {
	
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
