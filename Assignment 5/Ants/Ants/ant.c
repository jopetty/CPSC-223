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

#define MAX_UNI_SZE		(UINT16_MAX) // Number of entries in hash table
#define ERR_UNIVERSE	(1)			 // Status if Universe is NULL

// MARK: - Properties

/**
 Contains a character and a position in the universe.
 Tiles are added onto the hash table, and the character
 is retrieved by first computing the hash of the position,
 and then checking the position against the target to
 mitigate collisions.
 
 Positions are stored as unsigned integers to make conversion
 to an array index via the hash function easier.
*/
typedef struct tile {
	uint16_t character;
	Position position;
	struct tile * next;
} Tile;

/**
 A hash table for Tiles. Implemented as a 2^16 bit array of
 linked lists of Tiles. Indices are accessed via the hash
 function. If no Tiles are placed in a given slot, the
 pointers default to NULL.
*/
struct universe {
	Tile * data[MAX_UNI_SZE];
};

// MARK: - Private Functions

/**
 Computes a 16-bit hash of the input position and returns
 the value as an array index. The algorithm hashes each
 coordinate independently, and then combines them via
 @p hash @p = @p hash(x) @p & @p (hash(y) @p + @p hash(z)).
 This combination was found through trial and error to
 produce relatively few collisions.
 
 @param position	The current position.
 
 @returns The hash of the tuple @p (x,y,z).
*/
static uint16_t getHashIndex(Position position) {
	
	size_t hash[3] = { position.x, position.y, position.z };
	for (size_t i = 0; i < 12; i++) {
		for (size_t j = 0; j < 3; j++) {
			hash[j] = ((hash[j] >> 8)^hash[j])*0x6B + i;
		}
	}
	
	// Downcast to prevent over-indexing
	return (uint16_t)(hash[0] & (hash[1] + hash[2]));
}

/**
 Creates a new tile in the universe with the character
 and position of an Ant.
 
 @param ant	An ant.
 
 @return A pointer to a tile with a NULL next reference.
*/
static Tile * createTileFromAnt(Ant ant) {
	
	Tile * tile = malloc(sizeof(*tile));
	tile->character = ant.character;
	tile->position = ant.position;
	tile->next = NULL;
	
	return tile;
}

// MARK: - Public Functions

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
		exit(ERR_UNIVERSE);
	}
	for (size_t i = 0; i < MAX_UNI_SZE; i++) {
		universe->data[i] = NULL;
	}
	
	return universe;
}

/**
 Frees all dynamically allocated memory in the universe;
 Frees all tiles and then the universe wrapper itself.
 
 @param universe	The universe.
*/
void destroyUniverse(Universe * universe) {
	
	if (universe == NULL) { return; }
	
	for (size_t i = 0; i < MAX_UNI_SZE; i++) {
		if (universe->data[i]) {
			Tile * next;
			Tile * curr = universe->data[i];
			while (curr) {
				if (curr->next) {
					next = curr->next;
					free(curr);
					curr = next;
				} else {
					free(curr);
					curr = NULL;
				}
			}
		}
	}
	
	free(universe);
	universe = NULL;
}

/**
 Creates a new Ant at (0,0,0) with the given character.
 
 @param character	An ASCII character (0--255).
 
 @return An Ant with values @p {c,0,0,0}.
*/
inline Ant createAntWithCharacter(uint16_t character) {
	return (Ant) {
		.character = character,
		.position = (Position) { .x = 0, .y = 0, .z = 0 }
	};
}

/**
 Retrieves the character placed at a given position, or
 a space (' ') if no character was placed there.
 
 @param position	The requested position.
 @param universe	The universe.
 
 @return The character located at the given position, or
 a space if no character has been placed.
*/
int getCharAt(Position position, Universe * universe) {
	
	if (NULL == universe) { return ' '; }
	
	Tile * tile = universe->data[getHashIndex(position)];
	while (tile) {
		if ((tile->position.x == position.x) &&
			(tile->position.y == position.y) &&
			(tile->position.z == position.z)) {
			
			return tile->character;
		} else {
			tile = tile->next;
		}
	}
	
	return ' ';
	
}

/**
 Places the ant's character at the ant's current location.
 If the location as been marked before, the character at
 that position is simply changed to the current character;
 otherwise, a new Tile is constructed and placed at the
 end of the linked list for that particular hash value.
 
 @param ant	The current ant.
 @param universe	The universe.
*/
void placeChar(Ant ant, Universe * universe) {
	
	if (NULL == universe) {
		fprintf(stderr, "Fatal Error: Attempted to place character in a NULL Universe.\n");
		exit(ERR_UNIVERSE);
	}
	
	Tile * tile;
	size_t i = getHashIndex(ant.position);
	
	// Check if the hash table is not NULL for this position
	if ((tile = universe->data[i])) {
		
		while (tile) { // Check if position is correct
			if ((tile->position.x == ant.position.x) &&
				(tile->position.y == ant.position.y) &&
				(tile->position.z == ant.position.z)) {
				
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
