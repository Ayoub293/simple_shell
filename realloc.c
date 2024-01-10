#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initial size of the array
    int initial_size = 5;
    
    // Allocate memory for the array
    int *dynamic_array = (int *)malloc(initial_size * sizeof(int));
    if (dynamic_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the array with some values
    for (int i = 0; i < initial_size; i++) {
        dynamic_array[i] = i * 2;
    }

    // Display the initial array
    printf("Initial Array:\n");
    for (int i = 0; i < initial_size; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");

    // New size of the array
    int new_size = 8;

    // Resize the array using realloc
    int *resized_array = (int *)realloc(dynamic_array, new_size * sizeof(int));
    if (resized_array == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(dynamic_array);  // Free the original array before exiting
        return 1;
    }

    // Update the pointer to the resized array
    dynamic_array = resized_array;

    // Initialize the new elements in the resized array
    for (int i = initial_size; i < new_size; i++) {
        dynamic_array[i] = i * 3;
    }

    // Display the resized array
    printf("Resized Array:\n");
    for (int i = 0; i < new_size; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");

    // Free the dynamically allocated memory
    free(dynamic_array);

    return 0;
}
