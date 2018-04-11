//
//  main.c
//  Assignment 7
//
//  Created by Jackson Petty on 4/6/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "array.h"

#include <stdio.h>

int sum(int x, int y) {
	return x+y;
}

int main(int argc, const char * argv[]) {

	Array * array = arrayCreate(sum, 100);
	
	for (size_t i = 0; i < arraySize(array); i++) {
		arraySet(array, i, i);
	}
	
	printArray(array);
	
	arrayDestroy(array);
	
	return 0;
}
