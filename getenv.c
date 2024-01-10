#include "shell.h"

/**
 * @brief Returns the string array copy of our environment.
 *
 * @param info Structure containing potential arguments.
 * @return String array of environment variables.
 */
char **get_environ(info_t *info) {
    if (!info->environ || info->env_changed) {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * @brief Removes an environment variable.
 *
 * @param info Structure containing potential arguments.
 * @param var The string env var property.
 * @return 1 on successful delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var) {
    list_t *node = info->env;
    size_t index = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node) {
        p = starts_with(node->str, var);
        if (p && *p == '=') {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }
    return info->env_changed;
}

/**
 * @brief Initializes a new environment variable or modifies an existing one.
 *
 * @param info Structure containing potential arguments.
 * @param var The string env var property.
 * @param value The string env var value.
 * @return Always 0.
 */
int _setenv(info_t *info, char *var, char *value) {
    char *env_entry = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    env_entry = malloc(_strlen(var) + _strlen(value) + 2);
    if (!env_entry)
        return 1;

    _strcpy(env_entry, var);
    _strcat(env_entry, "=");
    _strcat(env_entry, value);

    node = info->env;
    while (node) {
        p = starts_with(node->str, var);
        if (p && *p == '=') {
            free(node->str);
            node->str = env_entry;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), env_entry, 0);
    free(env_entry);
    info->env_changed = 1;
    return 0;
}
