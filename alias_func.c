#include "shell.h"

int status;

/**
 * free_alias - frees all aliases
 * @_alias: ptr to head of alias list
 *
 * Return: TRUE
 */
int free_alias(alias *_alias)
{
	alias *tmp;

	while (_alias != NULL)
	{
		tmp = _alias;
		_alias = _alias->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}

	return (TRUE);
}

/**
 * check_alias - this will check if the command is an alias,
 * and if so replace it with it's value
 * @args: argument to be checked
 * @_alias: pointer to the list of aliases
 *
 * Return: TRUE
 */
int check_alias(char **args, alias *_alias)
{
	while (_alias != NULL)
	{
		if (str_comp(*args, _alias->key, MATCH) == TRUE)
		{
			*args = _strdup(_alias->value);
			return (DO_EXECVE);
		}
		_alias = _alias->next;
	}
	return (TRUE);
}

/**
 * print_alias - prints all aliases in list
 * @_alias: pointer to the list of aliases
 *
 * Return: SKIP_FORK
 */
int print_alias(alias *_alias)
{
	while (_alias != NULL)
	{
		write(STDOUT_FILENO, _alias->key, _strlen(_alias->key));
		write(STDOUT_FILENO, "=\'", 2);
		write(STDOUT_FILENO, _alias->value,
				_strlen(_alias->value));
		write(STDOUT_FILENO, "\'\n", 2);
		_alias = _alias->next;
	}
	return (SKIP_FORK);
}

/**
 * get_alias - prints the value of a particular alias
 * @arg: alias key
 * @_alias: points to list of aliases
 *
 * Return: TRUE if valid alias, FALSE if not
 */
int get_alias(char *arg, alias *_alias)
{
	while (_alias != NULL)
	{
		fflush(stdin);
		if (str_comp(arg, _alias->key, MATCH) == TRUE)
		{
			write(STDOUT_FILENO, arg, _strlen(arg));
			write(STDOUT_FILENO, "=\'", 2);
			write(STDOUT_FILENO, _alias->value,
					_strlen(_alias->value));
			write(STDOUT_FILENO, "\'\n", 2);
			return (TRUE);
		}
		_alias = _alias->next;
	}

	status = 1;
	write(STDERR_FILENO, "alias: ", 7);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, " not found\n", 11);

	return (FALSE);
}

/**
 * set_alias - Set or reset an alias value
 * @arg: alias key
 * @_alias: pointer to list of aliases
 * @_value: value of alias to be set
 *
 * Return: TRUE
 */
int set_alias(char *arg, alias *_alias, char *_value)
{
	while (_alias->next != NULL
			&& str_comp(_alias->key, arg, MATCH) != TRUE)
	{
		_alias = _alias->next;
	}

	if (str_comp(_alias->key, arg, MATCH) == TRUE)
	{
		free(_alias->value);
	}
	else
	{
		_alias->next = malloc(sizeof(alias *));
		_alias = _alias->next;
		if (_alias == NULL)
			exit(EXIT_FAILURE);

		_alias->key = _strdup(arg);
		_alias->next = NULL;
	}
	_alias->value = _strdup(_value);

	return (TRUE);
}
