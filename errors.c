#include "shell.h"

/**
 * _eputs - Outputs a given input string.
 * @str: The string to be printed.
 *
 * This function is used to display the provided string as output.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes the character c to the standard error stream (stderr).
 * @c: The character to be printed.
 *
 * This function writes the provided character to the stderr stream. If the
 * buffer is full or a special flush character is encountered, the buffer is
 * written to stderr.
 *
 * Return: On success, it returns 1. On error, -1 is returned, and the errno
 *         variable is set accordingly.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
	write(2, buf, i);
	i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putfd - Writes the character c to the specified file descriptor (fd).
 * @c: The character to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function writes the provided character to
 * the specified file descriptor.
 * If the buffer is full or a flush condition is met,
 * the buffer is written to
 * the file descriptor.
 *
 * Return: On success, it returns 1. On error, -1 is returned, and the errno
 *         variable is set accordingly.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Writes the input string to the specified file descriptor (fd).
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function outputs the provided string to the specified file descriptor.
 * It returns the number of characters written.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
