/**
 * @brief The code receives a letter and a word, it then goes through the word
 * and prints all suffixes that started with the letter provided.
 *
 * @return 0, prints results.
 *
 * @assumptions
 *  The input is a letter then a word of up to 127 characters.
 *  The input is valid.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "my_suffix.h"

/**
 * @brief Goes through the string str and searches for the letter c.
 *        When it finds c, it prints out the string from it forward.
 *
 * @param[in] char str[]    user's chosen word
 * @param[in] char c        user's chosen letter
 *
 * @return int suffix_amount - the number of suffixes found.
 */
int suffix(char str[], char c) {
    int i, j, suffix_amount = 0; /* counters */

    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] == c) {
            for (j = i; str[j] != '\0' ; ++j) {
                printf("%c", str[j]);
            }
        printf("\n");
            ++suffix_amount;
        }
    }

    return suffix_amount;
}


/**
 * @brief The function receives a letter and a word from the user,
 *        either by redirected file or from the terminal,
 *        and sends it to another function to extract all suffixes
 *
 * @return 0
 */
int main(void) {
    char word[128], letter, w;
    /* word and letter received from user, char temp holder*/
    int i = 0, suffix_amount; /* counters */

    if (isatty(fileno(stdin))) {
        /* Prompt user to write the required input */
        printf("Please enter a letter and a word: ");
    }
    /* Scan the letter */
    fscanf(stdin, "%c ", &letter);

    /* Scan until newline */
    while ((w = getchar()) != '\n') {
        word[i] = w;
        ++i;
    }
    word[i] = '\0';
    printf("The letter and word you entered are: "
           "%c and %s\n", letter, word);

    suffix_amount = suffix(word, letter);
    printf("The letter and word you entered were: %c and %s\n"
           "The number of suffixes found is: "
           "%d\n", letter, word, suffix_amount);

    return 0;
}