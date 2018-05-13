//
//  HashMap.c
//  Assignment 8
//
//  Created by Jackson Petty on 4/15/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "HashMap.h"
#include "Graph.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define HASH_SET_SIZE	(UINT16_MAX)

#define ERR_NULL_PTR	(3)

// MARK: - Private Functions

/**
 Frees all linked-list elements, along with all vertices
 contained in those elements. Allows for proxy destruction
 of a graph, since we reference every vertex in the table,
 except the root.
 
 @param list	A linked list of elements.
*/
void destroyLinkedList(Element * list) {
	
	Element * walker;
	while (list) {
		walker = list;
		list = list->next;
		if (walker->vertex) {
			free(((Vertex *)walker->vertex)->string);
			free(((Vertex *)walker->vertex)->connections);
			free(walker->vertex);
		}
		free(walker);
		walker = NULL;
	}
}

// MARK: - Public Functions

/**
 Returns the element in a hash table at a given index, or
 @c NULL if no such element exists. This accessor adds the
 additional guarantee that the element return points to a
 vertex whose string matches the desired string; this serves
 as a protection against collisions in the hash table.
 
 @param string	The string to match any found element against.
 @param index	The hashed index of the string.
 @param hashset	A Hashtable whose elements are guaranteed
 to be unique.
 
 @return A matching element, or @c NULL if none exists.
*/
Element * getHashElement(char * string, size_t index, Element * hashset[]) {
	
	if (hashset == NULL || string == NULL) {
		fprintf(stderr, "Fatal Error: Cannot use a null pointer.\n");
		exit(ERR_NULL_PTR);
	}
	
	Element * current = hashset[index];
	
	while (current) {
		char * testString = ((Vertex *)(current->vertex))->string;
		if (strcmp(testString, string) == 0) {
			return current;
		} else {
			current = current->next;
		}
	}
	
	return current;
}

/**
 Maps between the input string and positive integers
 in the range 0 to HASH_SET_SIZE. Uses prime multipliers
 and xor to try to achieve a fairly uniform distribution
 of indices for similar strings. Hashtable is indexed
 by 16-bit unsigned integers since we create the hashtable
 with space for UINT16_MAX entries.
 
 @param string	The input string.
 
 @return The hash of the input string.
*/
uint16_t getHashIndex(char * string) {
	
	if (string == NULL) {
		fprintf(stderr, "Fatal Error: Cannot use a null pointer.\n");
		exit(ERR_NULL_PTR);
	}
	
	size_t length = strlen(string);
	size_t index = 7;
	
	for (size_t i = 1; i < length; i++) {
		index = ((index * 31) ^ (string[i] * 11)) % HASH_SET_SIZE;
	}
	
	return (uint16_t)index;
}

/**
 Creates a new hashtable.
 
 @return A new hashtable.
*/
Element ** createHashtable(void) {
	
	Element ** hashtable = malloc(sizeof(*hashtable) * HASH_SET_SIZE);
	if (hashtable == (void *)NULL) {
		fprintf(stderr, "Fatal Error: Could not initialize hashtable.\n");
		exit(3);
	}
	
	for (size_t i = 0; i < HASH_SET_SIZE; i++) {
		hashtable[i] = NULL;
	}
	
	return hashtable;
}

/**
 Places an element into a hashtable if and only if
 it has not been placed there before.
 
 @param element	A possible element of the hashtable.
 @param index	The index at which the element is to be placed.
 @param hashset	The hashtable.
*/
void placeElement(Element * element, size_t index, Element * hashset[]) {
	
	if (element == NULL || hashset == NULL) {
		fprintf(stderr, "Fatal Error: Cannot use a null pointer.\n");
		exit(ERR_NULL_PTR);
	}
	
	Element * current = hashset[index];
	char * inputString = ((Vertex *)element->vertex)->string;
	
	// Traverse linked list until we find a match
	// or place element at NULL location
	if (current == NULL) {
		hashset[index] = element;
		element->next = NULL;
	} else {
		char * testString = ((Vertex *)current->vertex)->string;
		while (current->next) {
			if (strcmp(testString, inputString) == 0) {
				return;
			} else {
				current = current->next;
				testString = ((Vertex *)current->vertex)->string;
			}
		}
		
		current->next = element;
		element->next = NULL;
	}
}

/**
 Frees all memory allocated to a hashtable, including
 all vertices it contains by proxy. This allows for
 linear destruction of a graph referenced in the table.
 
 @param hashset	A Hashtable whose elements are guaranteed
 to be unique.
 */
void destroyHashtable(Element * hashset[]) {
	
	if (hashset == NULL) {
		return;
	}
	
	for (size_t i = 0; i < HASH_SET_SIZE; i++) {
		destroyLinkedList(hashset[i]);
	}
	
	free(hashset);
	hashset = NULL;
}
