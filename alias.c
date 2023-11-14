#include "shell.h"


/**
 * set_alias - Adds or updates an alias in the list of aliases.
 *
 * @information: A pointer to the INFO struct containing the alias list.
 * @S: The alias string to be added or updated.
 *
 * Return: 1 on failure, 0 on success.
*/

int set_alias(INFO *information, char *S)
{
	char *ptr;

	ptr = _strchr(S, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(information, S));

	unset_alias(information, S);
	return (add_node_end(&(information->alias), S, 0) == NULL);
}

/**
 * unset_alias - Removes an alias from the list of aliases.
 *
 * @inf: A pointer to the INFO struct containing the alias list.
 * @S: The alias string to be removed.
 *
 * Return: 1 if the alias was not found, 0 if removed successfully.
*/

int unset_alias(INFO *inf, char *S)
{
	char *ptr, c;
	int r;

	ptr = _strchr(S, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, S, -1)));
	*ptr = c;
	return (r);
}

/**
 * replace_alias - Replace command with an alias if a matching alias exists.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: 1 if an alias was replaced, 0 otherwise.
*/

int replace_alias(INFO *information)
{
	int i;
	LSIT *Node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		Node = node_starts_with(information->alias, information->argv[0], '=');
		if (!Node)
			return (0);
		free(information->argv[0]);
		ptr = _strchr(Node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		information->argv[0] = ptr;
	}
	return (1);
}
