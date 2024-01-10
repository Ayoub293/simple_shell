#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH_LEN 4096

void update_pwd() {
    char cwd[MAX_PATH_LEN];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("PWD", cwd, 1);
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    char *home_dir = getenv("HOME");
    char *old_pwd = NULL;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [DIRECTORY]\n", argv[0]);
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

    return 0;
}
