//
//  ant.h
//  Ants
//
//  Created by Jackson Petty on 3/3/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#ifndef ant_h
#define ant_h

#include <stdio.h>

// MARK: - Properties

/**
 Ant ant in the game. Each ant has a character and a position in 3D Cartesian space.
 @p character can be any valid ASCII character. @p x, @p y, @p z must be in the
 range 0 to 2^32 - 1.
 */
typedef struct ant {
	int character;
	unsigned int x;
	unsigned int y;
	unsigned int z;
} Ant;

/**
 A hash table to store the 2^32 possible positions.
*/
typedef struct universe Universe;

/**
 A list of all 256 possible ants and their last positions.
*/
typedef struct antfarm AntFarm;

// MARK: - Methods

/**
 Creates a new ant at a default starting position with the given character.
 
 @param c	An ASCII character (0--255).
 
 @return An Ant with character @p c at position (0,0,0).
*/
Ant createAntWithCharacter(int c);

/**
 Initializes a blank 2^32 × 2^32 × 2^32 universe. Positions are reduced to a 1-D array
 using a hash map.
 
 @return An array whose entries are linked lists of positions/characters
*/
Universe * createUniverse(void);
void destroyUniverse(Universe * universe);

int getCharAt(Ant ant, Universe * universe);
void placeAntAt(Ant ant, Universe * universe);

#endif /* ant_h */
