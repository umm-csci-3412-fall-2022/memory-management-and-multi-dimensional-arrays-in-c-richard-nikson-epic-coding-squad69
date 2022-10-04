#include <stdio.h>
#include "mergesort.h"

int main(){
	int array[6] = {2, 5, 3, 1, 8, 7};
	mergesort(6, array);
	for (int i = 0; i < 6; i++){
	printf("%d ", array[i]);
	}
	return 0;
}
