#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LEN 4096
#define MAX_COMMANDS 100

void update_pwd() {
    char cwd[MAX_PATH_LEN];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("PWD", cwd, 1);
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

void execute_command(char *command) {
    char *token;
    char *commands[MAX_COMMANDS];
    int command_count = 0;

    // Tokenize the command based on semicolons
    token = strtok(command, ";");
    while (token != NULL && command_count < MAX_COMMANDS) {
        commands[command_count++] = token;
        token = strtok(NULL, ";");
    }

    // Execute each command
    for (int i = 0; i < command_count; i++) {
        char *trimmed_command = strtok(commands[i], " \t\n");
        if (trimmed_command != NULL) {
            // Execute the trimmed command
            system(trimmed_command);
        }
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

    // Execute commands separated by semicolons
    char command[MAX_PATH_LEN];
    printf("Enter commands separated by semicolons (;):\n");
    fgets(command, sizeof(command), stdin);
    execute_command(command);

    return 0;
}
