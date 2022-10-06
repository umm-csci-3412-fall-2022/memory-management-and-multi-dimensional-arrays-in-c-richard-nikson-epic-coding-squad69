#include "array_merge.h"
#include <stdlib.h>
#include "../mergesort/mergesort.c"

int contains(int* array, int value, int size){
	for (int i = 0; i < size; i++){
		if (array[i] == value){
			return 1;
		}
	}
	return 0;
}

int sum(int num_arrays, int* sizes) {
	int total = 0;
	for (int i = 0; i < num_arrays; i++) {
		total += sizes[i];
	}
	return total;
}

int* array_merge(int num_arrays, int* sizes, int** values) {
	const int max_size = sum(num_arrays, sizes);
	int* unique;
	unique = (int*) calloc(max_size, sizeof(int));
	int counter = 0;
	for (int i = 0; i < num_arrays; i++){
		for(int j = 0; j < sizes[i]; j++) {
			if(contains(unique, values[i][j], max_size) == 0) {
				unique[counter] = values[i][j];
				counter++;	
			}
		}
	}
	mergesort(counter, unique);
	int* output;
	output = (int*) calloc(counter+1, sizeof(int));
	output[0] = counter;
	for (int i = 1; i <= counter ; i++){
		output[i] = unique[i-1];
	}
	free(unique);
  	return output;
}
