#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 64
char **get_tokens(int nchars_read, char *lineptr, size_t *n, char **args);
void exec_cmd(pid_t child_pid, char **args, char **argv,
			  int status, char **envp);
int make_path(char *progpath, char *token, char **args);
/**
 * main - Entry point
 * @ac: Input value
 * @argv: Input value
 * @envp: envpment var
 * Return: (0) Always.
 */
int main(int ac, char **argv, char **envp)
{
	char *prompt = "(eshell) $ ", *lineptr = NULL;
	int len = strlen(prompt), status = 0;
	size_t n = 0, nchars_read = 0;
	char **args, **env;
	pid_t child_pid = 0;

	(void)ac;
	while (1)
	{
		if (isatty(0) != 0)
			write(STDOUT_FILENO, prompt, len);
		args = get_tokens(nchars_read, lineptr, &n, args);
		if (strcmp(args[0], "exit") == 0)
			return (free(args), free(lineptr), 0);
		else if (strcmp(args[0], "env") == 0)
		{
			env = envp;
			while (*env)
			{
				write(STDOUT_FILENO, *env, strlen(*env));
				write(STDOUT_FILENO, "\n", 1);
				env++;
			}
		}
		else
			exec_cmd(child_pid, args, argv, status, envp);
		free(args);
		free(lineptr);
		lineptr = NULL;
	}

	return (0);
}

/**
 * get_tokens - gets the tokens
 * @nchars_read: num chars read
 * @lineptr: lineptr
 * @args: arguments
 * @n: space allocated
 *
 * Return: Array of strings
 */
char **get_tokens(int nchars_read, char *lineptr, size_t *n, char **args)
{
	char *token;
	char *delim = " \n";
	int i;

	nchars_read = getline(&lineptr, n, stdin);
	if (nchars_read == -1)
	{
		free(lineptr);
		exit(errno);
	}

	args = malloc(MAX_ARGS * sizeof(char *));
	if (args == NULL)
	{
		perror("tsh: allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(lineptr, delim);

	i = 0;
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " \n");
		i++;
		if (i == MAX_ARGS)
		{
			break;
		}
	}
	args[i] = NULL;
	return (args);
}

/**
 * exec_cmd - execute command
 * @child_pid: child process
 * @args: argument to tokenize
 * @argv: command line params
 * @status: process status
 * @envp: environment variables
 *
 * Return: void
 */
void exec_cmd(pid_t child_pid, char **args, char **argv,
			  int status, char **envp)
{
	child_pid = fork();
	if (child_pid == -1)
		perror("tsh: fork error");
	else if (child_pid == 0)
	{
		if (access(args[0], X_OK) == 0)
		{
			if (execve(args[0], args, envp) == -1)
				perror(argv[0]);
			else
			{
				char *path = getenv("PATH"), progpath[20];
				int found = 0;
				char *token = strtok(path, ":");

				while (token != NULL)
				{
					int a = make_path(progpath, token, args);

					if (a == 1)
						break;
					token = strtok(NULL, ":");
				}
				if (found)
				{
					if (execve(progpath, args, envp) == -1)
						perror(argv[0]);
					else
					{
						perror(argv[0]);
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
	else if (wait(&status) == -1)
		perror("wait failed");
}

/**
 * make_path - make path to try
 * @progpath: end path to make
 * @token: token to use
 * @args: args to use
 *
 * Return: int
 */
int make_path(char progpath[], char *token, char **args)
{
	strcpy(progpath, token);
	strcat(progpath, "/");
	strcat(progpath, args[0]);
	strcat(progpath, "\0");

	if (access(progpath, X_OK) == 0)
	{
		return (1);
	}
	return (0);
}
