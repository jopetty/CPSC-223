//
//  ant.c
//  Ants
//
//  Created by Jackson Petty on 3/3/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "ant.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define MAX_UNI_SZE	(UINT16_MAX)
#define HASH_BYTES	(100)

#define ERR_ANT_FRM	(1)
#define ERR_NO_CHAR	(-1)

// MARK: - Properties

/**
 Contains a character and a position in the universe.
 Tiles are added onto the hash table, and the character
 is retrieved by first computing the hash of the position,
 and then checking the position against the target to
 mitigate collisions.
*/
typedef struct tile {
	int character;
	unsigned int x;
	unsigned int y;
	unsigned int z;
	
	struct tile * next;
} Tile;

/*
 A hash table for Tiles. Implemented as a 2^16 bit array of
 linked lists of Tiles. Indices are accessed via the hash
 function. If no Tiles are placed in a given slot, the
 pointers default to NULL.
*/
struct universe {
	Tile * data[MAX_UNI_SZE];
};

// MARK: - Private Methods

static uint16_t getHashIndex(unsigned int x, unsigned int y, unsigned int z) {
	
	size_t hash[3] = {x,y,z};
	for (size_t i = 0; i < 12; i++) {
		for (size_t j = 0; j < 3; j++) {
			hash[j] = ((hash[j] >> 8)^hash[j])*0x6B + i;
		}
	}
	
	// Downcast to prevent over-indexing.
	// & + is just from fiddling around to find the fewest collisions.
	uint16_t h = (uint16_t)(hash[0] & hash[1] + hash[2]);
	return h;
}

/**
 Creates a new tile in the universe with the character
 and position of an Ant.
 
 @param ant	An ant.
 
 @return A pointer to a tile with a NULL next reference.
*/
static Tile * createTileFromAnt(Ant ant) {
	
	Tile * t = malloc(sizeof(*t));
	t->character = ant.character;
	t->x = ant.x;
	t->y = ant.y;
	t->z = ant.z;
	t->next = NULL;
	
	return t;
}

// MARK: - Public Methods

/**
 Creates a new, empty universe of NULL Tile pointers.
 In the context of the application, the universe should
 be a singleton.
 
 @return A pointer to the new universe.
*/
Universe * createUniverse(void) {
	
	Universe * universe = malloc(sizeof(*universe));
	if (NULL == universe) {
		fprintf(stderr, "Fatal Error: Could not initialize a Universe.\n");
		exit(ERR_ANT_FRM);
	}
	for (size_t i = 0; i < MAX_UNI_SZE; i++) {
		universe->data[i] = NULL;
	}
	
	return universe;
}

/**
 Frees all dynamically allocated memory in the universe;
 Frees all tiles and then the universe wrapper itself.
 
 @param universe	The singleton universe.
*/
void destroyUniverse(Universe * universe) {
	
	if (universe == NULL) { return; }
	
	size_t count = 0;
	for (size_t i = 0; i < MAX_UNI_SZE; i++) {
		if (universe->data[i]) {
			Tile * next;
			Tile * curr = universe->data[i];
			while (curr) {
				count++;
				if (curr->next) {
					next = curr->next;
					free(curr);
					curr = next;
				} else {
					free(curr);
					curr = NULL;
				}
			}
//			fprintf(stderr, "Universe[%zu] had %zu entries.\n", i, count);
			count = 0;
		}
	}
	
	free(universe);
	universe = NULL;
}

/**
 Creates a new Ant at (0,0,0) with the given character.
 
 @param c	An ASCII character (0--255).
 
 @return An Ant with values {c, 0, 0, 0}.
*/
inline Ant createAntWithCharacter(int c) {
	return (Ant) {
		.character = c,
		.x = 0,
		.y = 0,
		.z = 0
	};
}

/**
 Retrieves the character placed at a given position, or
 a space (' ') if no character was placed there.
 
 @param ant	The ant located at the requested position.
 @param universe	The singleton universe.
 
 @return The character located at the ant's position, or
 a space if no character has been placed.
*/
int getCharAt(Ant ant, Universe * universe) {
	
	size_t index = getHashIndex(ant.x, ant.y, ant.z);
	Tile * tile = universe->data[index];
	while (tile) {
		if (tile->x == ant.x && tile->y == ant.y && tile->z == ant.z) {
			return tile->character;
		} else {
			tile = tile->next;
		}
	}
	
	return ' ';
	
}

/**
 Places the ant's character at the ants current location.
 If the location as been marked before, the character at
 that position is simply changed to the current character;
 otherwise, a new Tile is constructed and placed at the
 end of the linked list for that particular hash value.
 
 @param ant	The ant in question.
 @param universe	The singleton universe
*/
void placeAntAt(Ant ant, Universe * universe) {
	
	Tile * tile;
	size_t i = getHashIndex(ant.x, ant.y, ant.z);
	
	// Check if the hash table is not NULL for this position
	if ((tile = universe->data[i])) {
		
		while (tile) { // Find the value in the hash table with the right position
			if ((tile->x == ant.x) && (tile->y == ant.y) && (tile->z == ant.z)) {
				tile->character = ant.character;
				return;
			} else {
				if (tile->next) {
					tile = tile->next;
				} else {
					break; // No value matches the current position
				}
			}
		}
		
		Tile * newtile = createTileFromAnt(ant);
		tile->next = newtile;
		
	} else {
		tile = createTileFromAnt(ant);
		universe->data[i] = tile;
	}
}
