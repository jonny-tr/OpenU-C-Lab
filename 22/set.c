/**
 * @brief all functions for the sets
 */

#include "set.h"

/**
 * @brief the function reads numbers from and stores them in the set
 * @param set1 pointer to the set to store the numbers in
 * @param input pointer to an array of numbers to store
 * @param size the size of the array
 * @return 0
 */
int read_set(set *set1, const int *input, int size) {
    int i = 0, bit, byte; /* counter, places */
    unsigned char mask; /* mask */
 
    /* Initializing set */
    memset(*set1, 0, sizeof(*set1));
    
    while (i < size) {
        byte = input[i] / 8;
        bit = input[i] % 8;
        mask = 1;
        mask <<= bit;
        (*set1)[byte] |= mask;
        ++i;    
    }
    
    return 0;
}


/**
 * @brief the function prints the set
 * @param set1 pointer to the set
 * @return 0
 */
int print_set(set *set1) {
    int i, j, k = 0, f = 0; /* counters */
    unsigned char mask = 1;

    for (i = 0; i < 16; ++i) {
        for (j = 0; j < 8; ++j) {
            if ((*set1)[i] & mask) {
                fprintf(stdout, "%u ", (i * 8) + j);
                f = 1;
                ++k;
                if (k == 16) {
                    fprintf(stdout, "\n");
                    k = 0;
                }
            }
            mask <<= 1;
            /* If mask is 0, reset it to 1 */
            mask = (mask == 0) ? 1 : mask;
        }
    }
    /* Checks if the set is empty */
    if (!f) return -1;
    if (k) fprintf(stdout, "\n");

    return 0;
}

/**
 * @brief the function stores the union of two sets in set3,
 * @param set1 first set
 * @param set2 second set
 * @param set3 pointer to the set to store the union
 * @return 0
 */
int union_set(const set set1, const set set2, set *set3) {
    unsigned int i; /* counter */

    for (i = 0; i < 16; ++i) {
        (*set3)[i] = (char) (set1[i] | set2[i]);
    }
    return 0;
}

/**
 * @brief the function stores the intersection of two sets in set3,
 * @param set1 first set
 * @param set2 second set
 * @param temp_set pointer to the set to store the intersection
 * @return 0
 */
int intersect_set(const set set1, const set set2, set *set3) {
    unsigned int i; /* counter */

    for (i = 0; i < 16; ++i) {
        (*set3)[i] = (char) (set1[i] && set2[i]);
    }
    return 0;
}

/**
 * @brief the function stores the difference of two sets in set3
 * @param set1 first set
 * @param set2 second set
 * @param set3 pointer to the set to store the difference
 * @return 0
 */
int sub_set(const set set1, const set set2, set *set3) {
    unsigned int i; /* counter */

    for (i = 0; i < 16; ++i) {
        (*set3)[i] = (char) (set1[i] & !set2[i]);
    }
    return 0;
}

/**
 * @brief the function stores the symmetric difference of two sets in set3
 * @param set1 first set
 * @param set2 second set
 * @param set3 pointer to the set to store the symmetric difference
 * @return 0
 */
int symdiff_set(const set set1, const set set2, set *set3) {
    unsigned int i; /* counter */

    for (i = 0; i < 16; ++i) {
        (*set3)[i] = (char) (set1[i] ^ set2[i]);
    }
    return 0;
}

/**
 * @brief the function stops the program
 * @return -1
 */
int stop(void) {
    exit(-1);
}
