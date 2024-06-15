/**
 * @brief The code receives two decimal numbers, adds them bitwise,
 *        and present the result in decimal.
 *
 * @return 0, prints results.
 *
 * @assumptions The input is two natural numbers, up to 6 digits each.
 *              The input is valid.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include "my_add.h"


/**
 * @brief Prints the decimal number in binary.
 *        Every print is the width of sizeof(unsigned int) * 8.
 *
 * @param[in] unsigned int dec_num      a decimal number
 *
 * @return 0
 */
int print_binary(unsigned int dec_num) {
    int i; /* counter */

    for (i = sizeof(unsigned int) * 8 - 1; i >= 0; --i) {
        putc((dec_num & (1 << i)) ? '1' : '0', stdout);
    }

    return 0;
}


/**
 * @brief The function adds two numbers, bit by bit.
 *
 * @param[in] unsigned int a        user's chosen number
 * @param[in] unsigned int b        user's chosen number
 *
 * @return unsigned int sum
 */
unsigned int my_add(unsigned int a, unsigned int b) {
    unsigned int a_bit, b_bit, carry = 0, i, sum = 0, current_sum, mask = 1;
        /* relevant bits for calculation, carry, counter,
         * result and interim result, bitmask */

    /* Printing the numbers in binary */
    printf("The first number in binary is: ");
    print_binary(a);
    printf("\n");
    printf("The second number in binary is: ");
    print_binary(b);
    printf("\n");

    /* Adding the two numbers, bit by bit */
    for (i =0; i < sizeof(unsigned int) * 8; ++i) {
        /* Choosing the relevant bit using the mask */
        a_bit = a & mask;
        b_bit = b & mask;
        
        current_sum = a_bit ^ b_bit ^ carry;
        sum |= current_sum;
        carry = (a_bit & b_bit) | (carry & (a_bit ^ b_bit));

        /* Shifting the carry and the mask to the next bit */
        carry <<= 1;
        mask <<= 1;
    }

     /* Printing the result in binary */
    printf("The result in binary is: ");
    print_binary(sum);
    printf("\n");

    return sum;
}


/**
 * @brief The function receives two decimal numbers from the user,
 *        and calls other function to sum and print them in binary
 *        at the end it prints them and the result
 *
 * @return 0
 */
int main() {
    unsigned int num1 = 0, num2 = 0, sum; /* user input and the result */

    if (isatty(fileno(stdin))) {
        /* Prompt user to write required input */
        printf("Please enter two numbers: ");
    }

    fscanf(stdin, "%u %u", &num1, &num2);
    printf("The numbers you entered are: %u and %u\n", num1, num2);

    /* Send the numbers to my_add, expects an unsigned int in return */
    sum = my_add(num1, num2);

    printf("The numbers you entered were: %u and %u\n", num1, num2);
    printf("The sum of these numbers is: %u\n", sum);
    
    return 0;
}