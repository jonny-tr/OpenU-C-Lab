#ifndef SET_H
#define SET_H

#define _POSIX_C_SOURCE 200809L /* for isatty() */
#define allocation_failure \
            fprintf(stderr, "Memory allocation failed\n");\
            stop();

#define safe_free(p) if ((p) != NULL) { free(p); (p) = NULL; }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

typedef char set[16];

/* Parsing functions */
int input_reader(set **);
char *read_next_part(const char user_command[], unsigned int *position);
int command_verifier(char user_command[], unsigned int *position);
int set_verifier(char user_command[], unsigned int *position);
unsigned int comma_checker(const char user_command[], unsigned int *position);
int read_parser(const char user_command[], unsigned int *position, set *set1);

/* Set functions */
int read_set(set *set1, const int *input, int size);
int print_set(set *set1);
int union_set(const set set1, const set set2, set *set3);
int intersect_set(const set set1, const set set2, set *set3);
int sub_set(const set set1, const set set2, set *set3);
int symdiff_set(const set set1, const set set2, set *set3);
int stop(void);

#endif /* SET_H */
