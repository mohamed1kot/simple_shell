#include "shell.h"


/**
 * rem_comments - Remove comments from a string.
 *
 * @buffer: The input string that may contain comments.
*/

void rem_comments(char *buffer)
{
	int count;

	for (count = 0; buffer[count] != '\0'; count++)
		if (buffer[count] == '#' && (!count || buffer[count - 1] == ' '))
		{
			buffer[count] = '\0';
			break;
		}
}


/**
 * clear_information - Clear information in the INFO struct.
 *
 * @information: A pointer to the INFO struct to be cleared.
*/

void clear_information(INFO *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}
