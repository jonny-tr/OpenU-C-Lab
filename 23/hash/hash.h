#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define safe_free(p) if ((p) != NULL) { free(p); (p) = NULL; }

typedef struct node *ptr;
typedef struct node {
    char *filename;
    int occurrences;
    ptr next;
} node;

int list_manager(int argc, char **argv);
int file_parser(FILE *fd, ptr hash_table[29], char *filename);

#endif /* HASH_H */
