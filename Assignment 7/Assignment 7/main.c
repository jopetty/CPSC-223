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

int sum1(int x, int y) {
	return x + y + 1;
}

void printAggregates(Array * array) {
	size_t n = arraySize(array);
	
	for (size_t i = 0; i <= n; i++) {
		printf("%d ", arrayCombine(array, i));
	}
	printf("\n");
}

int main(int argc, const char * argv[]) {

	Array * array = arrayCreate(sum1, 20);
	
//	for (size_t i = 0; i < arraySize(array); i++) {
//		arraySet(array, i, i);
//	}
	
	arraySet(array, 5, 3);
	
	printArray(array); printf("\n");
	
	printAggregates(array);
	arrayDestroy(array);
	
	return 0;
}
