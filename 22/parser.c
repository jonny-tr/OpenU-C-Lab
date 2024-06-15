/**
 * @brief a parser for the command entered by the user
 */

#include "set.h"

/**
 * @brief the function reads the next part of the command
 * @param user_command the command entered by the user
 * @param position the position in the command
 * @return pointer to the string read, or NULL if there is no text
 */
char *read_next_part(const char user_command[], unsigned int *position) {
    char c, *next_part = NULL; /* strings */
    int buffer = 0; /* counter */

    /* Check if the command is finished */
    if (user_command[*position] == '\0') return NULL;

    /* Initial allocation */
    if (!(next_part = (char *)calloc(20, sizeof(char)))) {
        allocation_failure
    }

    /* Skip whitespaces */
    while ((c = user_command[*position]) == ' ' || c == '\t') ++(*position);

    /* Read the user's command and store it, reallocate if needed */
    while ((c = user_command[*position]) != ' ' && c != '\t' && c != '\0') {
        if (buffer >= 19 &&
            !(next_part = (char *)realloc(next_part,
                                          sizeof(char) * (buffer + 2)))) {
            allocation_failure
        }
        /* Don't store comma */
        if (c == ',') break;
        next_part[buffer] = c;
        ++buffer;
        ++(*position);
    }
    next_part[buffer] = '\0';

    return next_part;
}

/**
 * @brief checks if the next character is a comma
 * @param user_command the command entered by the user
 * @param position the position in the command
 * @return amount of commas, 0 if there is no comma
 */
unsigned int comma_checker(const char user_command[], unsigned int *position) {
    unsigned int commas = 0; /* counter */

    /* Skip whitespaces */
    while ((user_command[*position]) == ' '
           || (user_command[*position]) == '\t') ++(*position);

    while (user_command[*position] == ',') {
        ++(*position);
        ++commas;
    }

    return commas;
}

/**
 * @brief checks which command was chosen
 * @param user_command the command entered by the user
 * @param position the position in the command
 * @return command num, or -1 if the command was not found
 */
int command_verifier(char user_command[], unsigned int *position) {
    char *command, *commands[] = {"read_set", "print_set",
                                  "union_set", "intersect_set",
                                  "sub_set", "symdiff_set",
                                  "stop"}; /* strings */
    int i; /* counter */

    /* Read the user's command and store it */
    if ((command = read_next_part(user_command, position)) == NULL) {
        safe_free(command)
        return -1;
    }

    /* Check if the command is defined */
    for (i = 0; i < 7; ++i) {
        if (strcmp(commands[i], command) == 0) {
            safe_free(command)
            return i;
        }
    }

    fprintf(stderr, "Undefined command name\n");
    safe_free(command)
    return -1;
}

/**
 * @brief checks which set was chosen
 * @param user_command the command entered by the user
 * @param position the position in the command
 * @return set num, or -1 if the set was not found
 */
int set_verifier(char user_command[], unsigned int *position) {
    char *set_name, *sets[] = {"SETA", "SETB", "SETC",
                               "SETD", "SETE", "SETF"};
    int i;

    /* Read the user's command and store it */
    if ((set_name = read_next_part(user_command, position)) == NULL) {
        fprintf(stderr, "Missing parameter\n");
        safe_free(set_name)
        return -1;
    }

    for (i = 0; i < 6; ++i) {
        if (strcmp(sets[i], set_name) == 0) {
            safe_free(set_name)
            return i;
        }
    }

    fprintf(stderr, "Undefined set name\n");
    safe_free(set_name)
    return -1;
}

/**
 * @brief parses the read command and sends it to read_set
 * @param user_command the command entered by the user
 * @param position the position in the command
 * @param set1 the set to be filled
 * @return 0 if ok, -1 if there was an error
 */
int read_parser(const char user_command[], unsigned int *position, set *set1) {
    /* counters and arrays */
    int i, buffer = 0, *command_numbers, next_number, amount_numbers = 0;
    unsigned int commas; /* external counter */
    char *command_part; /* string */

    /* Initial allocation */
    if (!(command_numbers = (int *)calloc(20, sizeof(int)))) {
        allocation_failure
    }

    /* Read the user's command and store it */
    while ((command_part = read_next_part(user_command, position)) != NULL) {

        if (strcmp(command_part, "-1") == 0) break;

        /* Check if the command_part is an integer */
        for (i = 0; i < strlen(command_part); ++i) {
            if (!isdigit(command_part[i])) {
                fprintf(stderr, "Invalid set member – not an integer\n");
                safe_free(command_numbers)
                safe_free(command_part)
                return -1;
            }
        }

        commas = comma_checker(user_command, position);
        switch (commas) {
            case 0:
                fprintf(stdout, "Missing comma\n");
                safe_free(command_numbers)
                safe_free(command_part)
                return -1;
            case 1:
                break;
            default:
                fprintf(stdout, "Multiple consecutive commas\n");
                safe_free(command_numbers)
                safe_free(command_part)
                return -1;
        }

        /* Reallocate if needed */
        if (buffer >= 19 &&
            !(command_numbers = (int *)realloc(command_numbers, buffer + 2))) {
            allocation_failure
        }

        next_number = atoi(command_part);
        if (next_number >= 0 && next_number <= 127) {
            command_numbers[buffer] = next_number;
            ++amount_numbers;
            ++buffer;
        }
        else {
            fprintf(stderr, "Invalid set member – value out of range\n");
            safe_free(command_numbers)
            safe_free(command_part)
            return -1;
        }
    }
    
    /* Last part of the command was not -1 */
    if (strcmp(command_part, "-1") != 0) {
        fprintf(stderr, "List of set members is not terminated correctly\n");
        safe_free(command_numbers)
        safe_free(command_part)
        return -1;
    }
    
    /* Ensuring there is nothing after the command */
    if ((command_part = read_next_part(user_command, position))
        || (comma_checker(user_command, position))) {
        fprintf(stdout, "Extraneous text after end of command\n");
        safe_free(command_numbers)
        if (command_part != NULL) safe_free(command_part)
        return -1;
    }

    read_set(set1, command_numbers, amount_numbers);

    safe_free(command_numbers)
    safe_free(command_part)
    return 0;
}
