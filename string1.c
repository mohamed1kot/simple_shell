#include "shell.h"


/**
 * _atoi - converts a string to an integer.
 *
 * @str: The string to convert to an integer.
 *
 * Return: The integer value of the string.
*/

int _atoi(char *str)
{
	int i, sig = 1, F = 0, out;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && F != 2; i++)
	{
		if (str[i] == '-')
			sig *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			F = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (F == 1)
			F = 2;
	}

	if (sig == -1)
		out = -result;
	else
		out = result;

	return (out);
}


/**
 * _erratoi - Convert a string to an integer, with error handling.
 *
 * @str: The string to convert to an integer.
 *
 * Return: The integer representation of the string on success,
 *         -1 if the string contains non-numeric characters or overflows.
*/

int _erratoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * _strncpy - Copy a portion of a string to another string.
 *
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string (dest).
*/

char *_strncpy(char *dest, char *src, int n)
{
	int i, k;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (str);
}

/**
 * _strncat - Concatenate a portion of one string to another string.
 *
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the destination string (dest).
*/

char *_strncat(char *dest, char *src, int n)
{
	int i, k;
	char *str = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[i] = '\0';
	return (str);
}

/**
 * _strchr - Locate the first occurrence of a character in a string.
 *
 * @str: The string to search.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 * or NULL if not found.
*/

char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

