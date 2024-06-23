#include "hash.h"

/**
 * @brief Manages the list of files and their occurrences.
 *
 * This function manages the list of files and their occurrences.
 * It reads the files, parses them, and populates the hash table with nodes.
 * It then prints the occurrences of each integer in the files.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @return 0 if the list was successfully managed, and 1 if an error occurred.
 */
int list_manager(int argc, char **argv) {
    int i; /* Counter */
    FILE *fd; /* File pointer */
    ptr hash_table[29] = {0}; /* Hash table */
    ptr temp; /* Temporary node */

    /* Loop files and parse */
    for (i = 1; i < argc; ++i) {
        fd = fopen(argv[i], "r");
        if (fd == NULL) {
            fprintf(stderr, "Error: Unable to open file %s\n", argv[i]);
            return 1;
        }

        /* Send to parsing */
        if (file_parser(fd, hash_table, argv[i]) == 1) {
            fclose(fd);
            return 1;
        }
        fclose(fd);
    }

    /* Print the hash table */
    for (i = 0; i < 29; ++i) {
        temp = hash_table[i];
        if (temp == NULL) continue;
        fprintf(stdout, "%d appears in ", i);

        while (temp != NULL) {
            fprintf(stdout, "file %s - ", temp->filename);
            fprintf(stdout, "%d times", temp->occurrences);
            temp = temp->next;
            if (temp != NULL) fprintf(stdout, ", ");
        }
        fprintf(stdout, "\n");
    }

    /* Free the hash table memory */
    for (i = 0; i < 29; ++i) {
        temp = hash_table[i];
        while (temp != NULL) {
            ptr next = temp->next;
            safe_free(temp)
            temp = next;
        }
    }

    return 0;
}


/**
 * @brief Parses the file and populates the hash table with nodes.
 *
 * This function reads integers from the given file,
 * creates a new node for each integer, and adds it to the hash table.
 *
 * @param fd The file pointer to the file to be parsed.
 * @param hash_table The hash table to be populated with nodes.
 * @param filename The name of the file being parsed.
 * @return 0 if the file was successfully parsed, and 1 if an error occurred.
 */
int file_parser(FILE *fd, ptr hash_table[29], char *filename) {
    int c; /* Character */
    ptr prev = NULL, n; /* Previous node */

    /* Run until EOF */
    while ((fscanf(fd, "%d ", &c)) != EOF) {
        /* For existing numbers */
        if (hash_table[c] != NULL) {
            n = hash_table[c];
            while (n != NULL) {
                if (strcmp(n->filename, filename) == 0) {
                    n->occurrences++;
                    break;
                }
                prev = n;
                n = n->next;
            }
            if (n != NULL) continue;
        }

        /* Create a new node */
        n = (ptr)calloc(1, sizeof(node));
        if (n == NULL) {
            fprintf(stderr, "Error: Unable to allocate memory\n");
            return 1;
        }

        /* Set data */
        n->filename = filename;
        n->occurrences++;
        n->next = NULL;

        if (hash_table[c] == NULL) {
            hash_table[c] = n;
        }
        else {
            prev->next = n;
        }
        prev = n;
    }

    return 0;
}

/**
 * @brief Checks if any files were passed as arguments and calls list_manager.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @return 0 if the program ran successfully, and 1 if an error occurred.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No files specified\n");
        return 1;
    }

    list_manager(argc, argv);

    return 0;
}
