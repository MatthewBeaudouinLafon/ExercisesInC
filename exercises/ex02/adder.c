#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int append_int(int value, int* array, int* last_index, int array_size);
void flush_buffer();

int main() {
    int scan_val;
    int buffer_flusher;

    int max_numbers = 25;
    int numbers_idx = 0;
    int numbers[max_numbers];

    int max_input = 10 + 1; // +1 to count EOL char
    int user_input[max_input];
    user_input[0] = '0';

    do {
        // Get input
        scan_val = scanf("%d", user_input);

        if (scan_val == EOF) {
            puts("EOF Detected");
            // TODO: have this as while condition rather than break
            break;
        } else if (scan_val < 1) {
            puts("Please enter an integer");
            flush_buffer();
            continue;
        } else if (numbers_idx < max_numbers) {
            // add to array
            int append_success = append_int(user_input[0], numbers, &numbers_idx, max_numbers);
            
            if (!append_success) {
                break;
            }
        } else {
            puts("Entered too many numbers, adding now.");
            break;
        }

    } while (1); 

    puts("Printing array");
    int sum = 0;
    for (int i=0; i < numbers_idx; i++) {
        // printf("%d\n", numbers[i]);
        sum += numbers[i];
    }

    printf("Total = %d\n", sum);

    // sum array
    return 0;
}

int append_int(int value, int* array, int* last_index, int array_size) {
    if (*last_index >= array_size) {
        puts("Index exceeds array size");
        return 0;
    } else {
        array[*last_index] = value;
        (*last_index)++;
        return 1;
    }
}

void flush_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}