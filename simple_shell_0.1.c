#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_LENGTH 1024

/**
* printPrompt - function that  prints the prompt to the standard output
* Return: Always (void)
*/
void printPrompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 10);
}

/**
* executeCommand - function that forks a child process while executing the
* command
* @command: input value
* Return: Always (void)
*/
void executeCommand(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
	perror("fork");
	exit(EXIT_FAILURE);

	}
	else if (pid == 0)
	{
	execlp(command, command, NULL);
	write(STDERR_FILENO, "#cisfun: No such file or directory: ", 38);
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
	}
	else
	{
	int status;

	waitpid(pid, &status, 0);
	}
}
/**
* main - Entry Point
* Return: Always (0) when successful
*/
int main(void)
{
	char command[MAX_LENGTH];
	ssize_t bytesRead;

	while (1)
	{
	printPrompt();
	bytesRead = read(STDIN_FILENO, command, MAX_LENGTH);

	if (bytesRead == -1)
	{
	perror("read");
	exit(EXIT_FAILURE);
	}
	else if (bytesRead == 0)
	{
	write(STDOUT_FILENO, "\n", 1);
		break;
	}

	command[strcspn(command, "\n")] = 0;
	executeCommand(command);
	}

	return (0);
}
