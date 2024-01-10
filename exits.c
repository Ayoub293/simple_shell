#include "shell.h"

/**
 * @brief Copies a string with a specified maximum length.
 *
 * @param dest The destination string to be copied to.
 * @param src The source string.
 * @param n The maximum number of characters to be copied.
 * @return A pointer to the destination string.
 */
char *_strncpy(char *dest, const char *src, int n)
{
    char *destination = dest;

    int i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }

    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }

    return destination;
}

/**
 * @brief Concatenates two strings with a specified maximum length.
 *
 * @param dest The destination string.
 * @param src The source string.
 * @param n The maximum number of bytes to be used.
 * @return A pointer to the destination string.
 */
char *_strncat(char *dest, const char *src, int n)
{
    char *destination = dest;

    int i = 0;
    while (dest[i] != '\0')
        i++;

    int j = 0;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';

    return destination;
}

/**
 * @brief Locates a character in a string.
 *
 * @param s The string to be parsed.
 * @param c The character to look for.
 * @return A pointer to the memory area containing the character, or NULL if not found.
 */
char *_strchr(const char *s, char c)
{
    while (*s != '\0')
    {
        if (*s == c)
            return (char *)s;

        s++;
    }

    return NULL;
}
