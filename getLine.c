#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * custom_getline - read a line from standard input
 * @buffer: pointer to the buffer where the line is stored
 * @size: size of the buffer
 * Return: number of characters read (including newline), 0 on EOF, -1 on error
 */
ssize_t custom_getline(char *buffer, size_t size) {
    // ... (same as before)
}

/**
 * split_line - split a line into an array of words
 * @line: input line
 * @argv: array of strings to store the words
 * Return: number of words
 */
int split_line(char *line, char **argv) {
    // ... (same as before)
}

/**
 * execute_exit - handle the exit built-in command with arguments
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 1 if exit should be executed, 0 otherwise
 */
int execute_exit(int argc, char **argv) {
    if (argc == 1) {
        // No arguments provided, execute normal exit
        return 1;
    } else if (argc == 2) {
        // Argument provided, check if it's a valid integer
        int status = atoi(argv[1]);
        if (status != 0 || (status == 0 && strcmp(argv[1], "0") == 0)) {
            // Valid integer, exit with specified status
            exit(status);
        } else {
            // Invalid argument
            fprintf(stderr, "Exit: Invalid status argument\n");
            return 0;
        }
    } else {
        // Too many arguments
        fprintf(stderr, "Exit: Too many arguments\n");
        return 0;
    }
}

int main(void) {
    // ... (same as before)

    while (1) {
        // ... (same as before)

        // Split the line into an array of words
        int argc = split_line(buffer, argv);

        // Check for exit built-in
        if (strcmp(argv[0], "exit") == 0) {
            if (execute_exit(argc, argv)) {
                // Free allocated memory for arguments
                for (int i = 0; i < argc; i++) {
                    free(argv[i]);
                }
                break;
            }
        }

        // ... (rest of the code remains the same)

        // Free allocated memory for arguments
        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
