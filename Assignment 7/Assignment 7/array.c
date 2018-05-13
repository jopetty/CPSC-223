////
////  array.c
////  Assignment 7
////
////  Created by Jackson Petty on 4/6/18.
////  Copyright © 2018 Jackson Petty. All rights reserved.
////
//
//#include "array.h"
//
//#include <stdio.h>
//
//#define ERR_BAD_SIZE	(1)
//#define ERR_BAD_ALLOC	(2)
//
//typedef struct tree {
//	int value;
//	size_t index;
//	int aggregate;
//	struct tree * left;
//	struct tree * right;
//} Tree;
//
///**
// An array.
// */
//struct array {
//	size_t size;
//	Tree * data;
//	int (*combine)(int, int);
//};
//
//// MARK: - Private Functions
//
//Tree * createTree(void) {
//	Tree * tree = malloc(sizeof(*tree));
//	if (tree == NULL) {
//		fprintf(stderr, "Fatal Error: Unable to create tree.\n");
//		exit(ERR_BAD_ALLOC);
//	}
//
//	tree->index = 1;
//	tree->value = 0;
//	tree->aggregate = -1;
//	tree->left = NULL;
//	tree->right = NULL;
//
//	return tree;
//}
//
//Tree * buildTree(size_t low, size_t high) {
//
//	size_t diff = high - low;
//	size_t i = (high + low) / 2;
//
//	if (diff == 0) { return NULL; }
//
//	Tree * root = createTree();
//	root->value = 0;
//	root->index = i;
//	root->left = buildTree(low, i);
//	root->right = buildTree(i + 1, high);
//
//	return root;
//}
//
//void fellTree(Tree * tree) {
//
//	if (tree == NULL) { return; }
//
//	if (tree->left != NULL)  { fellTree(tree->left); }
//	if (tree->right != NULL) { fellTree(tree->right); }
//
//	free(tree);
//	tree = NULL;
//}
//
///**
// Returns a pointer to the tree with the
// given value, or the closest match,
// depending on the @c mode.
//
// If @c mode is zero, and no match is
// found, @c findValue with return @c NULL.
//*/
//Tree * findValue(Tree * tree, int n) {
//	if (tree == NULL || tree->value == n) {
//		return tree;
//	} else if (tree->value > n) {
//		return findValue(tree->left, n);
//	} else {
//		return findValue(tree->right, n);
//	}
//}
//
//
//int getValueAtIndex(const Tree * tree, const size_t i) {
//
//	if (tree == NULL) { return 0; }
//
//	if (i == tree->index) {
//		return tree->value;
//	} else if (i > tree->index) {
//		return getValueAtIndex(tree->right, i);
//	} else {
//		return getValueAtIndex(tree->left, i);
//	}
//}
//
//void setValueAtIndex(Tree * tree, size_t i, int v) {
//	if (tree == NULL) { return; }
//
//	if (i == tree->index) {
//		tree->value = v;
//	} else if (i > tree->index) {
//		setValueAtIndex(tree->right, i, v);
//	} else {
//		setValueAtIndex(tree->left, i, v);
//	}
//}
//
//void setAggAtIndex(Tree * tree, size_t i, int v) {
//	if (tree == NULL) { return; }
//
//	if (i == tree->index) {
//		tree->value = v;
//	} else if (i > tree->index) {
//		setValueAtIndex(tree->right, i, v);
//	} else {
//		setValueAtIndex(tree->left, i, v);
//	}
//}
//// MARK: - Public Functions
//
///**
// Creates a new array of size @c n,
// ininialized to all zeros.
//
// Runs in O(n) time.
//*/
//Array * arrayCreate(int (*combine)(int, int), size_t n) {
//
//	if (n == 0) {
//		fprintf(stderr, "Fatal Error: Cannot create Array of size 0.\n");
//		exit(ERR_BAD_SIZE);
//	}
//
//	Array * array = malloc(sizeof(*array));
//	array->size = n;
//	array->combine = combine;
//	array->data = buildTree(0, n);
//
//	return array;
//
//}
//
///**
// Frees all memory allocated for an array.
//
// Runs in O(n) time.
//*/
//void arrayDestroy(Array * array) {
//
//	if (array == NULL) {
//		return;
//	}
//
//	fellTree(array->data);
//
//	free(array);
//	array = NULL;
//
//}
//
///**
// Returns the @c i-th element of the array,
// or 0 if @c i is out of range.
//*/
//int arrayGet(const Array * array, size_t i) {
//	if (array == NULL) {
//		return 0;
//	}
//
//	if (i > array->size) {
//		return 0;
//	}
//
//	return getValueAtIndex(array->data, i);
//}
//
//void arraySet(Array * array, size_t i, int v) {
//	if (array == NULL) { return; }
//
//	if (i > array->size) { return; }
//
//	setValueAtIndex(array->data, i, v);
//}
//
//size_t arraySize(const Array * array) {
//	if (array == NULL) { exit(3); }
//
//	return array->size;
//}
//
//int arrayCombine(const Array * array, size_t k) {
//	if (array == NULL) { exit(3); }
//
//	if (k == 0 || k > array->size) {
//		return arrayCombine(array, array->size);
//	}
//
//	int accumulator = arrayGet(array, 0);
//
//	for (size_t i = 1; i < k; i++) {
//		accumulator = array->combine(accumulator, arrayGet(array, i));
//	}
//
//	return accumulator;
//}
//
//void printArray(const Array * self) {
//	for (size_t i = 0; i < self->size; i++) {
//		printf("%d ", arrayGet(self, i));
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
