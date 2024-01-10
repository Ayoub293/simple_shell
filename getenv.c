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
    // ... (same as before)
}

/**
 * execute_setenv - handle the setenv built-in command
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, -1 on failure
 */
int execute_setenv(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "setenv: Incorrect number of arguments\n");
        return -1;
    }

    if (setenv(argv[1], argv[2], 1) != 0) {
        perror("setenv");
        return -1;
    }

    return 0;
}

/**
 * execute_unsetenv - handle the unsetenv built-in command
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, -1 on failure
 */
int execute_unsetenv(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "unsetenv: Incorrect number of arguments\n");
        return -1;
    }

    if (unsetenv(argv[1]) != 0) {
        perror("unsetenv");
        return -1;
    }

    return 0;
}

int main(void) {
    // ... (same as before)

    while (1) {
        // ... (same as before)

        // Check for setenv and unsetenv built-in commands
        if (strcmp(argv[0], "setenv") == 0) {
            execute_setenv(argc, argv);
        } else if (strcmp(argv[0], "unsetenv") == 0) {
            execute_unsetenv(argc, argv);
        }

        // ... (rest of the code remains the same)

        // Free allocated memory for arguments
        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
