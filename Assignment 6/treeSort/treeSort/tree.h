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

typedef struct node Node;

/**
 Sorts a tree based on how many children each node has.
 Recursively calls itself on all non-trivial sub-trees.
 
 @param root	Pointer to the root node of a sub-tree.
 */
void treeSort(Node * root);

Node * parseTree(void);

void printTree(Node * tree);

void fellTree(Node * tree);

#endif /* tree_h */
