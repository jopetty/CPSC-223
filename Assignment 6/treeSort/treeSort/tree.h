//
//  tree.h
//  treeSort
//
//  Created by Jackson Petty on 3/25/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include <stdio.h>

/**
 A node in a tree with arbitrarily many children.
 */
typedef struct node Node;

/**
 Sorts a tree based on how many children each node has.
 Recursively calls itself on all non-trivial sub-trees.
 Implementation is based on the @c qsort library function.
 Resultant tree will be sorted in descending order of @c size.
 
 @param root	Pointer to the root node of a sub-tree.
 */
void sortTree(Node * root);

/**
 Parses a sanitized non-empty input string
 into a single tree. Input must be a valid
 sequence, or this will fail with a fatal
 error.
 
 @return The root node of the tree.
 */
Node * parseTree(const char * input, size_t start, size_t end);

/**
 Parse the input from stdin into a NULL terminated
 buffer, which is then passed to the tree parser.
 While parsing stdin, input is sanitized to remove
 any illegal characters, or throw errors if input
 is invalid. If a sring is returned from @c parseInput,
 it is guaranteed to describe a valid tree.
 
 @return The sanitized string of the tree.
 */
char * parseInput(void);

/**
 Prints each node, then callus itself recursively to print all child nodes.
 
 @param tree	A pointer to the root node of the tree.
 */
void printTree(Node * tree);

/**
 Destroys a tree recursively from the root node.
 
 @param tree	A pointer to the root node of the tree.
 */
void fellTree(Node * tree);

#endif /* tree_h */
