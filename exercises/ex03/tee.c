/* Written by Matthew Beaudouin-Lafon
Easy test: gcc tee.c -o T && cat sample.txt | ./T target.txt

Copy standard input to each FILE, and also to standard output.

    -a, --append
            append to the given FILEs, do not overwrite

    -i, --ignore-interrupts
            ignore interrupts
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MAX_INPUT 120

int main(int argc, char* argv[]) {
    // Interpret flags
    char write_mode = 'w';

    char ch;
    while ((ch = getopt(argc, argv, "ai")) != EOF) {
        switch(ch) {
        case 'a':
            write_mode = 'a';
            break;
        case 'i':
            signal(SIGINT, SIG_IGN);
            break;
        }
    }
    argc -= optind;
    argv += optind;

    if (argc < 1) {
        fprintf(stderr, "Must provide an input.\n");
    } else if (argc > 1) {
        fprintf(stderr, "Provided too many inputs.\n");
    }

    // Open File
    FILE* output;
    if (!(output = fopen(argv[0], &write_mode))) {
        fprintf(stderr, "Cannot open file.\n");
        return 1;
    }

    // Loop through input
    char buffer[MAX_INPUT];
    while ((fgets(buffer, MAX_INPUT, stdin) != NULL)) {
        fputs(buffer, stdout);
        fputs(buffer, output);
    }

    fputs("\n", stdout); // End cleanly
    fclose(output);
    return 0;
}

/* Reflection
3. The main slowdown was figuring out the proper way to read input line by line.
Lots of people have different solutions that do slightly different things. 
Otherwise it was a pretty smooth implementation process. Head First C definitely
helped a lot with the flag handling.


*/