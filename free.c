#include "shell.h"


/**
 * free_info - Free memory and resources associated with the INFO struct.
 *
 * @information: A pointer to the INFO struct.
 * @A: A flag indicating whether to free A resources
 * (1) or only specific resources (0).
*/

void free_info(INFO *information, int A)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (A)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			f_list(&(information->env));
		if (information->history)
			f_list(&(information->history));
		if (information->alias)
			f_list(&(information->alias));
		ffree(information->environ);
			information->environ = NULL;
		bfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}


/**
 * bfree - Free a pointer and set it to NULL.
 *
 * @P: A pointer to a pointer to be freed.
 *
 * Return: 1 if the pointer is successfully freed
 * and set to NULL, 0 if the pointer is NULL.
*/

int bfree(void **P)
{
	if (P && *P)
	{
		free(*P);
		*P = NULL;
		return (1);
	}
	return (0);
}

/**
 * ffree - Free a NULL-terminated array of pointers and set them to NULL.
 *
 * @P: A pointer to a NULL-terminated array of pointers.
*/

void ffree(char **P)
{
	char **a = P;

	if (!P)
		return;
	while (*P)
		free(*P++);
	free(a);
}
