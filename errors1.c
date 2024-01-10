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
    static char input_buffer[BUFFER_SIZE];
    static size_t buffer_index = 0;
    static ssize_t bytes_in_buffer = 0;

    ssize_t total_bytes = 0;

    while (1) {
        // Refill the buffer if needed
        if (buffer_index == bytes_in_buffer) {
            bytes_in_buffer = read(STDIN_FILENO, input_buffer, BUFFER_SIZE);

            // Check for EOF
            if (bytes_in_buffer == 0) {
                if (total_bytes == 0) {
                    return 0; // EOF at the beginning
                }
                break;
            } else if (bytes_in_buffer == -1) {
                perror("read");
                return -1; // Error
            }

            buffer_index = 0;
        }

        // Copy bytes from the input buffer to the user buffer
        while (buffer_index < bytes_in_buffer && total_bytes < size - 1) {
            if (input_buffer[buffer_index] == '\n') {
                buffer[total_bytes++] = input_buffer[buffer_index++];
                buffer[total_bytes] = '\0'; // Null-terminate the string
                return total_bytes;
            }

            buffer[total_bytes++] = input_buffer[buffer_index++];
        }
    }

    buffer[total_bytes] = '\0'; // Null-terminate the string
    return total_bytes;
}

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        // Display prompt
        write(STDOUT_FILENO, "$ ", 2);

        // Read command from the user using custom_getline
        ssize_t n = custom_getline(buffer, BUFFER_SIZE);

        // Check for end of file (Ctrl+D)
        if (n == 0) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        // Remove newline character
        buffer[n - 1] = '\0';

        // Check for exit built-in
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Fork a new process (rest of the code remains the same)
        // ...
    }

    return EXIT_SUCCESS;
}
