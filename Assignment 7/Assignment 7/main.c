//
//  main.c
//  Assignment 7
//
//  Created by Jackson Petty on 4/6/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "array.h"
#include "rope.h"

#include <stdio.h>

int sum(int x, int y) {
	return x+y;
}

int sum1(int x, int y) {
	return x + y + 1;
}

int main(int argc, const char * argv[]) {

	Array * array = arrayCreate(sum1, 6);
	
	printf("\n\n\n");
	
//	arraySet(array, 5, 3);
//	arraySet(array, 0, 8);
////	arraySet(array, 100, 3);
//	arraySet(array, 20, 8);
	printArray(array);
	
	printf("Size:\t%zu\n", arraySize(array));
	printf("Combine: %d\n", arrayCombine(array, 2));
	
	return 0;
}
