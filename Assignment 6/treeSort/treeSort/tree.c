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

/**
 A node in a tree with arbitrarily many children.
 @c size is the total number of descendants of the node
 plus one. @c width is the number of children the node
 has. @c parent is a pointer to the root node of the tree.
 @c children is an array of pointers to the child nodes.
*/
struct node {
	size_t width;
	size_t size;
	Node * parent;
	Node * children[];
};

// MARK: - Static Functions

/**
 Creates a dynamically allocated node with the given
 number of children. When returned, the @size is 1,
 the @c parent is a NULL pointer, the @children is
 an array of NULL pointers, and the @c width is the
 parameter passed to the function call.
 
 @param children	The number of child nodes of this node.
 
 @return A pointer to a disjoint node with space for @c children child nodes.
*/
static Node * createNodeWithChildren(size_t children) {
	
	Node * node = malloc(sizeof(*node) + children * sizeof(*node->children));
	if (NULL == node) {
		fprintf(stderr, "Fatal Error: Unable to create node.\n");
		exit(ERR_BAD_NODE);
	}
	
	node->size = 1;
	node->width = children;
	node->parent = NULL;
	memset(node->children, NULL, children);
	
	return node;
}

/**
 Compares two trees based on their @c size. Implemented
 so that the resultant tree will be sorted in descending
 order.
 
 @param treeA A constant void pointer, to be cast to a Node *.
 @param treeB A constant void pointer, to be case to a Node *.
 
 @return treeA->size < treeB->size.
*/

static inline int compareTrees(const void * treeA, const void * treeB) {
	const Node * const lhs = *(Node **)treeA;
	const Node * const rhs = *(Node **)treeB;
	return (int)(lhs->size < rhs->size);
}

// MARK: - Public Functions

/**
 Sorts a tree based on how many children each node has.
 Recursively calls itself on all non-trivial sub-trees.
 Implementation is based on the @c qsort library function.
 Resultant tree will be sorted in descending order of @c size.
 
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
			if (level == 0) { break; } else { level--; }
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
	
	Node * root;
	size_t v_level = 0;			 // Vertical level of the tree
	size_t children = 0;		 // How many children does a node have
	size_t boundary[2] = {0, 0}; // Start and end points for recursive call.
	
	for (size_t i = start; i < end ; i++) {
		
		input[i] == '[' ? v_level++ : v_level--;
		if (v_level == 0) { children++; }
		
	}
	
	root = createNodeWithChildren(children);
	
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

/**
 Prints each node, then callus itself recursively to print all child nodes.
 
 @param tree	A pointer to the root node of the tree.
*/
void printTree(Node * tree) {
	
	if (tree == NULL) { return; }
	
	printf("[");
	
	for (size_t i = 0; i < tree->width; i++) {
		printTree(tree->children[i]);
	}
	
	printf("]");
}

/**
 Destroys a tree recursively from the root node.
 
 @param tree	A pointer to the root node of the tree.
*/
void fellTree(Node * tree) {
	
	if (tree == NULL) { return; }
	
	for (size_t i = 0; i < tree->width; i++) {
		fellTree(tree->children[i]);
	}

	free(tree);
	tree = NULL;
}
