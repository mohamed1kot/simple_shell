#include "shell.h"


/**
 * _getenv - Get the value of an environment variable.
 *
 * @information: A pointer to the INFO
 * struct containing environment information.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
*/

char *_getenv(INFO *information, const char *name)
{
	LSIT *Node = information->env;
	char *Ptr;

	while (Node)
	{
		Ptr = starts_with(Node->str, name);
		if (Ptr && *Ptr)
			return (Ptr);
		Node = Node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Set an environment variable.
 *
 * @information: A pointer to the INFO struct
 * containing environment information.
 *
 * Return: 0 on success, 1 on error.
*/

int _mysetenv(INFO *information)
{
	if (information->argc != 3)
	{
		_eputs("incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Unset one or more environment variables.
 *
 * @information: A pointer to the INFO
 * struct containing environment information.
 *
 * Return: 0 on success, 1 on error.
*/

int _myunsetenv(INFO *information)
{
	int count;

	if (information->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (count = 1; count <= information->argc; count++)
		_unsetenv(information, information->argv[count]);

	return (0);
}

