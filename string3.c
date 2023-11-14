#include "shell.h"

/**
 * _puts - Print a string to the standard output.
 *
 * @str: The string to be printed.
*/

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Write a character to a buffer or flush it.
 *
 * @c: The character to be written.
 *
 * Return: 1 if successful, otherwise 0.
*/

int _putchar(char c)
{
	static int i;
	static char buffer[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _strlen - Calculate the length of a string.
 *
 * @str: The string to calculate the length of.
 *
 * Return: The length of the string.
*/

int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - Compare two strings lexicographically.
 *
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: 0 if the strings are equal,
 * a negative value if str1 < str2,
 * or a positive value if str1 > str2.
*/

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

