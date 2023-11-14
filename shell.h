#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

#define BUF_SIZE 1024
#define BUF_FLUSH -1

#define C_NOR	0
#define C_OR	1
#define C_and	2
#define C_chin	3

#define conv_lower	1
#define conv_unsign	2

#define U_getline 0
#define U_strtok 0

#define f_histroy	".simple_shell_history"
#define M_history	4096
#define info_int \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct list_s - A structure representing a linked list node.
 *
 * @num: An integer value associated with the node.
 * @str: A string value associated with the node.
 * @next: A pointer to the next node in the linked list.
 *
 * Description: This structure is used to create a linked list
 *              where each node contains an integer value, a string
 *              value, and a pointer to the next node in the list.
*/

typedef struct list_s
{
	int num;
	char *str;
	struct list_s *next;
} LSIT;

/**
 * struct PASS - A structure representing information related to the shell.
 * @arg: The argument string entered by the user.
 * @argv: An array of strings representing command arguments.
 * @path: The path associated with the command.
 * @argc: The count of command arguments.
 * @line_count: The line number of the input.
 * @err_num: An error number associated with the command.
 * @linecount_flag: A flag indicating whether line counting is active.
 * @fname: The name of the shell executable.
 * @env: A linked list representing the environment variables.
 * @history: A linked list representing the command history.
 * @alias: A linked list representing command aliases.
 * @environ: An array of strings representing the environment variables.
 * @env_changed: A flag indicating whether the environment has changed.
 * @status: The status of the last executed command.
 * @cmd_buf: An array of strings representing the command buffer.
 * @cmd_buf_type: The type of command buffer (e.g., AND, OR, NORMAL).
 * @readfd: The file descriptor for reading input.
 * @histcount: The count of command history entries.
 *
 * Description: This structure holds information related to the shell,
 *              including command details, environment variables, history,
 *              and other related information.
*/

typedef struct PASS
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	LSIT *env;
	LSIT *history;
	LSIT *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} INFO;

/**
 * struct BULITIN - A structure representing a built-in command.
 *
 * @type: The name of the built-in command.
 * @func: A function pointer to the corresponding built-in function.
 *
 * Description: This structure associates a built-in command name with
 *              its corresponding function pointer for execution in the shell.
*/

typedef struct BULITIN
{
	char *type;
	int (*func)(INFO *);
} builtin_t;


ssize_t in_buf(INFO *information, char **buffer, size_t *length);
ssize_t get_in(INFO *information);
ssize_t read_buffer(INFO *information, char *buffer, size_t *i);
int _getline(INFO *information, char **pointer, size_t *length);
void *_realloc(void *pointer, unsigned int o_size, unsigned int N_size);
int set_alias(INFO *information, char *S);
int unset_alias(INFO *information, char *S);
int rep_alias(INFO *information);
int _Myalias(INFO *information);
int _Myexit(INFO *information);
int _Mycd(INFO *information);
int _Myhelp(INFO *information);
int _Myenv(INFO *information);
char *_getenv(INFO *information, const char *name);
int _Mysetenv(INFO *information);
int _Myunsetenv(INFO *information);
int is_delimiter(char count, char *delimater);
int _isAlpha(int i);
int is_Cmd(INFO *information, char *PATH);
int is_Chain(INFO *information, char *buffer, size_t *Ptr);
void Check_chain(INFO *inf, char *buff, size_t *Ptr, size_t i, size_t len);
int pop_env_list(INFO *information);
char **get_Environ(INFO *information);
int _unsetenv(INFO *information, char *V);
int _setenv(INFO *information, char *V, char *val);
char *find_PATH(INFO *information, char *pathstr, char *C);
int f_builtin(INFO *information);
void find_cmd(INFO *information);
void fork_cmd(INFO *information);
int bfree(void **P);
void free_info(INFO *information, int A);
void ffree(char **P);
void sig_Handler(__attribute__((unused))int sigin_num);
int _Myhistory(INFO *indormation);
char *get_history_file(INFO *indormation);
int w_history(INFO *indormation);
int R_history(INFO *indormation);
int build_history_list(INFO *information, char *buffer, int L_count);
int renumber_history(INFO *information);
int interactive(INFO *information);
LSIT *Node_starts_with(LSIT *Node, char *pre, char c);
ssize_t get_Node_index(LSIT *head, LSIT *Node);
LSIT *add_Node(LSIT **head, const char *S, int number);
LSIT *add_Node_end(LSIT **head, const char *str, int number);
int del_Node_at_index(LSIT **head, unsigned int idx);
void f_list(LSIT **head_P);
size_t list_len(const LSIT *head);
char **LSITTo_strings(LSIT *head);
int main(int argc, char **argv);
int P_alias(LSIT *Node);
void P_error(INFO *information, char *e_str);
int print_d(int input, int fd);
size_t P_list(const LSIT *head);
size_t P_list_str(const LSIT *head);
void _eputs(char *str);
int _eputchar(char C);
int _putfd(char C, int fd);
int _putsfd(char *str, int fd);
void rem_comments(char *buffer);
void clear_information(INFO *information);
int _atoi(char *str);
int _eatoi(char *str);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *str, char c);
char *dup_chars(char *str, int start, int end);
char *_memset(char *s, char c, unsigned int n);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
int rep_string(char **old, char *new);
char **_strtok2(char *str, char C);
char **_strtok(char *str, char *C);
char *_strcat(char *dest, char *src);
char *convert_number(long int number, int base, int flag);
void set_info(INFO *information, char **av);
int hsh(INFO *information, char **av);
char *starts_with(const char *stack, const char *needle);
int rep_var(INFO *information);


#endif
