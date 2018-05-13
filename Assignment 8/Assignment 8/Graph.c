//
//  Graph.c
//  Assignment 8
//
//  Created by Jackson Petty on 4/15/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "Graph.h"

#include "HashMap.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct metaelt {
	Vertex * vertex;
	struct metaelt * next;
} MetaElement;

// MARK: - Private Functions

/**
 Checks to see if two characters are a match in the game.
 This occurs when either 1) both characters are vowels, or
 2) when the ASCII difference of the two characters is at
 most 5. If The characters are matches, we can stack the
 rightmost on top of the leftmost.
 
 @param a	The leftmost character.
 @param b	The rightmost character.
 
 @return Whether @c a and @c b can be stacked.
 */
bool checkChars(const char a, const char b) {
	
	// Check if both chars are vowels
	if ((a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') &&
		(b == 'a' || b == 'e' || b == 'i' || b == 'o' || b == 'u')) {
		return true;
	} else if (a - b <= 5 && a - b >= -5) { // Check ASCII difference
		return true;
	}
	
	return false;
}

/**
 Creates a new vertex from a given string.
*/
Vertex * newVertexFromString(char * string) {
	
	Vertex * vertex = malloc(sizeof(*vertex));
	assert(vertex);
	
	vertex->isValidPath = false;
	vertex->string = string;
	
	// Make each vertex have by default 0 children
	vertex->connections = NULL;
	vertex->size = 0;
	
	return vertex;
}

/**
 Buids a new string out of the original by moving the character
 at the index &c stack to index @ignore and removing the
 character currently at index @ignore, resulting in a new string
 which is one character shorter than the original.
 
 @param old	The original string.
 @param ignore	The index of the character to be deleted.
 @param stack	The index of the card to be moved to @c ignore.
 
 @return new The new string.
 */
char * buildString(const char * old, size_t ignore, size_t stack) {
	
	size_t offset = 0;
	size_t length = strlen(old);
	char * new = malloc(length * sizeof(char));
	
	new[ignore] = old[stack];
	for (size_t i = 0; i < ignore; i++) {
		new[i] = old[i];
	}
	for (size_t i = ignore + 1; i < length; i++) {
		if (i == stack) { offset++; length--; }
		new[i] = old[i + offset];
	}
	new[length] = '\0';
	
	return new;
}

// MARK: - Public Functions

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
Vertex * buildGraph(char * string, Element * hashset[]) {
	
	size_t length = strlen(string);
	if (length == 1) {
		Vertex * graph = malloc(sizeof(*graph));
		assert(graph);
		graph->string = string;
		graph->size = 0;
		graph->connections = NULL;
		graph->isValidPath = true;
		
		return graph;
	}

	// Linked List of all unique vertices built from
	// this string.
	MetaElement * vList = NULL;
	size_t children = 0;
	
	for (size_t i = 0; i < length; i++) {
		if (i + 1 < length) {
			if (checkChars(string[i], string[i + 1])) {
				
				children++;
				
				char * substring = buildString(string, i, i+1);
				size_t index = getHashIndex(substring);
				Element * element = getHashElement(substring, index, hashset);

				if (element ==  NULL) {
					Vertex * newV = buildGraph(substring, hashset);
					Element * newElement = malloc(sizeof(*element));
					newElement->vertex = newV;
					newElement->next = NULL;
					placeElement(newElement, index, hashset);
					element = newElement;
				} else {
					free(substring);
				}
				
				MetaElement * newElt = malloc(sizeof(*newElt));
				newElt->vertex = element->vertex;
				
				newElt->next = vList;
				vList = newElt;
				
				if (((Vertex *)(element->vertex))->isValidPath) {
					break;
				}
			}
		}
		if (i + 3 < length) {
			if (checkChars(string[i], string[i + 3])) {
				
				children++;
				
				char * substring = buildString(string, i, i+3);
				size_t index = getHashIndex(substring);
				Element * element = getHashElement(substring, index, hashset);
				
				if (element ==  NULL) {
					Vertex * newV = buildGraph(substring, hashset);
					Element * newElement = malloc(sizeof(*element));
					newElement->vertex = newV;
					newElement->next = NULL;
					placeElement(newElement, index, hashset);
					element = newElement;
				} else {
					free(substring);
				}
				
				MetaElement * newElt = malloc(sizeof(*newElt));
				newElt->vertex = element->vertex;
				
				newElt->next = vList;
				vList = newElt;
				
				if (((Vertex *)(element->vertex))->isValidPath) {
					break;
				}
			}
		}
	}
	
	// Create vertex and fill its descendents with vertexList nodes
	Vertex * graph = newVertexFromString(string);
	graph->size = children;

	graph->connections = malloc(children * sizeof(Vertex *));
	for (size_t i = 0; i < graph->size; i++) {
		graph->connections[i] = NULL;
	}
	
	size_t i = 0;
	MetaElement * walker = vList;
	while (walker) {
		graph->connections[i++] = walker->vertex;
		walker = vList->next;
		if (vList) { free(vList); }
		vList = walker;
	}
	
	if (length == 1) {
		graph->isValidPath = true;
	} else {
		graph->isValidPath = false;
		for (size_t i = 0; i < graph->size; i++) {
			graph->isValidPath = graph->isValidPath || graph->connections[i]->isValidPath;
		}
	}

	return graph;
	
}

/**
 Prints a path from a node to a substring of length
 one, or returns if no such path exists.
 
 @param graph	A directed graph whose vertices
 contain strings.
*/
void printGraph(Vertex * graph) {
	
	if (graph == NULL || !(graph->isValidPath)) {
		return;
	}
	
	printf("%s\n", graph->string);
	for (size_t i = 0; i < graph->size; i++) {
		if (graph->connections[i]->isValidPath) {
			printGraph(graph->connections[i]);
			break;
		}
	}
}
