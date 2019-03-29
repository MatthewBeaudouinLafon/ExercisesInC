/* Example code for Exercises in C.

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// VALUE: represents a value in a key-value pair

/* Here's one way of making a polymorphic object in C */

typedef struct {
    enum Type {INT, STRING} type;
    union {
        int i;
        char *s;
    };
} Value;


/* Makes a Value object that contains an int.
*
* i: value to store.
*
* returns: pointer to a new Value
*/
Value *make_int_value(int i)
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = INT;
    value->i = i;
    return value;
}


/* Makes a Value object that contains a string.
*
* s: value to store.
*
* returns: pointer to a new Value
*/
Value *make_string_value(char *s)
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = STRING;
    value->s = s;
    return value;
}


void free_value(Value *val) {
    free(val);
}


/* Prints a value object.
*
* value: pointer to Value
*
*/
void print_value (Value *value)
{
    if (value == NULL) {
        printf ("%p\n", value);
        return;
    }
    switch (value->type) {
        case INT:
        printf ("%d\n", value->i);
        break;
        case STRING:
        printf ("%s\n", value->s);
        break;
    }
}

// HASHABLE: Represents a key in a key-value pair.

/* Here's another way to make a polymorphic object.

The key can be any pointer type.  It's stored as a (void *), so
when you extract it, you have to cast it back to whatever it is.

`hash` is a pointer to a function that knows how to hash the key.
`equal` is a pointer to a function that knows how to compare keys.

*/

typedef struct {
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
} Hashable;


/* Makes a Hashable object.
*
* key: pointer to anything
* hash: function that can hash keys
* equal: function that compares keys
*
* returns: pointer to Hashable
*
*/
Hashable *make_hashable(void *key,
    int (*hash) (void *),
    int (*equal) (void *, void *))
{
    Hashable *hashable = (Hashable *) malloc (sizeof (Hashable));
    hashable->key = key;
    hashable->hash = hash;
    hashable->equal = equal;
    return hashable;
}


void free_hashable(Hashable* hashable) {
    free(hashable);
}


/* Prints a Hashable object.
*
* hashable: pointer to hashable
*/
void print_hashable(Hashable *hashable)
{
    printf ("key %p\n", hashable->key);
    printf ("hash %p\n", hashable->hash);
}


/* Hashes an integer.
*
* p: pointer to integer
*
* returns: integer hash value
*/
int hash_int(void *p)
{
    return *(int *)p;
}


/* Hashes a string.
*
* p: pointer to first char of a string
*
* returns: integer hash value
*/
int hash_string(void *p)
{
    char *s = (char *) p;
    int total = 0;
    int i = 0;

    while (s[i] != 0) {
        total += s[i];
        i++;
    }
    return total;
}


/* Hashes any Hashable.
*
* hashable: Hashable object
*
* returns: int hash value
*/
int hash_hashable(Hashable *hashable)
{
    return hashable->hash (hashable->key);
}


/* Compares integers.
*
* ip: pointer to int
* jp: pointer to int
*
* returns: 1 if equal, 0 otherwise
*/
int equal_int (void *ip, void *jp)
{
    // FILL THIS IN!
    return *((int*) ip) == *((int*) jp);
}


/* Compares strings.
*
* s1: pointer to first char of a string
* s2: pointer to first char of a string
*
* returns: 1 if equal, 0 otherwise
*/
int equal_string (void *s1, void *s2)
{
    // FILL THIS IN!
    int res = strcmp((char*) s1, (char*) s2);
    if (res == 0) {
        return 1;
    } else {
        return 0;
    }
}


/* Compares Hashables.
*
* h1: Hashable
* h2: Hashable of the same type
*
* returns: 1 if equal, 0 otherwise
*
*/
int equal_hashable(Hashable *h1, Hashable *h2)
{
    return h1->equal(h1->key, h2->key);
}


/* Makes a Hashable int.
*
* Allocates space and copies the int.
*
* x: integer to store
*
* returns: Hashable
*/
Hashable *make_hashable_int (int x)
{
    int *p = (int *) malloc (sizeof (int));
    *p = x;
    return make_hashable((void *) p, hash_int, equal_int);
}


/* Makes a Hashable int.
*
* Stores a reference to the string (not a copy).
*
* s: string to store
*
* returns: Hashable
*/
Hashable *make_hashable_string (char *s)
{
    return make_hashable((void *) s, hash_string, equal_string);
}


// NODE: a node in a list of key-value pairs

typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;


/* Makes a Node. */
Node *make_node(Hashable *key, Value *value, Node *next)
{
    Node *node = (Node *) malloc (sizeof (Node));
    node->key = key;
    node->value = value;
    node->next = next;
    return node;
}


/* Prints a Node. */
void print_node(Node *node)
{
    if (node == NULL) {
        puts("null node");
        return;
    }
    puts("  print_node");
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    printf ("next %p\n", node->next);
}


/* Prints all the Nodes in a list. */
void print_list(Node *node)
{
    // puts("  print_list");
    if (node == NULL) {
        puts("end node\n");
        return;
    }
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    puts("-----");
    print_list(node->next);
}


/* Prepends a new key-value pair onto a list.

This is actually a synonym for make_node.

Note: It really feels like this function should change the list in place.
Note 2: The more I think about it, the less I like this api. 
    It's like appending on an array by calling list[-1].append()
    (but I don't care quite enough to refactor it)
    ((though I would if this weren't a homework))
*/
Node *prepend(Hashable *key, Value *value, Node *rest)
{
    return make_node(key, value, rest);
}


/* Looks up a key and returns the corresponding value, or NULL */
Value *list_lookup(Node *list, Hashable *key)
{
    // FILL THIS IN!
    Node *node = list; 
    while (node != NULL) {
        if (key->equal(key, node->key)) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void free_list(Node *node) {
    if (node == NULL) {
        return;
    }
    Node *next_node;
    next_node = node->next;

    //// Not up to the node to free its contents (as I learned the hard way)
    // free_hashable(node->key);
    // free_value(node->value);

    free(node);

    free_list(next_node);
}


// MAP: a map is an array of lists of key-value pairs

typedef struct map {
    int size_limit;
    int size;
    Node **lists;
} Map;


/* Makes a Map with n lists. */
Map *make_map(int size_limit)
{
    int i;

    Map *map = (Map *) malloc (sizeof (Map));
    map->size = 0;
    map->size_limit = size_limit;
    map->lists = (Node **) malloc (sizeof (Node *) * size_limit);

    for (i = 0; i < size_limit; i++) {
        map->lists[i] = NULL;
    }
    return map;
}


/* Prints a Map. */
void print_map(Map *map)
{
    printf("map of size %i and max_size %i\n", map->size, map->size_limit);
    int i;
    for (i=0; i<map->size_limit; i++) {
        if (map->lists[i] == NULL) {
            printf ("list #%d\n", i);
            puts("empty list\n");
        } else {
            // puts("  a list");
            printf ("list #%d\n", i);
            print_list (map->lists[i]);
        }
    }
}


void free_map(Map *map)
{
    int i;
    for (i = 0; i < map->size_limit; i++) {
        free_list(map->lists[i]);
    }

    free(map->lists);
    free(map);
}


/* Adds a key-value pair to a map. */
void map_add(Map **map_ptr, Hashable *key, Value *value)
{
    // FILL THIS IN!
    Map *map = *map_ptr;
    if (map->size == map->size_limit) {
        Map *new_map = make_map(map->size_limit * 2);
        // Copy all items over
        int i;
        for (i = 0; i < map->size_limit; i++) { // for all items in map
            Node *node = map->lists[i];
            while (node != NULL) {
                // print_hashable(key);
                // print_value(value);
                // puts("");
                // print_map(new_map);
                // puts("good?");
                map_add(&new_map, node->key, node->value);

                node = node->next;
            }
        }

        free_map(map);
        *map_ptr = new_map;
        map = new_map;
        // puts("added");
        // find a way to change map in place? return map?
    }

    int index = hash_hashable(key) % map->size_limit;
    // printf("index computed: %i\n", index);

    Node *head = map->lists[index];

    // printf("not yet added:");
    // print_node(head);

    // puts("---prepend---");
    // puts("--key--");
    // print_hashable(key);
    // puts("-value-");
    // print_value(value);
    // puts("-list-");
    // printf("head pointer %p\n", head);
    // print_list(head);
    // puts("---end prepend---");
    head = prepend(key, value, head);

    map->lists[index] = head;
    map->size += 1;

    // printf("just added node:");
    // print_node(head);
}


/* Looks up a key and returns the corresponding value, or NULL. */
Value *map_lookup(Map *map, Hashable *key)
{
    // FILL THIS IN!
    Node *list = map->lists[hash_hashable(key) % map->size_limit];
    return list_lookup(list, key);
}


/* Prints the results of a test lookup. */
void print_lookup(Value *value)
{
    printf ("Lookup returned ");
    print_value (value);
    printf ("\n");
}


int main ()
{
    // 1       -> 17
    // "apple" -> "Orange"
    // 2       ->
    // 13       -> 42

    Hashable *hashable1 = make_hashable_int (1);
    Hashable *hashable2 = make_hashable_string ("Apple");
    Hashable *hashable3 = make_hashable_int (2);
    Hashable *hashable4 = make_hashable_int (13);

    Value *value1 = make_int_value (17);
    Value *value2 = make_string_value ("Orange");
    Value *value3 = make_int_value (42);

    // make a list by hand
    puts("\n--- Make a node");
    Node *node1 = make_node(hashable1, value1, NULL);
    print_node (node1);

    puts("\n--- Make and print list");
    Node *list = prepend(hashable2, value2, node1);
    print_list (list);

    // run some test lookups
    puts("\n--- Should find 17");
    Value *value = list_lookup (list, hashable1);
    print_lookup(value);

    puts("\n--- Should find 'Orange'");
    value = list_lookup (list, hashable2);
    print_lookup(value);

    puts("\n--- Shouldn't find anything");
    value = list_lookup (list, hashable3);
    print_lookup(value);

    // make a map
    Map *map = make_map(2);
    puts("\n--- map with no items");
    print_map(map);

    map_add(&map, hashable1, value1);
    puts("\n--- map with 1 item");
    print_map(map);

    map_add(&map, hashable2, value2);

    // printf ("\nMap\n");
    puts("\n--- map with 2 items");
    print_map(map);

    // NOTE: looks like adding kv isn't working
    // run some test lookups
    puts("\n--- Should find 17");
    value = map_lookup(map, hashable1);
    print_lookup(value);

    puts("\n--- Should find 'Orange'");
    value = map_lookup(map, hashable2);
    print_lookup(value);

    puts("\n--- Shouldn't find anything");
    value = map_lookup(map, hashable3);
    print_lookup(value);


    // Testing resize
    puts("\n--- add value, should resize");
    map_add(&map, hashable3, value3);
    print_map(map);

    puts("\n--- Should find 17");
    value = map_lookup(map, hashable1);
    print_lookup(value);

    puts("\n--- Should find 'Orange'");
    value = map_lookup(map, hashable2);
    print_lookup(value);

    puts("\n--- Should find 42");
    value = map_lookup(map, hashable3);
    print_lookup(value);

    puts("\n--- Shouldn't find anything");
    value = map_lookup(map, hashable4);
    print_lookup(value);

    return 0;
}
