#include "header.h"

/**
 * _pathbuffer - finds the string to call execve on
 * @av: pointer to array of user of strings
 * @PATH: pointer to PATH string
 * @copy: pointer to copy of PATH string
 *
 * Return: a pointer to string to call execve on
 */
char *_pathbuffer(char **av, char *PATH, char *copy)
{
	char *tok, *pathbuffer = NULL, *concatstr = NULL;
	static char tmp[256];
	int pathlen = 0, pathflag = 0, /*len = 0,*/ z = 0, toklen = 0;
	struct stat h;

	copy = NULL;
	copy = _strdup(PATH);
	pathlen = _splitPath(copy);
	tok = strtok(copy, ": =");
	while (tok != NULL)
	{
		concatstr = _concat(tmp, av, tok);
		if (stat(concatstr, &h) == 0)
		{
			pathbuffer = concatstr;
			pathflag = 1;
			break;
		}
		if (z < pathlen - 2)
		{
			toklen = _strlen(tok);
			if (tok[toklen + 1] == ':')
			{
				if (stat(av[0], &h) == 0)
				{
					pathbuffer = av[0];
					pathflag = 1;
					break;
				}
			}
		}
		z++;
		tok = strtok(NULL, ":");
	}
	if (pathflag == 0)
		pathbuffer = av[0];
	free(copy);
	return (pathbuffer);
}

/**
 * _splitPath - counts the number of PATH members
 * @str: pointer to string to count
 *
 * Return: number of PATH members
 */
int _splitPath(char *str)
{
	int i;
	int searchflag = 1;
	int wordcount = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ':' && searchflag == 1)
		{
			wordcount += 1;
			searchflag = 0;
		}
		if (str[i + 1] == ':')
		{
			searchflag = 1;
		}
	}
	return (wordcount);
}

/**
 * _strcmpPath - compares PATH with environ to find PATH value
 * @s1: pointer PATH string
 * @s2: pointer to environ string with actual value
 *
 * Return: 0 on success
 */
int _strcmpPath(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s2[i] != '='; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}

/**
 * checkbuiltins - check if first user string is a built-in
 * @av: pointer to array of user of strings
 * @buffer: pointer to user string
 * @exitstatus: exit status of execve
 * Return: 1 if user string is equal to env or 0 otherwise
 */
int checkbuiltins(char **av, char *buffer, int exitstatus)
{
	int i;

	if (_strcomp(av[0], "env") == 0)
	{
		_env();
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
		free(buffer);
		return (1);
	}
	else if (_strcomp(av[0], "exit") == 0)
	{
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
		free(buffer);
		exit(exitstatus);
	}
	else
		return (0);
}

/**
 * _forkprocess - create child process to execute based on user input
 * @av: pointer to array of user of strings
 * @buffer: pointer to user string
 * @pathbuffer: pointer to user input
 *
 * Return: 0 on success
 */
int _forkprocess(char **av, char *buffer, char *pathbuffer)
{
	int i, status, result, exitstatus = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
	{
		result = execve(pathbuffer, av, environ);
		if (result == -1)
		{
			perror(av[0]);
			for (i = 0; av[i]; i++)
				free(av[i]);
			free(av);
			free(buffer);
			exit(127);
		}
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
	}
	for (i = 0; av[i]; i++)
		free(av[i]);
	free(av);
	free(buffer);
	return (exitstatus);
}

