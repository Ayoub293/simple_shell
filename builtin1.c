#include "shell.h"

/**
 * @brief Displays the command history with line numbers.
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * @brief Unsets an alias.
 *
 * @param info Parameter struct.
 * @param str The string alias.
 * @return Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *equal_sign_pos;
    int ret;

    equal_sign_pos = _strchr(str, '=');
    if (!equal_sign_pos)
        return 1;

    *equal_sign_pos = '\0';
    ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *equal_sign_pos = '=';

    return ret;
}

/**
 * @brief Sets an alias to a string.
 *
 * @param info Parameter struct.
 * @param str The string alias.
 * @return Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *equal_sign_pos;

    equal_sign_pos = _strchr(str, '=');
    if (!equal_sign_pos)
        return 1;

    if (!*++equal_sign_pos)
        return unset_alias(info, str);

    unset_alias(info, str);
    return add_node_end(&(info->alias), str, 0) == NULL;
}

/**
 * @brief Prints an alias string.
 *
 * @param node The alias node.
 * @return Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *equal_sign_pos = NULL;
    char *alias_start = NULL;

    if (node)
    {
        equal_sign_pos = _strchr(node->str, '=');
        for (alias_start = node->str; alias_start <= equal_sign_pos; alias_start++)
            _putchar(*alias_start);

        _putchar('\'');
        _puts(equal_sign_pos + 1);
        _puts("'\n");

        return 0;
    }

    return 1;
}

/**
 * @brief Mimics the alias builtin (man alias).
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int _myalias(info_t *info)
{
    int i;
    char *equal_sign_pos;
    list_t *node;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equal_sign_pos = _strchr(info->argv[i], '=');
        if (equal_sign_pos)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}
