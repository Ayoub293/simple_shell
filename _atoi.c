#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        // Display prompt
        write(STDOUT_FILENO, "$ ", 2);

        // Read command from the user
        ssize_t n = read(STDIN_FILENO, buffer, BUFFER_SIZE);

        // Check for end of file (Ctrl+D)
        if (n == 0) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        // Remove newline character
        buffer[n - 1] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            // Execute the command using execve
            if (execve(buffer, NULL, NULL) == -1) {
                // Print an error message if the command is not found
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            // Wait for the child process to complete
            waitpid(pid, NULL, 0);
        }
    }

    return EXIT_SUCCESS;
}
