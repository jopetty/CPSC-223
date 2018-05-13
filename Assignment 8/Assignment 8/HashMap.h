//
//  HashMap.h
//  Assignment 8
//
//  Created by Jackson Petty on 4/15/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h

#include <stdio.h>
#include <stdint.h>

/**
 An element in a hashtable. If a hash collision
 occurs, elements will form a linked list.
 
 @param vertex	A void pointer to a vertex
 in a graph. Must cast to (Vertex *).
 @param next	The next element in the
 linked list.
*/
typedef struct element {
	void * vertex;
	struct element * next;
} Element;

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
uint16_t getHashIndex(char * string);

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
Element * getHashElement(char * string, size_t index, Element * hashset[]);

/**
 Creates a new hashtable.
 
 @return A new hashtable.
 */
Element ** createHashtable(void);

/**
 Places an element into a hashtable if and only if
 it has not been placed there before.
 
 @param element	A possible element of the hashtable.
 @param index	The index at which the element is to be placed.
 @param hashset	The hashtable.
 */
void placeElement(Element * element, size_t index, Element * hashset[]);

/**
 Frees all memory allocated to a hashtable, including
 all vertices it contains by proxy. This allows for
 linear destruction of a graph referenced in the table.
 
 @param hashset	A Hashtable whose elements are guaranteed
 to be unique.
*/
void destroyHashtable(Element * hashset[]);

#endif /* HashMap_h */
