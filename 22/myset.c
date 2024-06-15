/**
 * @brief The program is a pocket calculator that defines sets
 */

#include "set.h"

#define extra_text \
            if ((command_part = read_next_part(user_command, &position)) \
                || comma_checker(user_command, &position)) { \
                    fprintf(stderr, "Extraneous text after end of command\n"); \
                    safe_free(command_part);   \
                    safe_free(user_command)                  \
                    return -1;\
            }

#define missing_comma \
        commas = comma_checker(user_command, &position); \
        switch (commas) { \
            case 0:   \
                fprintf(stdout, "Missing comma\n");       \
                safe_free(user_command)                       \
                safe_free(command_part)                       \
                return -1;                                \
            case 1:   \
                break;\
            default:   \
                fprintf(stdout, "Multiple consecutive commas\n"); \
                safe_free(user_command)                        \
                safe_free(command_part)                        \
                return -1;                                \
        }

#define illegal_comma \
        if (comma_checker(user_command, &position)) { \
            fprintf(stdout, "Illegal comma\n");       \
            safe_free(user_command)                        \
            return -1;\
        }

/**
 * @brief the function manages the command reading and execution
 * @param sets an array of pointers to the sets
 * @return 0
 */
int input_reader(set **sets) {
    int c, set1, set2, set3, /* character, sets */
        command; /* command number */
    unsigned int buffer = 0, position = 0, commas; /* counters */
    char *user_command = NULL, *temp_realloc = NULL,
         *command_part = NULL; /* strings */

    /* Initial allocation */
    if (!(user_command = (char *)calloc(20, sizeof(char)))) {
        allocation_failure
    }

    if (isatty(fileno(stdin))) {
        fprintf(stdout, "Please enter a command:\n");
    }

    /* Skip whitespaces */
    while ((c = fgetc(stdin)) == ' ' || c == '\t' || c == '\n');

    /* Read the user's command and store it, reallocate if needed */
    do {
        if (c == EOF) {
            fprintf(stderr, "Error: Reached end of file.\n");
            stop(); /* exit the program*/
        }

        /* Reallocate if needed */
        if ((buffer >= 19)
            && !(user_command = (char *) realloc(user_command,
                                            sizeof(char) * (buffer + 2)))) {
            safe_free(user_command)
            safe_free(temp_realloc)
            allocation_failure
        }
        user_command[buffer] = (char)c;
        ++buffer;
    } while ((c = fgetc(stdin)) != '\n');
    user_command[buffer] = '\0';

    /* Print the user's command */
    fprintf(stdout, "%s\n", user_command);

    /* Ensuring there is no comma before the command */
    illegal_comma

    /* Check if the command is defined */
    if ((command = command_verifier(user_command, &position)) == -1) {
        safe_free(user_command)
        return -1;
    }

    /* Command is stop */
    if (command == 6) {
        extra_text
        fprintf(stdout, "Exiting...\n");
        safe_free(user_command)
        stop(); /* exit the program */
        return 0;
    }

    /* Ensuring there is no comma after the command */
    illegal_comma

    /* Check if the set is defined */
    if ((set1 = set_verifier(user_command, &position)) == -1) {
        safe_free(user_command)
        return -1;
    }

    /* Command is print_set */
    if (command == 1) {
        extra_text
        if (print_set(sets[set1]) == -1)
            fprintf(stdout, "The set is empty\n");
        safe_free(user_command)
        return 0;
    }

    missing_comma

    /* Command is read_set */
    if (command == 0) {
        read_parser(user_command, &position, sets[set1]);
        safe_free(user_command)
        return 0;
    }

    /* Check next parts of the command */
    if ((set2 = set_verifier(user_command, &position)) == -1) {
        safe_free(user_command)
        return -1;
    }
    missing_comma
    if ((set3 = set_verifier(user_command, &position)) == -1) {
        safe_free(user_command)
        return -1;
    }
    extra_text

    switch (command) {
        case 2: /* Union set */
            union_set(*sets[set1], *sets[set2], sets[set3]);
            break;
        case 3: /* Intersect set */
            intersect_set(*sets[set1], *sets[set2], sets[set3]);
            break;
        case 4: /* Sub set */
            sub_set(*sets[set1], *sets[set2], sets[set3]);
            break;
        case 5: /* Symdiff set */
            symdiff_set(*sets[set1], *sets[set2], sets[set3]);
            break;
        default: /* Undefined command was already checked */
            break;
    }
    safe_free(user_command)
    return 0;
}

/**
 * @brief the function defines the user interface
 * @param void
 * @return 0
 */
int main(void) {
    /* Sets */
    set SETA, SETB, SETC, SETD, SETE, SETF;
    /* Array of set pointers */
    set *sets[6];

    /* Initializing sets */
    memset(&SETA, 0, sizeof(set));
    memset(&SETB, 0, sizeof(set));
    memset(&SETC, 0, sizeof(set));
    memset(&SETD, 0, sizeof(set));
    memset(&SETE, 0, sizeof(set));
    memset(&SETF, 0, sizeof(set));

    /* Initialize the set pointers */
    sets[0] = &SETA;
    sets[1] = &SETB;
    sets[2] = &SETC;
    sets[3] = &SETD;
    sets[4] = &SETE;
    sets[5] = &SETF;

    /* Check if stdin is a terminal and print welcome message */
    if (isatty(fileno(stdin))) {
        fprintf(stdout, "Welcome to your pocket computer!\n");
    }

    /* Reading commands */
    while (1) input_reader(sets);

    return 0;
}
