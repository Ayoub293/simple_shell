#include "shell.h"

/**
 * @brief Initializes the info_t struct.
 *
 * @param info Pointer to the info_t struct.
 */
void clear_info(info_t *info) {
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * @brief Initializes the info_t struct with command line arguments.
 *
 * @param info Pointer to the info_t struct.
 * @param av Argument vector.
 */
void set_info(info_t *info, char **av) {
    int argc = 0;

    info->fname = av[0];
    
    if (info->arg) {
        info->argv = strtow(info->arg, " \t");

        if (!info->argv) {
            info->argv = malloc(sizeof(char *) * 2);

            if (info->argv) {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }

        for (argc = 0; info->argv && info->argv[argc]; argc++)
            ;
        
        info->argc = argc;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * @brief Frees the allocated memory in the info_t struct.
 *
 * @param info Pointer to the info_t struct.
 * @param freeAll Flag indicating whether to free all fields.
 */
void free_info(info_t *info, int freeAll) {
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (freeAll) {
        if (!info->cmd_buf)
            free(info->arg);

        free_list(&(info->env));
        free_list(&(info->history));
        free_list(&(info->alias));

        ffree(info->environ);
        info->environ = NULL;

        bfree((void **)info->cmd_buf);

        if (info->readfd > 2)
            close(info->readfd);

        _putchar(BUF_FLUSH);
    }
}
