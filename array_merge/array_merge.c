#include "array_merge.h"

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
	int unique[] = sum(num_arrays, sizes);
	unique = (int*) calloc(num_arrays, sizeof(int));
	int counter = 0;
	for (int i = 0; i < num_arrays; i++){
		for(int j = 0; j < sizes[i]; j++) {
			if(contains(values[i], values[i][j], sizes[i]) == 0) {
				unique[counter] = values[i][j];
				counter++;	
			}
		}
	}	
  	return sizes;
}
