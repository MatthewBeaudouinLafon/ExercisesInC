/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
    if (*list == NULL) {
        return -1;
    }
    Node *head = *list;
    int head_val = head->val;
    *list = head->next;
    free(head);
    return head_val;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
    Node *original_head = *list;
    Node *new_head = make_node(val, original_head);
    *list = new_head;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
    if (*list == NULL) {
        return 0;
    }

    Node *prev_node = NULL;
    Node *current_node = *list;

    while (current_node != NULL) {
        if (current_node->val == val) {
            if (prev_node == NULL) {
                // head has value
                pop(list);
            } else {
                // any other node has value
                prev_node->next = current_node->next;
                free(current_node);
            }
            return 1;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    return 0;
}


/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
    Node *prev_node = NULL;
    Node *current_node = *list;
    Node *next_node = NULL;

    if (*list == NULL) {
        return;
    }

    // Switch be pointer direction between current and previous node
    while (current_node != NULL) {
        next_node = current_node->next;

        current_node->next = prev_node;

        prev_node = current_node;
        current_node = next_node;
    }
    
    *list = prev_node;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    puts("\npop");
    int retval = pop(list);
    print_list(list);

    puts("\npush popped value + 10");
    push(list, retval+10);
    print_list(list);

    puts("\nremove 3");
    retval = remove_by_value(list, 3);
    print_list(list);
    printf("returned %i\n", retval);

    puts("\nremove 7");
    retval = remove_by_value(list, 7);
    print_list(list);
    printf("returned %i\n", retval);

    puts("\nreverse");
    reverse(list);
    print_list(list);
}
