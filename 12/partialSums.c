/**
 * @brief       This code is aimed to receive an array of natural numbers
 *              and return a new array of their partial sums.
 *
 * @return      0, prints results.
 *
 * @assumptions The input is an array of  natural numbers, and array's size.
 *              The input is valid.
 */

#define _POSIX_C_SOURCE 200809L /* defined for isatty() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "partialSums.h"


/**
 * @brief       The function receives an array and its size
 *              and returns an array built from its partial sums.
 *
 * @param[in]   int amount      amount of numbers in the array
 * @param[in]   int *array      pointer to array of numbers to calculate
 *
 * @return      int *sum_array
 */
int *partialSums(int amount, int *array) {
    int i, sum = 0; /* i - counter, sum - current sum */
    int *sum_array = (int *) malloc(amount * sizeof(int));
        /* sum_array - new results array */

    if (sum_array == NULL) {
        exit(EXIT_FAILURE); /* Exit if not enough memory */
    };

    for (i = 0; i < amount; ++i) {
        sum += array[i];
        sum_array[i] = sum;
    }

    return sum_array;
}


/**
 * @brief       The function receives the size of an array and its content,
 *              and calls another function to partially sum it
 *
 * @return      0
 */
int main(void) {
    int size, i; /* array's size and a counter */
    int *user_nums = NULL, *calculated_nums = NULL;
        /* the original array and the result array */

    if (isatty(fileno(stdin))) {
        /* Prompt user to insert input */
        fprintf(stdout, "Please enter the user_nums's size: ");
    }
    fscanf(stdin, "%d", &size);
    user_nums = (int *) malloc(size * sizeof(int)); /* Allocating memory */

    if (user_nums == NULL) {
        exit(EXIT_FAILURE); /* Exit if not enough memory */
    };

    if (isatty(fileno(stdin))) {
        /* If the input is from the terminal, prompt user to insert numbers */
        fprintf(stdout, "Please enter %d integers: ", size);
    }

    for (i = 0; i < size; i++) {
        fscanf(stdin, "%d", &user_nums[i]);
    }

    fprintf(stdout, "The numbers you entered are: \n");
    for (i = 0; i < size; ++i) {
        fprintf(stdout, "%d ", user_nums[i]);
    }

    /* Send the user_nums to partialSums and print result */
    calculated_nums = partialSums(size, user_nums);
    printf("\nThe result is: \n");
    for (i = 0; i < size; ++i) {
        printf("%d ", calculated_nums[i]);
    }
    printf("\n");

    /* Free allocated memory */
    free(user_nums);
    free(calculated_nums);
    return 0;
}