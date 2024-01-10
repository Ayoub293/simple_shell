#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main() {
    char input[MAX_PATH_LEN];
    char *commands[MAX_COMMANDS];
    int command_count;
    int status;

    // Main shell loop
    while (1) {
        // Display the prompt (you can customize this)
        printf("SimpleShell> ");

        // Read user input
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Check for exit command
        if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell...\n");
            break;
        }

        // Parse the command
        parse_command(input, commands, &command_count);

        // Execute logical commands
        execute_logical_commands(commands, command_count);

        // Free memory allocated for the command tokens
        for (int i = 0; i < command_count; i++) {
            free(commands[i]);
        }
    }

    return 0;
}
