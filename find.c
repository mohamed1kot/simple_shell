#include "shell.h"


/**
 * find_PATH - Find the full PATH to an executable command.
 *
 * @information: A pointer to the INFO struct.
 * @pathstr: The PATH string containing colon-separated directories.
 * @C: The name of the command to find.
 *
 * Return: A dynamically allocated string with
 * the full PATH to the command if found, or NULL if not found.
*/

char *find_PATH(INFO *information, char *pathstr, char *C)
{
	int i = 0, curr_pos = 0;
	char *PATH;

	if (!pathstr)
		return (NULL);
	if ((_strlen(C) > 2) && starts_with(C, "./"))
	{
		if (is_Cmd(information, C))
			return (C);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			PATH = dup_chars(pathstr, curr_pos, i);
			if (!*PATH)
				_strcat(PATH, C);
			else
			{
				_strcat(PATH, "/");
				_strcat(PATH, C);
			}
			if (is_Cmd(information, PATH))
				return (PATH);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * f_builtin - Find and execute built-in commands.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: The return value of
 * the executed built-in command or -1 if not found.
*/

int f_builtin(INFO *information)
{
	int i, built_in_ = -1;
	builtin_t builtintbl[] = {
		{"exit", _Myexit},
		{"env", _Myenv},
		{"help", _Myhelp},
		{"history", _Myhistory},
		{"setenv", _Mysetenv},
		{"unsetenv", _Myunsetenv},
		{"cd", _Mycd},
		{"alias", _Myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(information->argv[0], builtintbl[i].type) == 0)
		{
			information->line_count++;
			built_in_ = builtintbl[i].func(information);
			break;
		}
	return (built_in_);
}

/**
 * find_cmd - Find and execute external commands.
 *
 * @inf: A pointer to the INFO struct.
*/

void find_cmd(INFO *inf)
{
	char *PATH = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_delimiter(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	PATH = find_PATH(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (PATH)
	{
		inf->path = PATH;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_Cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			P_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - Fork a child process to execute an external command.
 *
 * @inf: A pointer to the INFO struct.
*/

void fork_cmd(INFO *inf)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(inf->path, inf->argv, get_Environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				P_error(inf, "Permission denied\n");
		}
	}
}

