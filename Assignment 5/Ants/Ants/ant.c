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

/**
 Computes the hash of the input position for lookup in the
 Universe hash table. Implements a modified version of the
 Pearson hash; instead of returning a single 8-bit hash,
 we return a 16-bit hash formed by adding together 2 8-bit
 hashes.
 
 @param x	The X coordinate.
 @param y	The Y coordinate.
 @param z	The Z coordinate.
 
 @return Returns a 16-bit hash index of the input position.
*/
//static size_t oldHashIndex(int x, int y, int z) {
//
//	// Convert positions to string buffers
//	int x_length = snprintf( NULL, 0, "%d", x );
//	char * x_str = malloc( x_length + 1 );
//	snprintf( x_str, x_length + 1, "%d", x );
//
//	int y_length = snprintf( NULL, 0, "%d", y );
//	char * y_str = malloc( y_length + 1 );
//	snprintf( y_str, y_length + 1, "%d", y );
//
//	int z_length = snprintf( NULL, 0, "%d", z );
//	char * z_str = malloc( z_length + 1 );
//	snprintf( z_str, z_length + 1, "%d", z );
//
//	// Concatenate position into a single string
//	char position[x_length + y_length + z_length + 3];
//	strcpy(position, x_str);
//	strcat(position, y_str);
//	strcat(position, z_str);
//
//	// T Table of shuffled values from 0 to 255
//	unsigned char T[256] = {
//		251, 175, 119, 215, 81, 14, 79, 191, 103, 49, 181, 143, 186, 157,  0,
//		232, 31, 32, 55, 60, 152, 58, 17, 237, 174, 70, 160, 144, 220, 90, 57,
//		223, 59,  3, 18, 140, 111, 166, 203, 196, 134, 243, 124, 95, 222, 179,
//		197, 65, 180, 48, 36, 15, 107, 46, 233, 130, 165, 30, 123, 161, 209, 23,
//		97, 16, 40, 91, 219, 61, 100, 10, 210, 109, 250, 127, 22, 138, 29, 108,
//		244, 67, 207,  9, 178, 204, 74, 98, 126, 249, 167, 116, 34, 77, 193,
//		200, 121,  5, 20, 113, 71, 35, 128, 13, 182, 94, 25, 226, 227, 199, 75,
//		27, 41, 245, 230, 224, 43, 225, 177, 26, 155, 150, 212, 142, 218, 115,
//		241, 73, 88, 105, 39, 114, 62, 255, 192, 201, 145, 214, 168, 158, 221,
//		148, 154, 122, 12, 84, 82, 163, 44, 139, 228, 236, 205, 242, 217, 11,
//		187, 146, 159, 64, 86, 239, 195, 42, 106, 198, 118, 112, 184, 172, 87,
//		2, 173, 117, 176, 229, 247, 253, 137, 185, 99, 164, 102, 147, 45, 66,
//		231, 52, 141, 211, 194, 206, 246, 238, 56, 110, 78, 248, 63, 240, 189,
//		93, 92, 51, 53, 183, 19, 171, 72, 50, 33, 104, 101, 69, 8, 252, 83, 120,
//		76, 135, 85, 54, 202, 125, 188, 213, 96, 235, 136, 208, 162, 129, 190,
//		132, 156, 38, 47, 1, 7, 254, 24, 4, 216, 131, 89, 21, 28, 133, 37, 153,
//		149, 80, 170, 68, 6, 169, 234, 151
//	};
//
//	size_t h;
//	size_t hash = 0;
//	size_t length = strlen(position);
//
//	for (size_t j = 0; j < HASH_BYTES; j++) {
//		h = T[(position[0] + j) % 256];
//		for (size_t i = length; i > 0;) {
//			h = T[h ^ position[--i]];
//		}
//		hash += h;
//	}
//
//	free(x_str);
//	free(y_str);
//	free(z_str);
//
//	return hash;
//}

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
