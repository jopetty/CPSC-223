//
//  parser.c
//  Ants
//
//  Created by Jackson Petty on 3/3/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "parser.h"

#include "ant.h"

// MARK: - Methods

/**
 Reads instructions from @p stdin and manipulates ants based on the commands
*/
void parse_input(void) {
	
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
			
			if ('h' == c) { anthony.x--; }
			else if ('j' == c) { anthony.y--; }
			else if ('k' == c) { anthony.y++; }
			else if ('l' == c) { anthony.x++; }
			else if ('<' == c) { anthony.z++; }
			else if ('>' == c) { anthony.z--; }
			else if ('*' == c) {
				anthony.x *= 2;
				anthony.y *= 2;
				anthony.z *= 2;
			} else if ('.' == c) {
				placeAntAt(anthony, universe);
			} else if ('?' == c) {
				printf("%c", getCharAt(anthony, universe));
			} else if ('\n' == c) {
				antfarm[anthony.character] = anthony;
				count = 0;
			}
		}
	}
	
	destroyUniverse(universe);
	
}
