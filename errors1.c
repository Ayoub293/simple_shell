#include "shell.h"

/**
 * @brief Converts a string to an integer.
 *
 * @param s The string to be converted.
 * @return 0 if no numbers in the string, converted number otherwise,
 *         -1 on error.
 */
int _erratoi(char *s)
{
    if (*s == '+')
        s++;

    unsigned long int result = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
        {
            return -1;
        }
    }

    return result;
}

/**
 * @brief Prints an error message.
 *
 * @param info The parameter & return info struct.
 * @param estr String containing specified error type.
 */
void print_error(info_t *info, const char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * @brief Prints a decimal (integer) number (base 10).
 *
 * @param input The input number.
 * @param fd The file descriptor to write to.
 * @return The number of characters printed.
 */
int print_d(int input, int fd)
{
    int (*putchar_func)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;
    unsigned int abs_value = (input < 0) ? -input : input;
    unsigned int current = abs_value;

    if (input < 0)
    {
        putchar_func('-');
        count++;
    }

    for (int i = 1000000000; i > 1; i /= 10)
    {
        if (abs_value / i)
        {
            putchar_func('0' + current / i);
            count++;
        }
        current %= i;
    }

    putchar_func('0' + current);
    count++;

    return count;
}

/**
 * @brief Converts a number to a string.
 *
 * @param num The number to convert.
 * @param base The base of the number.
 * @param flags Argument flags.
 * @return The string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
    static char buffer[50];
    char *ptr = &buffer[49];
    unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;

    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (num < 0 && !(flags & CONVERT_UNSIGNED))
        *--ptr = '-';

    return ptr;
}

/**
 * @brief Replaces the first instance of '#' with '\0'.
 *
 * @param buf Address of the string to modify.
 */
void remove_comments(char *buf)
{
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
