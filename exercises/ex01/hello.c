#include <stdio.h>

int main() {
    int a = 3;
    int b = 4;
    int c = a + b;
    printf("c is %d\n", c);
    if (c%2 == 0) {
        printf("c is even\n");
    } else {
        printf("c is odd\n");
    }
    // int x = 5;
    // // printf("Hello, World!\n");
    // int y = x + 1;
    // printf("%i\n", y);
    return 0;
}
 /*

 1. `	movl	$5, -8(%rbp)`
    Seems to allocate 5 to a variable

 2. A bunch of lines disappear, including the one about declaring X. I assume
    that since it isn't getting used, the compiler decides to ignore it. 

 3. No optimization adds
        `	movl	-8(%rbp), %esi`
    and changes the "Hello World" string literal at the bottom with %i.

    With optimization it ... removes a bunch of asm I don't understand. But it 
    does keep the x declaration (because x is needed!)

 4. Without optimization, seems to initialize y to 0, then add 1 to x and move
    it to y (roughly).
    With optimization, it simply initializes a variable as 6. Sweet.

Conclusion: The optimizer cuts out code that doesn't get used and simplifies
deterministic code paths.
 */ 