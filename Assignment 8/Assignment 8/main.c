//
//  main.c
//  Assignment 8
//
//  Created by Jackson Petty on 4/14/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "Graph.h"
#include "HashMap.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERR_SUCCESS	(0)	// No problemo
#define ERR_BAD_ARG	(1)	// Incorrect number of arguments
#define ERR_BAD_STR	(2)	// Zero-length string

int main(int argc, char * argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(ERR_BAD_ARG);
	} else if (strlen(argv[1]) == 0) {
		exit(ERR_BAD_STR);
	}
	
	Element ** hashset = createHashtable();
	Vertex * graph = buildGraph(argv[1], hashset);
	
	printGraph(graph);
	
	destroyHashtable(hashset);
	free(graph->connections);
	free(graph);
	
	return 0;
}
