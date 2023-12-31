#include "shell.h"

/**
 * _Myalias - Handles the 'alias' command.
 *
 * @inf: A pointer to the INFO struct containing the alias list.
 *
 * Return: 0 on success.
*/

int _Myalias(INFO *inf)
{
	int i = 0;
	char *ptr = NULL;
	LSIT *Node = NULL;

	if (inf->argc == 1)
	{
		Node = inf->alias;
		while (Node)
		{
			P_alias(Node);
			Node = Node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		ptr = _strchr(inf->argv[i], '=');
		if (ptr)
			set_alias(inf, inf->argv[i]);
		else
			P_alias(Node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}

/**
 * _Myexit - Handles the 'exit' command to terminate the shell.
 *
 * @information: A pointer to the INFO struct that holds command information.
 *
 * Return: -2 to indicate the shell should exit, or 1 if an error occurs.
*/

int _Myexit(INFO *information)
{
	int endcheck;

	if (information->argv[1])
	{
		endcheck = _eatoi(information->argv[1]);
		if (endcheck == -1)
		{
			information->status = 2;
			P_error(information, "illegal num: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _eatoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _Mycd - Handles the 'cd' command to change the current directory.
 *
 * @information: A pointer to the INFO struct
 * containing command and environment information.
 *
 * Return: 0 on success, 1 on certain error conditions.
*/

int _Mycd(INFO *information)
{
	char *s, *D, buffer[1024];
	int _chdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		D = _getenv(information, "HOME=");
		if (!D)
			_chdir =
				chdir((D = _getenv(information, "PWD=")) ? D : "/");
		else
			_chdir = chdir(D);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		_chdir =
			chdir((D = _getenv(information, "OLDPWD=")) ? D : "/");
	}
	else
		_chdir = chdir(information->argv[1]);
	if (_chdir == -1)
	{
		P_error(information, "can't cd to ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _Myhelp - Handles the 'help' command (currently unimplemented).
 *
 * @information: A pointer to the INFO struct that holds command information.
 *
 * Return: Always returns 0.
*/

int _Myhelp(INFO *information)
{
	char **arg_arr;

	arg_arr = information->argv;
	_puts("Help call works Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}

/**
 * _Myenv - Displays the environment variables.
 *
 * @information: A pointer to the INFO
 * struct containing environment information.
 *
 * Return: Always returns 0.
*/

int _Myenv(INFO *information)
{
	P_list_str(information->env);
	return (0);
}

