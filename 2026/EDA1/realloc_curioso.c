#include <stdio.h>
#include <stdlib.h>

int main() {
	int *arr = malloc(3 * sizeof(int));
	
	for (int i = 0; i < 3; i++) {
		arr[i] = i + 1;
	}
	
	// Guardo un puntero a una posición cualquiera del vector.
	int *ptr = &arr[1];
	
	printf("Antes de realloc:\n");
	printf("arr: %p\n", arr);
	printf("ptr: %p\n", ptr);
	printf("valor ptr: %d\n", *ptr);
	
	// Agrandamos el array (no se algun valor grande...)
	arr = realloc(arr, 1000 * sizeof(int));
	
	printf("\nDespues de realloc:\n");
	printf("arr: %p\n", arr);
	printf("ptr: %p\n", ptr);  // Donde apunta?
	
	printf("valor ptr: %d\n", *ptr);  // EPA!
	
	//free(arr);
	
	return 0;
}
