/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

/////////////////////////////...
// NOTE: I have the latest macOS, so I couldn't check this against Valgrind.
/////////////////////////////...

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    int *never_allocated = malloc(sizeof (int)); // Fix to problem below: allocate it
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));
    int array1[100];
    int *array2 = malloc(100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    read_element(array1, -1);
    read_element(array1, 100);

    // but it does bounds-check dynamic arrays
    read_element(array2, -1); 
    read_element(array2, 100);
    // Fixes for these: use a language that does bounds checking.

    // and it catches use after free
    *use_after_free = 17; // Fix: consider using before free.
    free(use_after_free);
    // *use_after_free = 17;

    // never_free is definitely lost
    *never_free = 17;
    // Fix: don't lose it (and free it)
    free(never_free);

    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
    free_anything(never_allocated); // Fixed by allocating it.

    free(free_twice);
    // free(free_twice); // Don't free twice

    return 0;
}
