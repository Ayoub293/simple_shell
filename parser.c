#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, const char *path)
{
    struct stat st;

    (void)info;
    return path && stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

/**
 * dup_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Newly allocated string containing the duplicated characters.
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
    char *buf = NULL;
    int k = 0;

    buf = malloc(stop - start + 1);
    if (!buf)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = start; i < stop; i++)
    {
        if (pathstr[i] != ':')
        {
            buf[k++] = pathstr[i];
        }
    }

    buf[k] = '\0';
    return buf;
}

/**
 * find_path - Finds this cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found, or NULL.
 */
char *find_path(info_t *info, const char *pathstr, const char *cmd)
{
    if (!pathstr || !cmd)
    {
        return NULL;
    }

    if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
    {
        return is_cmd(info, cmd) ? strdup(cmd) : NULL;
    }

    int i = 0, curr_pos = 0;
    char *path = NULL;

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
            {
                _strcat(path, cmd);
            }
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            if (is_cmd(info, path))
            {
                return path;
            }

            if (!pathstr[i])
            {
                break;
            }

            curr_pos = i;
        }
        i++;
    }

    return NULL;
}
