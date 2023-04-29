#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define FALSE 0
#define TRUE 1
#define NFOT 2
#define MATCH 3
#define PREFIX 4
#define EXIT_SHELL 5
#define SKIP_FORK 6
#define DO_EXECVE 7

/**
 * struct Alias - singly linked list
 * @name: name of alias
 * @value: command that alias calls
 * @next: points to next node
 */
typedef struct Alias_lst
{
	char *key;
	char *value;
	struct Alias_lst *next;
} alias;

extern char **environ;

extern int status;

extern int line_num;

extern char *shell_name;

int process_command(char **args);

int built_ins(char **args);

int and_or(char **args, char operator, int last_compare);

char *check_command(char **args);

int execute_command(char **args);

char *sanitize_input(char *old_buf, size_t *old_size);

int check_input_error(char *ptr);

void print_error_msg(char *arg0, char *arg1);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _getline(char **line_ptr, size_t *n, int file);

char *check_var(char *arg);

int _strlen(char *str);

char *_strdup(char *src);

char *str_concat(char *s1, char *s2);

int str_comp(char *s1, char *s2, int pref_or_match);

char *get_array_element(char **array, char *element_name);

char **create_array(char *str, char delim, char **if_sep);

int _listlen(char **list, char *entry);

char **copy_array(char **old_array, int new_size);

int free_array(char **args);

int _setenv(const char *name, const char *value);

int _unsetenv(const char *name);

int _chngdir(char *name);

int alias_handler(char **args, int free);

int free_alias(alias *_alias);

int check_alias(char **args, alias *_alias);

int print_alias(alias *_alias);

int get_alias(char *arg, alias *_alias);

int set_alias(char *arg, alias *_alias, char *new_value);

int print_env(void);

char *_itos(int n);

int _stoi(char *s);

#endif
