//
//  rope.c
//  Assignment 7
//
//  Created by Jackson Petty on 4/12/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "rope.h"

#include <assert.h>
#include <stdlib.h>

// Mark: - Data Structures

typedef struct node Node;
typedef struct leaf Leaf;

struct node {
	size_t low;
	size_t high;
	int aggregate;
	
	Node * left;
	Node * right;
	
	Leaf * leftLeaf;
	Leaf * rightLeaf;
	
	Node * parent;
};

typedef struct leaf {
	size_t index;
	int value;
	
	Node * parent;
} Leaf;

struct array {
	Node * data;
	int (*combine)(int, int);
};

// MARK: - Static Functions

static Leaf * createLeafWithIndex(size_t i) {
	Leaf * leaf = malloc(sizeof(*leaf));
	assert(leaf);
	
	leaf->index = i;
	leaf->value = 0;
	leaf->parent = NULL;
	
	return leaf;
}

static Node * createNodeWithRange(size_t low, size_t high) {
	assert(high >= low);
	Node * node = malloc(sizeof(*node));
	assert(node);
	
	node->high = high;
	node->low = low;
	node->aggregate = 0;
	node->left = NULL;
	node->right = NULL;
	node->leftLeaf = NULL;
	node->rightLeaf = NULL;
	
	// Create children nodes or leaves
	if (high - low == 0) { // Create a leaf node here
		Leaf * leaf = createLeafWithIndex(low);
		leaf->parent = node;
		node->leftLeaf = leaf;
	} else if (high - low == 1) { // Create two leaevs here
		Leaf * lLeaf = createLeafWithIndex(low);
		lLeaf->parent = node;
		node->leftLeaf = lLeaf;
		
		Leaf * rLeaf = createLeafWithIndex(high);
		rLeaf->parent = node;
		node->rightLeaf = rLeaf;
	} else {
		size_t n = (high - low) / 2;
		node->left = createNodeWithRange(low, low + n);
		node->right = createNodeWithRange(low + n + 1, high);
		
		node->left->parent = node;
		node->right->parent = node;
	}
	
	return node;
	
}

static Leaf * getLeafAtIndex( Node * node, size_t i) {
	assert(node);
	
	if (i < node->low || i > node->high) {
		return NULL;
	}
	
	// Check if there are any leaf nodes
	if (node->leftLeaf != NULL || node->rightLeaf != NULL) {
		
		if (node->leftLeaf->index == i) { return node->leftLeaf; }
		if (node->rightLeaf->index == i) { return node->rightLeaf; }
		
		return NULL; // Leaf is not in the tree,
	} else { // Not a parent node
		
		size_t n = (node->high - node->low) / 2;
		return i <= node->low + n ? getLeafAtIndex(node->left, i) : getLeafAtIndex(node->right, i);
	}
}

static int findAggOfInterval(size_t low, size_t high, int (*combine)(int, int), Node * node) {
	if (node->high == high && node->low == low || ((high == low)) {
		return node->aggregate;
	} else { // left, right, or both
		size_t mid = (node->low + node->high) / 2; // middle of node range
		if (high > mid && low > mid) { // right
			return findAggOfInterval(low, high, combine, node->right);
		} else if (high < mid && low < mid) { // left
			return findAggOfInterval(low, high, combine, node->left);
		} else {
			return combine(findAggOfInterval(low, mid, combine, node->left), findAggOfInterval(mid + 1, high, combine, node->right));
		}
	}
}

// MARK: - Public Functions
Array * arrayCreate(int (*combine)(int, int), size_t n) {
	assert(n > 0);
	
	Array * self = malloc(sizeof(*self));
	assert(self);
	
	Node * node = createNodeWithRange(0, n);
	self->data = node;
	self->combine = combine;
	
	for (size_t i = 0; i < n; i++) {
		arraySet(self, i, 0);
	}
	
	return self;
}

void arraySet(Array * self, size_t i, int v) {
	assert(self);
	
	if (i > self->data->high) { return; }
	
	Leaf * leaf = getLeafAtIndex(self->data, i);
	if (leaf) { leaf->value = v; }
	
	Node * current = leaf->parent;
	while (current) {
		
		// Test leaves
		if (current->leftLeaf) {
			if (current->rightLeaf) {
				current->aggregate = self->combine(current->leftLeaf->value,
												   current->rightLeaf->value);
			} else if (current->right) {
				current->aggregate = self->combine(current->leftLeaf->value,
												   current->right->aggregate);
			} else {
				current->aggregate = current->leftLeaf->value;
			}
		} else if (current->rightLeaf) {
			if (current->left) {
				current->aggregate = self->combine(current->left->aggregate,
												   current->rightLeaf->value);
			} else {
				current->aggregate = current->rightLeaf->value;
			}
		} else if (current->left) {
			if (current->right) {
				current->aggregate = self->combine(current->left->aggregate,
												   current->right->aggregate);
			} else {
				printf("What the fuck!!");
			}
			
		}
		
		printf("The range %zu - %zu has value %d\n", current->low, current->high, current->aggregate);
		current = current->parent;
	}
}

size_t arraySize(const Array * self) {
	assert(self);
	
	return self->data->high - self->data->low;
}

void printArray(const Array * self) {
	for (size_t i = self->data->low; i < self->data->high; i++) {
		Leaf * leaf = getLeafAtIndex(self->data, i);
		if (leaf) { printf("%zu: %d\n", leaf->index, leaf->value); }
	}
}

int arrayCombine(const Array * self, size_t k) {
	Node * node = self->data;
	
	if (node->high <= k) {
		return node->aggregate;
	} else {
		return findAggOfInterval(0, k, self->combine, node);
	}
}




