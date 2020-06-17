#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
    int* ptr;
    int n, sum = 0;

    //
    // #1 Allocate memory for 8 elements with malloc
    n = 8;
    printf("\n#1 Allocate memory for %d elements with malloc\n", n);

    ptr = (int*) malloc(n * sizeof(int));

    if(ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    } else {
        printf("Memory allocation successful\n");
    }

    // insert data into newly allocated memory
    for(int i = 0; i < n; i++) {
        ptr[i] = i*2;
    }

    printf("\nInserted elements into memory: \n");
    
    for(int i = 0; i < n; i++) {
        printf("Element %1d: %2d\n", i, ptr[i]);
    }

    // free the pointer
    free(ptr);
    printf("\nMemory deallocated\n");

    //
    // #2 Allocate memory for 8 elements with calloc
    n = 8;
    printf("\n#2 Allocate memory for 8 elements with calloc\n", n);

    ptr = (int*) calloc(n, sizeof(int));

    if(ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    } else {
        printf("Memory allocation successful\n");
    }

    // free the pointer
    free(ptr);
    printf("\nMemory deallocated\n");


    //
    // #3 Reallocate memory
    printf("\n#3 Reallocate memory\n");

    // allocate 8 bytes for start
    n = 8;
    ptr = (int*) malloc(n * sizeof(int));

    if(ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    } else {
        printf("Memory allocation successful\n");
    }

    // insert data into newly allocated memory
    for(int i = 0; i < n; i++) {
        ptr[i] = i*2;
    }

    printf("\nInserted elements into memory before reallocation: \n");
    
    for(int i = 0; i < n; i++) {
        printf("Element %1d: %2d\n", i, ptr[i]);
    }

    // reallocating memory
    printf("\nReallocating memory\n");

    n = 16;
    ptr = (int*) realloc(ptr, n * sizeof(int));

    for(int i = 0; i < n; i++) {
        printf("Element %1d: %2d\n", i, ptr[i]);
    }

    return 0;
}