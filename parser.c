#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_SIZE 50

void parse_command(char *input, char *tokens[], int *token_count) {
    // Tokenize the input command based on spaces
    char *token = strtok(input, " \t\n");
    *token_count = 0;

    while (token != NULL && *token_count < MAX_TOKENS) {
        tokens[*token_count] = strdup(token);
        (*token_count)++;
        token = strtok(NULL, " \t\n");
    }
}

int main() {
    char input[MAX_TOKEN_SIZE];
    char *tokens[MAX_TOKENS];
    int token_count;

    printf("Enter a command: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    // Parse the command
    parse_command(input, tokens, &token_count);

    // Display the parsed tokens
    printf("Parsed tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i]);
        free(tokens[i]);
    }

    return 0;
}
