#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024
/**
 * get_path - function to execute a path command
 * @cmd: Input value
 * Return:(cmd_path) while token is  not NULL
 * NULL when access is 0
 */
char *get_path(char *cmd)
{
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        char *token = strtok(path_copy, ":");
        size_t cmd_path_len = strlen(token) + strlen(cmd) + 2;
        char *cmd_path = malloc(cmd_path_len);

        while (token != NULL)
        {
                strncpy(cmd_path, token, cmd_path_len);
                strncat(cmd_path, "/", cmd_path_len - strlen(cmd_path) - 1);
                strncat(cmd_path, cmd, cmd_path_len - strlen(cmd_path) - 1);

                if (access(cmd_path, X_OK) == 0)
                {
                        free(path_copy);
                        return (cmd_path);
                }

                token = strtok(NULL, ":");
        }
        free(cmd_path);
        free(path_copy);
        return (NULL);
}
/**
 * execute_command - function that executes command in a program
 * @args: Input value
 * Return: (void)
 */
void execute_command(char **args)
{
        char *cmd = args[0];
        char *cmd_path = get_path(cmd);
        pid_t pid;

        if (cmd_path == NULL)
        {
                write(STDERR_FILENO, cmd, strlen(cmd));
                write(STDERR_FILENO, ": no command\n", strlen(": no command\n"));
                return;
        }

        pid = fork();

        if (pid == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
                execv(cmd_path, args);
                perror("execv");
                exit(EXIT_FAILURE);
        }
        else
        {
                int status;

                waitpid(pid, &status, 0);
        }
        free(cmd_path);
}
/**
 * main - Entry Point
 * Return: (0) when successful
 */
int main(void)
{
        char command[MAX_LENGTH];
        ssize_t bytes_read;
        char *args[MAX_LENGTH];
        int arg_count = 0;
        char *token = strtok(command, "\n");

        while (1)
        {
                write(STDOUT_FILENO, "$ ", 2);
                bytes_read = read(STDIN_FILENO, command, MAX_LENGTH);

                if (bytes_read == -1)
                {
                        perror("read");
                        exit(EXIT_FAILURE);
                }
                else if (bytes_read == 0)
                {
                        write(STDOUT_FILENO, "\n", 1);
                        break;
                }

                while (token != NULL)
        {
                args[arg_count++] = token;
                token = strtok(NULL, " \n");
        }
        args[arg_count] = NULL;

        if (arg_count > 0)
        {
                execute_command(args);
        }
        }

return (0);
}
