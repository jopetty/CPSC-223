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

Node * parseTree(void) {
	int c;
	size_t complete = 1; // Has a full tree been parsed?
	size_t level = 0;
	Node * tree = NULL;
	
	while ((c = getchar()) != EOF) {
		switch (c) {
			case '[':
				complete = 0;
				level++;
				break;
				
			case ']':
				if (level > 0) {
					
				} else { // Too many closing braces
					fellTree(tree);
					exit(ERR_BAD_INPUT);
				}
				
			default:
				if (complete) {
					return tree;
				} else {
					fellTree(tree);
					exit(ERR_BAD_INPUT);
				}
				break;
		}
	}
	
	if (complete == 1 && level == 0) {
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
