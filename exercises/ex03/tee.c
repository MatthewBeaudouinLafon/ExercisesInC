/* Written by Matthew Beaudouin-Lafon

Copy standard input to each FILE, and also to standard output.

    -a, --append
            append to the given FILEs, do not overwrite

    -p     diagnose errors writing to non pipes

    --output-error[=MODE]
            set behavior on write error.  See MODE below

    --help display this help and exit

    --version
            output version information and exit
*/

#include <stdio.h>
#include <unistd.h>

#define MAX_INPUT 120

int main(int argc, char* argv[]) {
    // Interpret flags
    char ch;
    while ((ch = getopt(argc, argv, "ai")) != EOF) {
        switch(ch) {
        case 'a':
            puts("Gonna append now ok?");
            break;
        case 'i':
            puts("I may or may not interrupt.");
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
    if (!(output = fopen(argv[0], "w"))) {
        fprintf(stderr, "Cannot open file.\n");
        return 1;
    }

    // Loop through input
    char* buffer[MAX_INPUT];
    while ((fgets(buffer, MAX_INPUT, stdin) != NULL)) {
        fputs(buffer, stdout);
        fputs(buffer, output);
    }
    
    // Write to file
        // fputs("Hello file!", output);
    // Write to stdout

    // Close file
    fclose(output);
}