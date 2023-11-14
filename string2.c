#include "shell.h"

/**
 * dup_chars - Duplicate a portion of a character string.
 *
 * @str: The source string.
 * @start: The starting index of the portion to duplicate.
 * @end: The index at which to end duplicating.
 *
 * Return: A dynamically allocated string containing the duplicated portion.
*/

char *dup_chars(char *str, int start, int end)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < end; i++)
		if (str[i] != ':')
			buffer[j++] = str[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * _memset - Fill memory with a constant byte.
 *
 * @s: A pointer to the memory area to fill.
 * @c: The byte to fill the memory area with.
 * @n: The number of bytes to fill.
 *
 * Return: A pointer to the memory area @s.
*/

char *_memset(char *s, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = c;
	return (s);
}
/**
 * _strcpy - Copy a string from source to destination.
 *
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: The destination buffer after copying the source string.
*/

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Duplicate a string in a new memory location.
 *
 * @str: The source string to duplicate.
 *
 * Return: A dynamically allocated string with
 * a duplicate of the source string, or NULL on failure.
*/

char *_strdup(const char *str)
{
	int len = 0;
	char *R;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	R = malloc(sizeof(char) * (len + 1));
	if (!R)
		return (NULL);
	for (len++; len--;)
		R[len] = *--str;
	return (R);
}

