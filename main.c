#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

#define MAX_PATH_LEN 4096
#define MAX_COMMANDS 100
#define MAX_ALIASES 50
#define MAX_ALIAS_NAME_LEN 50

typedef struct {
    char name[MAX_ALIAS_NAME_LEN];
    char value[MAX_PATH_LEN];
} Alias;

Alias aliases[MAX_ALIASES];
int alias_count = 0;

void update_pwd() {
    char cwd[MAX_PATH_LEN];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("PWD", cwd, 1);
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

int execute_command(char *command) {
    int status;

    // Execute the command and get the exit status
    status = system(command);

    if (WIFEXITED(status)) {
        // The command exited normally
        return WEXITSTATUS(status);
    } else {
        // The command did not exit normally
        return -1;
    }
}

void execute_logical_commands(char *commands[], int command_count) {
    int status;

    // Execute each command
    for (int i = 0; i < command_count; i++) {
        char *trimmed_command = strtok(commands[i], " \t\n");
        if (trimmed_command != NULL) {
            // Check if the command is an alias
            int alias_index = -1;
            for (int j = 0; j < alias_count; j++) {
                if (strcmp(trimmed_command, aliases[j].name) == 0) {
                    alias_index = j;
                    break;
                }
            }

            // If it's an alias, execute the alias value instead
            if (alias_index != -1) {
                status = execute_command(aliases[alias_index].value);
            } else {
                // Execute the trimmed command
                status = execute_command(trimmed_command);

                // Handle logical operators
                if (i < command_count - 1) {
                    char *logical_operator = strtok(NULL, " \t\n");
                    if (logical_operator != NULL) {
                        if (strcmp(logical_operator, "&&") == 0 && status != 0) {
                            // Skip the next command if the previous one failed
                            i++;
                        } else if (strcmp(logical_operator, "||") == 0 && status == 0) {
                            // Skip the next command if the previous one succeeded
                            i++;
                        }
                    }
                }
            }
        }
    }
}

void print_aliases() {
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void print_selected_aliases(char *names[], int name_count) {
    for (int i = 0; i < name_count; i++) {
        for (int j = 0; j < alias_count; j++) {
            if (strcmp(names[i], aliases[j].name) == 0) {
                printf("%s='%s'\n", aliases[j].name, aliases[j].value);
                break;
            }
        }
    }
}

void define_alias(char *name, char *value) {
    if (alias_count < MAX_ALIASES) {
        // Check if the alias already exists
        for (int i = 0; i < alias_count; i++) {
            if (strcmp(name, aliases[i].name) == 0) {
                // Update the value of the existing alias
                strcpy(aliases[i].value, value);
                return;
            }
        }

        // Define a new alias
        strcpy(aliases[alias_count].name, name);
        strcpy(aliases[alias_count].value, value);
        alias_count++;
    } else {
        fprintf(stderr, "alias: Too many aliases\n");
    }
}

int main(int argc, char *argv[]) {
    char *home_dir = getenv("HOME");
    char *old_pwd = NULL;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [COMMAND]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 1 || strcmp(argv[1], "~") == 0) {
        if (chdir(home_dir) != 0) {
            perror("chdir() error");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[1], "-") == 0) {
        old_pwd = getenv("OLDPWD");
        if (old_pwd == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            exit(EXIT_FAILURE);
        }

        if (chdir(old_pwd) != 0) {
            perror("chdir() error");
            exit(EXIT_FAILURE);
        }
    } else {
        if (chdir(argv[1]) != 0) {
            perror("chdir() error");
            exit(EXIT_FAILURE);
        }
    }

    update_pwd();

    if (old_pwd != NULL) {
        printf("%s\n", old_pwd);
        free(old_pwd);
    }

    // Execute commands with logical operators and aliases
    char command[MAX_PATH_LEN];
    printf("Enter commands with logical operators and aliases:\n");
    fgets(command, sizeof(command), stdin);

    char *token;
    char *commands[MAX_COMMANDS];
    int command_count = 0;

    // Tokenize the command based on semicolons
    token = strtok(command, ";");
    while (token != NULL && command_count < MAX_COMMANDS) {
        commands[command_count++] = token;
        token = strtok(NULL, ";");
    }

    // Execute logical commands
    execute_logical_commands(commands, command_count);

    // Handling the 'alias' command
    if (strstr(command, "alias") != NULL) {
        char *alias_command = strtok(command, " \t\n");
        if (strcmp(alias_command, "alias") == 0) {
            char *name = strtok(NULL, " \t\n");
            if (name != NULL) {
                // Check if the command is 'alias' or 'alias name=value'
                if (strchr(name, '=') != NULL) {
                    // 'alias name=value' syntax
                    define_alias(name, strchr(name, '=') + 1);
                } else {
                    // 'alias name' syntax
                    char *names[MAX_ALIASES];
                    int name_count = 0;

                    // Tokenize the command based on spaces
                    names[name_count++] = name;
                    while ((name = strtok(NULL, " \t\n")) != NULL && name_count < MAX_ALIASES) {
                        names[name_count++] = name;
                    }

                    // Print aliases with specified names
                    print_selected_aliases(names, name_count);
                }
            } else {
                // Print all aliases
                print_aliases();
            }
        }
    }

    return 0;
}

void parse_command(char *input, char *tokens[], int *token_count) {
    // Implementation
}

void execute_logical_commands(char *commands[], int command_count) {
    // Implementation
}

// Rest of the code

