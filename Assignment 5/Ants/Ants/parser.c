//
//  parser.c
//  Ants
//
//  Created by Jackson Petty on 3/3/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "parser.h"
#include "ant.h"

#include <stdlib.h>

#define ANT_FRM_SZE	(256) // Number of ants, one for each ASCII character
#define ERR_BAD_CHAR	(2) // Status if illegal character is found as ant identifier

/**
 Reads instructions from @c stdin and manipulates ants based on the commands
*/
void parseInput(void) {
	
	int c = 0; // Must be signed to check for EOF
	size_t count = 0;
	Universe * universe = createUniverse();
	Ant anthony = createAntWithCharacter(' ');
	
	Ant antfarm[ANT_FRM_SZE];
	for (int i = 0; i < ANT_FRM_SZE; i++) {
		antfarm[i] = createAntWithCharacter(i);
	}
	
	while ((c = getchar()) != EOF) {
		if (0 == count++) {
			if (c < ANT_FRM_SZE) {
				anthony = antfarm[c];
			} else {
				// We only declared ants for ASCII characters in the ant farm;
				// any index > 256 will be out of bounds for the array.
				fprintf(stderr, "Fatal Error: Encountered an illegal identifying character.\n");
				exit(ERR_BAD_CHAR);
			}
		} else {
			switch (c) {
				case 'h':
					anthony.position.x--;
					break;
				case 'j':
					anthony.position.y--;
					break;
				case 'k':
					anthony.position.y++;
					break;
				case 'l':
					anthony.position.x++;
					break;
				case '<':
					anthony.position.z++;
					break;
				case '>':
					anthony.position.z--;
					break;
				case '*':
					anthony.position.x *= 2;
					anthony.position.y *= 2;
					anthony.position.z *= 2;
					break;
				case '.':
					placeChar(anthony, universe);
					break;
				case '?':
					printf("%c", getCharAt(anthony.position, universe));
					break;
				case '\n':
					antfarm[anthony.character] = anthony;
					count = 0;
					break;
					
				default:
					break;
			}
		}
	}
	
	destroyUniverse(universe);
	
}
