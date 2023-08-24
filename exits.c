#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to copy to.
 * @src: The source string.
 * @n: The number of characters to copy.
 *
 * This function copies up to 'n' characters from the source string to the
 * destination string. It returns the modified destination string.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * This function appends the characters from the source string to the end of
 * the destination string, using at most 'n' bytes.
 * It returns the concatenated string.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to locate.
 *
 * This function searches the given string for the first
 * occurrence of the specified character.
 * It returns a pointer to the memory area containing that
 * character within the string.
 *
 * Return: A pointer to the memory area in 's' containing the
 * character 'c', or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
