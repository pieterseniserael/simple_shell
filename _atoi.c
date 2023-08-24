#include "shell.h"

/**
 * interactive - Checks if the current shell is in interactive mode.
 * returns true if shell is interactive mode.
 * @info: struct address:
 *
 * Return: Returns 1 if interactive mode, otherwise, Return 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Determines if a given character is a delimiter.
 * @c: The character to be checked.
 * @delim: The string containing delimiters to compare against.
 *
 * This function examines whether the provided character is present in the
 * specified delimiter string, thus indicate if it serves as a delimiter.
 *
 * Return: Returns 1 if the character is a delimiter, otherwise returns 0.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Determines whether a given character is an alphabetic character.
 * @c: The input character to be checked.
 *
 * This function examines whether the provided character is an alphabetic
 * character.
 *
 * Return: Returns 1 if the character is alphabetic, otherwise returns 0.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer.
 * @s: The string to be converted.
 *
 * This function attempts to convert the provided string into an integer.
 *
 * Return: Returns 0 if no numbers are found in the string,
 * otherwise returns the converted integer.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
