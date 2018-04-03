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
	size_t width;
	size_t size;
	Node * parent;
	Node * children[];
};

// MARK: - Static Functions

static Node * createNodeWithChildren(size_t children) {
	
	Node * node = malloc(sizeof(*node) + children * sizeof(*node->children));
	if (NULL == node) {
		fprintf(stderr, "Fatal Error: Unable to create node.\n");
		exit(ERR_BAD_NODE);
	}
	
	node->size = 1;
	node->width = children;
	node->parent = NULL;
	for (size_t i = 0; i < children; i++) {
		node->children[i] = NULL;
	}
	
	return node;
}

/**
 Implements the selection sort algorithm.
 If time permits (it should), this should hopefully
 be replaced by a merge sort implementation.
*/

static inline int compareTrees(const void * treeA, const void * treeB) {
	const Node * const leftTree = *(Node **)treeA;
	const Node * const rightTree = *(Node **)treeB;
	return (int)(rightTree->size > leftTree->size);
}

// MARK: - Public Functions

/**
 Sorts a tree based on how many children each node has.
 Recursively calls itself on all non-trivial sub-trees.
 
 @param root	Pointer to the root node of a sub-tree.
*/
void sortTree(Node * root) {
	
	if (root == NULL) { return; }
	
	if (root->width > 0) {
		
		qsort(root->children, root->width, sizeof(Node *), compareTrees);
		
		for (size_t i = 0; i < root->width; i++) {
			sortTree(root->children[i]);
		}
	}
}

/**
 Parse the input from stdin into a NULL terminated
 buffer, which is then passed to the tree parser.
 While parsing stdin, input is sanitized to remove
 any illegal characters, or throw errors if input
 is invalid. If a sring is returned from @c parseInput,
 it is guaranteed to describe a valid tree.
 
 @return The sanitized string of the tree.
*/
char * parseInput(void) {
	
	int c;
	size_t level = 0;
	size_t length = 0;
	size_t size = BUFFER_SIZE;

	char * buffer = malloc(size * sizeof(char));
	
	while ((c = getchar()) != EOF) {
		
		if (c == '[') {
			level++;
		} else if (c == ']') {
			level--;
		} else {
			if (level == 0) {
				break;
			} else {
				free(buffer);
				buffer = NULL;
				exit(ERR_BAD_INPUT);
			}
		}
		
		if (length >= (size-1)) {
			size = ((length / BUFFER_SIZE) + 1) * BUFFER_SIZE;
			char * temp = realloc(buffer, size);
			if (temp != NULL) {
				buffer = temp;
			} else {
				fprintf(stderr, "Fatal Error: Could not reallocate space for buffer.\n");
				exit(ERR_BAD_INPUT);
			}
		}
		
		buffer[length++] = c;
	}
	
	if (length == 0) {
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	
	buffer[length] = '\0';
	
	return buffer;
}

/**
 Parses a sanitized non-empty input string
 into a single tree. Input must be a valid
 sequence, or this will fail with a fatal
 error.
 
 @return The root node of the tree.
*/
Node * parseTree(const char * input, size_t start, size_t end) {
	
	// TODO: Figure out why there is an off-by-one error
	
	size_t children = 0;	// How many children does a node have
	size_t v_level = 0;     // Vertical level of the tree
	
	for (size_t i = start; i < end ; i++) {
		
		input[i] == '[' ? v_level++ : v_level--;
		if (v_level == 0) { children++; }
		
	}
	
	Node * root = createNodeWithChildren(children);
	size_t boundary[2];
	
	children = 0;
	for (size_t i = start; i < end ; i++) {
		
		switch (input[i]) {
			case '[':
				if (v_level++ == 0) {
					boundary[0] = i + 1;
				}
				break;
			
			case ']':
				if (--v_level == 0) {
					boundary[1] = i;
					children++;
				}
				
			default:
				break;
		}
		
		if (v_level == 0) {
			root->children[children - 1] = parseTree(input, boundary[0], boundary[1]);
			root->children[children - 1]->parent = root;
			root->size += root->children[children - 1]->size;
		}
		
	}
	
	return root;
}

void printTree(Node * tree) {
	
	if (tree == NULL) { return; }
	
//	printf("\nNode has size of %d\n", tree->size);
	
	printf("[");
	
	for (size_t i = 0; i < tree->width; i++) {
		printTree(tree->children[i]);
	}
	
	printf("]");
}

void fellTree(Node * tree) {
	
	if (tree == NULL) { return; }
	
	for (size_t i = 0; i < tree->width; i++) {
		fellTree(tree->children[i]);
	}

	free(tree);
	tree = NULL;
}
