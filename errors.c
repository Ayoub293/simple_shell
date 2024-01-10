#include "shell.h"

/**
 * @brief Writes a string to standard error.
 *
 * @param str The string to be printed.
 */
void _eputs(char *str)
{
    if (!str)
        return;

    while (*str)
    {
        _eputchar(*str++);
    }
}

/**
 * @brief Writes a character to standard error.
 *
 * @param c The character to print.
 * @return On success, returns 1. On error, returns -1, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int count = 0;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
    {
        write(2, buffer, count);
        count = 0;
    }

    if (c != BUF_FLUSH)
        buffer[count++] = c;

    return 1;
}

/**
 * @brief Writes a character to a specified file descriptor.
 *
 * @param c The character to print.
 * @param fd The file descriptor to write to.
 * @return On success, returns 1. On error, returns -1, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int count = 0;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, count);
        count = 0;
    }

    if (c != BUF_FLUSH)
        buffer[count++] = c;

    return 1;
}

/**
 * @brief Writes a string to a specified file descriptor.
 *
 * @param str The string to be printed.
 * @param fd The file descriptor to write to.
 * @return The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return 0;

    while (*str)
    {
        count += _putfd(*str++, fd);
    }

    return count;
}
