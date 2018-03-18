//
//  parser.c
//  Ants
//
//  Created by Jackson Petty on 3/3/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "parser.h"
#include "ant.h"

/**
 Reads instructions from @p stdin and manipulates ants based on the commands
*/
void parseInput(void) {
	
	int c = 0;
	size_t count = 0;
	Universe * universe = createUniverse();
	Ant anthony = createAntWithCharacter(' ');
	
	Ant antfarm[256];
	for (int i = 0; i < 256; i++) {
		antfarm[i] = createAntWithCharacter(i);
	}
	
	while ((c = getchar()) != EOF) {
		if (0 == count++) {
			anthony = antfarm[c];
		} else {
			if ('h' == c) { anthony.position.x--; }
			else if ('j' == c) { anthony.position.y--; }
			else if ('k' == c) { anthony.position.y++; }
			else if ('l' == c) { anthony.position.x++; }
			else if ('<' == c) { anthony.position.z++; }
			else if ('>' == c) { anthony.position.z--; }
			else if ('*' == c) {
				anthony.position.x *= 2;
				anthony.position.y *= 2;
				anthony.position.z *= 2;
			} else if ('.' == c) {
				placeChar(anthony, universe);
			} else if ('?' == c) {
				printf("%c", getCharAt(anthony.position, universe));
			} else if ('\n' == c) {
				antfarm[anthony.character] = anthony;
				count = 0;
			}
		}
	}
	
	destroyUniverse(universe);
	
}
