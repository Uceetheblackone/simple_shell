#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024

/**
* executeCommand - forks a child process while executing
* the command with arguments
* @command: The command to execute
* @args: The array of arguments for the command
* Return: Always (void)
*/
void executeCommand(char *command, char *args[])
{
        char *envp[] = { NULL };
        pid_t pid = fork();

        if (pid == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
                execve(command, args, envp);
                perror("execve");
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
        char *args[MAX_LENGTH];
        char *token = strtok(command, " ");
        int i = 0;

        while (1)
        {
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

                while (token != NULL)
                {
                        args[i++] = token;
                        token = strtok(NULL, "\n");
                }
                args[i] = NULL;

                executeCommand(args[0], args);
        }
        return (0);
}
