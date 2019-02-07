/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

1. It's supposed to create two arrays, one filled with 42 and one with ints
matching the index.
foo creates a pointer to an int array, but it makes it locally so it's bound
to fail. Shoulda used a stack

2. Wow got a warning about returning a local stack array.

3. It returned (foo bar main added for clarity):
`
foo
0x7ffee7372ad0

bar
0x7ffee7372ad0

main
0
48
-415814912
32766
-415815136
`
foo created a stack array, put some stuff in it, then destroyed it.
bar then also created an array, and used the same pointer foo used because
nothing happened in between. Then it wrote some stuff, and got destroyed. 
main then goes on to print the contents of the array foo returned, but there's
only garbage there.

4. got this
`
foo

bar

main
0
48
-331322624
32766
-331322848
`
for some reason, the values 0, 48, 32766 are unchanged, but the negative values 
are. The garbage seems to be more consistent than I expected. 
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    puts("\nfoo");
    int *array = foo();
    puts("\nbar");
    bar();
    puts("\nmain");
    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
