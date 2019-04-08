#include <stdio.h>
#include <string.h>
#include <glib.h>

static void print_key_val(gpointer key, gpointer value, gpointer userdata) {
    printf("  '%s': %d\n", (char*) key, *((int*) value));
}

int main()
{
    int max_input = 120;
    GHashTable *dict = g_hash_table_new(g_str_hash, g_str_equal);

    char line_buffer[max_input];

    int *current_value;
    gpointer vptr;

    while ((fgets(line_buffer, max_input, stdin) != NULL)) {
        // fputs(line_buffer, stdout);

        char *word;
        char *string = line_buffer;

        if (strcmp(line_buffer, "OVER\n") == 0) {
            break;
        }

        // Note: I have the sneaking suspicion that the last word has an invisible \n.
        // Note2: Should strdup new words
        while( (word = strsep(&string," \n")) != NULL ) {

            if (word[0] == '\0') {
                puts("null");
                continue;
            } else if (word[0] == '\n') { // TODO: Merge back after debugging
                puts("endline");
                continue;
            } else if (g_hash_table_contains(dict, word)) {
                printf("incrementing '%s'", word);
                int *value_ptr = (int*) g_hash_table_lookup(dict, word);
                (*value_ptr)++;
                printf(": %d\n", *value_ptr);
            } else {
                printf("adding '%s'\n", word);
                gint* new_val = g_new(gint, 1);
                *new_val = 1;
                g_hash_table_insert(dict, strdup(word), new_val);
            }
        }
        puts("-- Done with line");
    }
    puts("-- Result");
    puts("{");
    g_hash_table_foreach(dict, print_key_val, NULL);
    puts("}");
}
