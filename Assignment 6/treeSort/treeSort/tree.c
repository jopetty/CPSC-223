//
//  tree.c
//  treeSort
//
//  Created by Jackson Petty on 3/25/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "tree.h"

struct node {
	unsigned int size;
	struct node * children[];
};

void swap(Node * array[], size_t i, size_t j) {
	Node * tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

/**
 Implements the selection sort algorithm.
 If time permits (it should), this should hopefully
 be replaced by a merge sort implementation.
*/
static void sortChildren(Node * root) {
	unsigned int min;
	for (int i = 0; i < root->size - 1; i++) {
		min = i;
		for (int j = i+1; j < root->size; j++) {
			if (root->children[j]->size < root->children[min]->size) {
				min = j;
			}
		}
		if (min != i) {
			swap(root->children, i, min);
		}
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
