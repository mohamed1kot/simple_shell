#include "shell.h"


/**
 * pop_env_list - Populate the environment list from the 'environ' array.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: Always returns 0.
*/

int pop_env_list(INFO *information)
{
	LSIT *Node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_Node_end(&Node, environ[j], 0);
	information->env = Node;
	return (0);
}


/**
 * get_Environ - Retrieve the environment variables.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: An array of strings containing environment variables.
*/

char **get_Environ(INFO *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = LSITTo_strings(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - Unset (remove) an environment variable.
 *
 * @information: A pointer to the INFO struct.
 * @V: The name of the environment variable to unset.
 *
 * Return: 1 if the environment was changed, 0 otherwise.
*/

int _unsetenv(INFO *information, char *V)
{
	LSIT *Node = information->env;
	size_t j = 0;
	char *Ptr;

	if (!Node || !V)
		return (0);

	while (Node)
	{
		Ptr = starts_with(Node->str, V);
		if (Ptr && *Ptr == '=')
		{
			information->env_changed = del_Node_at_index(&(information->env), j);
			j = 0;
			Node = information->env;
			continue;
		}
		Node = Node->next;
		j++;
	}
	return (information->env_changed);
}

/**
 * _setenv - Set (or update) an environment variable.
 *
 * @information: A pointer to the INFO struct.
 * @V: The name of the environment variable.
 * @val: The val to set for the environment variable.
 *
 * Return: 0 if successful, 1 on failure.
*/

int _setenv(INFO *information, char *V, char *val)
{
	char *buffer = NULL;
	LSIT *Node;
	char *Ptr;

	if (!V || !val)
		return (0);

	buffer = malloc(_strlen(V) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, V);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	Node = information->env;
	while (Node)
	{
		Ptr = starts_with(Node->str, V);
		if (Ptr && *Ptr == '=')
		{
			free(Node->str);
			Node->str = buffer;
			information->env_changed = 1;
			return (0);
		}
		Node = Node->next;
	}
	add_Node_end(&(information->env), buffer, 0);
	free(buffer);
	information->env_changed = 1;
	return (0);
}

