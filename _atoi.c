#include "shell.h"
#include <unistd.h>

/**
 * @brief Checks if the shell is in interactive mode.
 *
 * @param info The information structure for the shell.
 * @return Returns 1 if in interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * @brief Checks if a character is a delimiter.
 *
 * @param c The character to check.
 * @param delim The delimiter string.
 * @return Returns 1 if true, 0 if false.
 */
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}

	return (0);
}

/**
 * @brief Checks if a character is alphabetic.
 *
 * @param c The character to check.
 * @return Returns 1 if the character is alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * @brief Converts a string to an integer.
 *
 * @param s The string to be converted.
 * @return the converted integer. If no numbers in the string, returns 0.
 */
int atoi_custom(const char *s)
{
	int sign = 1, flag = 0;
	unsigned int result = 0;

	for (int i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		{
			else if (flag == 1)
		{
			flag = 2;
		}
	}
	return ((sign == -1) ? -result : result);
}

