#include "shell.h"

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: The destination string.
 * @src: The source string to be appended to dest.
 *
 * Return: A pointer to the destination string (dest) after concatenation.
*/

char *_strcat(char *dest, char *src)
{
	char *R = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (R);
}

/**
 * _strtok - Split a string into words using a delimiter.
 *
 * @str: The string to split.
 * @C: The delimiter used to split the string.
 *
 * Return: An array of strings containing the words from
 * the input string, or NULL on failure.
*/

char **_strtok(char *str, char *C)
{
	int i, j, k, l, Num = 0;
	char **S;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!C)
		C = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], C) && (is_delimiter(str[i + 1], C) || !str[i + 1]))
			Num++;

	if (Num == 0)
		return (NULL);
	S = malloc((1 + Num) * sizeof(char *));
	if (!S)
		return (NULL);
	for (i = 0, j = 0; j < Num; j++)
	{
		while (is_delimiter(str[i], C))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], C) && str[i + k])
			k++;
		S[j] = malloc((k + 1) * sizeof(char));
		if (!S[j])
		{
			for (k = 0; k < j; k++)
				free(S[k]);
			free(S);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			S[j][l] = str[i++];
		S[j][l] = 0;
	}
	S[j] = NULL;
	return (S);
}

/**
 * _strtok2 - Split a string into words using a character delimiter.
 *
 * @str: The string to split.
 * @C: The character delimiter used to split the string.
 *
 * Return: An array of strings containing
 * the words from the input string, or NULL on failure.
*/

char **_strtok2(char *str, char C)
{
	int i, j, k, l, Num = 0;
	char **S;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != C && str[i + 1] == C) ||
		    (str[i] != C && !str[i + 1]) || str[i + 1] == C)
			Num++;
	if (Num == 0)
		return (NULL);
	S = malloc((1 + Num) * sizeof(char *));
	if (!S)
		return (NULL);
	for (i = 0, j = 0; j < Num; j++)
	{
		while (str[i] == C && str[i] != C)
			i++;
		k = 0;
		while (str[i + k] != C && str[i + k] && str[i + k] != C)
			k++;
		S[j] = malloc((k + 1) * sizeof(char));
		if (!S[j])
		{
			for (k = 0; k < j; k++)
				free(S[k]);
			free(S);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			S[j][l] = str[i++];
		S[j][l] = 0;
	}
	S[j] = NULL;
	return (S);
}


/**
 * rep_string - Replace an old string with a new string.
 *
 * @old: A pointer to the old string.
 * @new: A pointer to the new string.
 *
 * Return: 1 if successful, 0 on failure.
*/

int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
