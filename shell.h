#ifndef SHELL_H
#define SHELL_H

// Maximum length for various strings
#define MAX_PATH_LEN 4096
#define MAX_COMMANDS 100
#define MAX_ALIASES 50
#define MAX_ALIAS_NAME_LEN 50

// Alias structure
typedef struct {
    char name[MAX_ALIAS_NAME_LEN];
    char value[MAX_PATH_LEN];
} Alias;

// Function prototypes
void update_pwd();
int execute_command(char *command, int *status);
void execute_logical_commands(char *commands[], int command_count);
void print_aliases();
void print_selected_aliases(char *names[], int name_count);
void define_alias(char *name, char *value);

// Function prototype for parse_command
void parse_command(char *input, char *tokens[], int *token_count);

#endif /* SHELL_H */
