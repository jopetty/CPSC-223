//
//  main.c
//  Ants
//
//  Created by Jackson Petty on 3/3/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char * argv[]) {
	
	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	parseInput();
	
	return EXIT_SUCCESS;
}
