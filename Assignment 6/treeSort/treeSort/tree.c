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
	Node * node = malloc(sizeof(*node) + size);
	if (NULL == node) {
		fprintf(stderr, "Fatal Error: Unable to create node.\n");
		exit(ERR_BAD_NODE);
	}
	
	node->size = size;
	node->parent = NULL;
	
	memset(node + sizeof(node->size) + sizeof(node->parent), NULL, size);
	
	return node;
}

/**
 Implements the selection sort algorithm.
 If time permits (it should), this should hopefully
 be replaced by a merge sort implementation.
*/
static void sortChildren(Node * root) {
	
	size_t min;
	for (size_t i = 0; i < root->size - 1; i++) {
		
		min = i;
		for (size_t j = i+1; j < root->size; j++) {
			if (root->children[j]->size < root->children[min]->size) {
				min = j;
			}
		}
		
		if (min != i) { swap(root->children, i, min); }
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
	size_t length = 0;
	char * buffer = malloc(BUFFER_SIZE);
	
	while ((c = getchar()) != EOF) {
		if (++length < (BUFFER_SIZE - 1)) {
			buffer[length - 1] = c;
		} else {
			// Reallocate the buffer
			char * newBuffer = realloc(buffer, length / BUFFER_SIZE); // NOTE: May be an off by one error here
			buffer = newBuffer;
			// the following lines may be bad
			free(newBuffer);
			newBuffer = NULL;
		}
	}
	
	buffer[length] = '\0';
	
	// Trim the buffer if too long
	if (BUFFER_SIZE % length != 0) {
		char * newBuffer = realloc(buffer, length);
		buffer = newBuffer;
		// Again, these may be bad
		free(newBuffer);
		newBuffer = NULL;
	}
	
	return buffer;
}

Node * parseTree(char * input) {
	int c;
	size_t v_level = 0;
	size_t h_level = 0;
	Node * tree = NULL;
	Node * currentNode = NULL;
	
	while ((c = getchar()) != EOF) {
		switch (c) {
			case '[':
				v_level++;
				h_level++;
				
				// Create node
				// Add to parent at the appropriate index
				currentNode =
				
				break;
				
			case ']':
				if (v_level > 0) {
					
				} else { // Too many closing braces
					fellTree(tree);
					exit(ERR_BAD_INPUT);
				}
				
			default:
				if (v_level == 0) {
					return tree;
				} else {
					fellTree(tree);
					exit(ERR_BAD_INPUT);
				}
				break;
		}
	}
	
	if (v_level == 0) {
		return tree;
	} else {
		fellTree(tree);
		exit(ERR_BAD_INPUT);
	}
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
	
	free(tree->children);
	free(tree);
	tree = NULL;
}
