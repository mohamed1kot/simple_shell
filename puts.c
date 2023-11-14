#include "shell.h"

/**
 * _eputs - Print a string to STDERR.
 *
 * @str: The string to print.
*/

void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - Print a character to STDERR.
 *
 * @C: The character to print.
 *
 * Return: 1 if successful.
*/

int _eputchar(char C)
{
	static int i;
	static char buffer[BUF_SIZE];

	if ((C == BUF_FLUSH) || (i >= BUF_SIZE))
	{
		write(2, buffer, i);
		i = 0;
	}
	if (C != BUF_FLUSH)
		buffer[i++] = C;
	return (1);
}

/**
 * _putfd - Print a character to a specified file descriptor.
 *
 * @C: The character to print.
 * @fd: The file descriptor to print to.
 *
 * Return: 1 if successful.
*/

int _putfd(char C, int fd)
{
	static int j;
	static char buffer[BUF_SIZE];

	if ((C == BUF_FLUSH) || (j >= BUF_SIZE))
	{
		write(fd, buffer, j);
		j = 0;
	}
	if (C != BUF_FLUSH)
		buffer[j++] = C;
	return (1);
}

/**
 * _putsfd - Print a string to a specified file descriptor.
 *
 * @str: The string to print.
 * @fd: The file descriptor to print to.
 *
 * Return: The number of characters printed.
*/

int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}

