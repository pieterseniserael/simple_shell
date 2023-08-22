#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return dest_start;
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	if (!str)
		return NULL;

	char *dup = malloc(_strlen(str) + 1);
	if (!dup)
		return NULL;

	return _strcpy(dup, str);
}

/**
 * _puts - prints a string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(const char *str)
{
	if (!str)
		return;

	while (*str)
		_putchar(*str++);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i = 0;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return 1;
}
