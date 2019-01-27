/*
Program to keep the count at a Blackjack table.
*/

#include <stdio.h>
#include <stdlib.h>

void prompt_user(char* card_name);
int get_card_value(char* card_name);
int update_count(int count, int card_val);

int main()
{
    char card_name[3];
    int count = 0;
    int val;
    do {
        prompt_user(card_name);
        val = get_card_value(card_name);
        if (val < 0) {
            continue;
        }

        count = update_count(count, val);
        printf("Currently count: %i\n", count);
    } while (card_name[0] != 'X');

    return 0;
}

/*  Prompt user for input. 
    Only uses 2 char buffer. Input should be a number between 2 and
    10 (inclusive), or J, Q, K.

    card_name: buffer to store result
*/
void prompt_user(char* card_name) {
    puts("enter the card_name: ");
    scanf("%2s", card_name);
}

/*  Convert card value to blackjack value.

    card_name: user input buffer
    Return: int between 1 and 10
            -1 for unusable value (invalid or 'X').
*/
int get_card_value(char* card_name) {
    int val = 0;
    switch(card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A':
            val = 11;
            break;
        case 'X':
            val = -1;
            break;
        default:
            val = atoi(card_name);
            if ((val < 1) || (val > 10)) {
                puts("I don't understand that value!");
                val = -1;
            }
    }
    return val;
}

/*  Update count based on card value
    
    count: current blackjack count
    card_val: value of new card

    return: count after new card
*/
int update_count(int count, const int card_val) {
    if ((card_val > 2) && (card_val < 7)) {
        count ++;
    } else if (card_val == 10 || card_val == 11) {
        count--;
    }
    return count;
}
