//
//  array.c
//  Assignment 7
//
//  Created by Jackson Petty on 4/6/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "array.h"

#include <stdio.h>

#define ERR_BAD_SIZE	(1)
#define ERR_BAD_ALLOC	(2)

#define SUBARRAY_SIZE	(512)

typedef struct tree {
	size_t size;
	int value;
	struct tree * left;
	struct tree * right;
	struct tree * parent;
} Tree;

/**
 An array.
 */
struct array {
	Tree * data;
};

// MARK: - Private Functions

void fellTree(Tree * tree) {
	// Unimplemented
}

// MARK: - Public Functions

/**
 Creates a new array of size @c n,
 ininialized to all zeros.
 
 Runs in O(n) time.
*/
Array * arrayCreate(int (*combine)(int, int), size_t n) {
	
	if (n == 0) {
		fprintf(stderr, "Fatal Error: Cannot create Array of size 0.\n");
		exit(ERR_BAD_SIZE);
	}
	
	// Unimplemented
	
	return NULL;
	
}

void arrayDestroy(Array * array) {
	
	if (array == NULL) {
		return;
	}
	
	fellTree(array->data);
	
	free(array);
	array = NULL;
	
}



















