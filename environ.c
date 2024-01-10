#include "shell.h"

/**
 * @brief Prints the current environment.
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int _myenv(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

/**
 * @brief Gets the value of an environment variable.
 *
 * @param info Structure containing potential arguments.
 * @param name Environment variable name.
 * @return The value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }

    return NULL;
}

/**
 * @brief Initializes a new environment variable or modifies an existing one.
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

/**
 * @brief Removes an environment variable.
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * @brief Populates the environment linked list.
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);

    info->env = node;
    return 0;
}
