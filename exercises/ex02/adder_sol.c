/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10
#define BUFFER_SIZE 20

// Error codes
#define SUCCESS 0
#define END_OF_FILE -1
#define BAD_INPUT -2

/* add_array: Adds up the elements of an array.
*
*  array: int pointer
*  n: number of elements in the array
*
*  returns: total
*/
int add_array(int array[], int n) {
    int i;
    int total = 0;

    for (i=0; i<n; i++) {
        total += array[i];
    }
    return total;
}

/* read_integer: Reads an integer from stdin.
*
*   returns: integer
*/
int read_integer(long* output) {
    char *res;
    char buffer[BUFFER_SIZE];

    // read a string
    res = fgets(buffer, sizeof(buffer), stdin);
    if (res == NULL) {
        return END_OF_FILE;
    }

    // check if the length of the string it too long
    if (strlen(buffer) >= BUFFER_SIZE) {
        return BAD_INPUT;
    }

    //printf("%s, %d\n", buffer, (int)strlen(buffer));

    // convert to integer
    // *output = atoi(buffer);
    char* end_num_ptr;
    *output = strtol(buffer, &end_num_ptr, 10);


    // check for invalid input.  Notice that atoi returns 0
    // for invalid input, so we can't allow the used to enter 0.
    if (*output == 0) {
        return BAD_INPUT;
    }
    *output = *output;
    return SUCCESS;
}

int main()
{
    int i;
    int res;
    int array[ARRAY_SIZE];

    for (i=0; i<ARRAY_SIZE; i++) {
        long number = 0;
        int res = read_integer(&number);
        //printf("%d\n", res);

        if (res == END_OF_FILE) {
            int total = add_array(array, i);
            printf("total %d\n", total);
            return 0;
        }

        if (res == BAD_INPUT) {
            printf("Invalid input.\n");
            return -1;
        }
        array[i] = number;
    }

    // if we get to the end of the loop, the user entered
    // too many numbers
    printf("Too many numbers.\n");
    return -1;
}
