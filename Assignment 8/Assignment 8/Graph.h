//
//  Graph.h
//  Assignment 8
//
//  Created by Jackson Petty on 4/15/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "HashMap.h"

#include <stdbool.h>
#include <stdio.h>

// MARK: - Data Structures

/**
 A vertex in a directed graph. All
 connected vertices have a string whose
 length is strictly less than the partent
 vertex.
 
 @param isValidPath	Boolean flag. @c true indicates
 that there is a path to a vertex whose string
 is of length one; false indicates the opposite.
 
 @param string	A string which is used to build all
 descendent vertices.
 
 @param size	The number of connections from this
 vertex to others. Since this graph is directed,
 this property is not a equivalence relation.
 
 @param connections	An array of length @c size whose
 members are vertices built from the string of
 this vertex.
 */
typedef struct vertex {
	bool isValidPath;
	char * string;
	size_t size;
	struct vertex ** connections;
} Vertex;

// MARK: - Functions

/**
 Builds a directed graph from the input string, whose vertices
 contain substrings of length strictly less than the input string.
 Valid substrings are made by an affirmative result of @c checkChars()
 for all possible pairs of characters in the input string.
 
 @param string	The input string for this vertex. All connections
 from this vertex will have substrings built from this.
 
 @param hashset	A hashtable whose entries are guaranteed to be unique.
 
 @return A vertex in a directed graph.
 */
Vertex * buildGraph(char * string, Element ** hashset);

/**
 Prints a path from a node to a substring of length
 one, or returns if no such path exists.
 
 @param graph	A directed graph whose vertices
 contain strings.
 */
void printGraph(Vertex * graph);

void destroyGraph(Vertex * graph);

#endif /* Graph_h */
