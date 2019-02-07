/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *p2 = malloc(128);
    char *s = "Hello, World";

    void *r1 = malloc(13);
    void *r2 = malloc(13); // diff between addresses 0x10

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("p2 points to %p\n", p2);
    printf ("s points to %p\n", s);

    printf ("r1 points to %p\n", r1);
    printf ("r2 points to %p\n", r2);


    return 0;
}
