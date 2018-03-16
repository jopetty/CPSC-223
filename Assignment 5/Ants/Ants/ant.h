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
 Creates a new, empty universe of NULL Tile pointers.
 In the context of the application, the universe should
 be a singleton.
 
 @return A pointer to the new universe.
 */
Universe * createUniverse(void);

/**
 Frees all dynamically allocated memory in the universe;
 Frees all tiles and then the universe wrapper itself.
 
 @param universe	The singleton universe.
 */
void destroyUniverse(Universe * universe);

/**
 Retrieves the character placed at a given position, or
 a space (' ') if no character was placed there.
 
 @param ant	The ant located at the requested position.
 @param universe	The singleton universe.
 
 @return The character located at the ant's position, or
 a space if no character has been placed.
 */
int getCharAt(Ant ant, Universe * universe);

/**
 Places the ant's character at the ants current location.
 If the location as been marked before, the character at
 that position is simply changed to the current character;
 otherwise, a new Tile is constructed and placed at the
 end of the linked list for that particular hash value.
 
 @param ant	The ant in question.
 @param universe	The singleton universe.
 */
void placeAntAt(Ant ant, Universe * universe);

#endif /* ant_h */
