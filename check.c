#include "shell.h"

/**
 * is_delim - checks if a character is a delimiter.
 *
 * @count: The character to check.
 * @delimater: A string containing delimiter characters.
 *
 * Return: Returns 1 if the character is a delimiter; otherwise, returns 0.
*/

int is_delim(char count, char *delimater)
{
	while (*delimater)
		if (*delimater++ == count)
			return (1);
	return (0);
}


/**
 * _isalpha - checks if a character is an alphabetic character.
 *
 * @i: The character to check.
 *
 * Return: Returns 1 if the character is an alphabetic character;
 * otherwise, returns 0.
*/

int _isalpha(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_cmd - Check if a PATH points to an executable command.
 *
 * @information: A pointer to the INFO struct.
 * @PATH: The PATH to be checked.
 *
 * Return: 1 if the PATH is an executable command, 0 if not.
*/

int is_cmd(INFO *information, char *PATH)
{
	struct stat ST;

	(void)information;
	if (!PATH || stat(PATH, &ST))
		return (0);

	if (ST.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * is_chain - Check if a command buffer contains a chaining operator.
 *
 * @information: A pointer to the INFO struct.
 * @buffer: The command buffer to check.
 * @Ptr: A pointer to the current position in the buffer.
 *
 * Return: 1 if a chaining operator is found, 0 otherwise.
*/

int is_chain(INFO *information, char *buffer, size_t *Ptr)
{
	size_t j = *Ptr;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = C_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = C_and;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		information->cmd_buf_type = C_chin;
	}
	else
		return (0);
	*Ptr = j;
	return (1);
}


/**
 * check_chain - Check and process chaining operators.
 *
 * @inf: A pointer to the INFO struct.
 * @buff: The command buffer to check.
 * @Ptr: A pointer to the current position in the buffer.
 * @i: The current position in the buffer.
 * @len: The length of the buffer.
*/

void check_chain(INFO *inf, char *buff, size_t *Ptr, size_t i, size_t len)
{
	size_t j = *Ptr;

	if (inf->cmd_buf_type == C_and)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == C_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*Ptr = j;
}

