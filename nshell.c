i#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

/**
 * main - Entry point
 * @ac: Input value
 * @argv: Input value
 * Return: (0) Always.
 */
int main(int ac, char **argv)
{
    char *prompt = "(eshell) $ ";
    int len = strlen(prompt);
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    char *token;
    const char *delim = "\n";
    int i = 0;
    pid_t child_pid;
    int status;
    char **args;
    char **env;


    (void)ac;

    while (1)
    {
        write(STDOUT_FILENO, prompt, len);
        nchars_read = getline(&lineptr, &n, stdin);
        if (nchars_read == -1)
        {
            write(STDOUT_FILENO, "Exiting shell ....\n", 20);
            free(lineptr);
            return (-1);
        }

        args = malloc(MAX_ARGS * sizeof(char *));
        if (args == NULL)
        {
            perror("tsh: allocation error");
            exit(EXIT_FAILURE);
        }

	token = strtok(lineptr, delim);

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
        if (strcmp(args[0], "exit") == 0)
        {
            free(args);
            free(lineptr);
            return (0);
        }
        else if (strcmp(args[0], "env") == 0)
        {
            env = environ;
            while (*env)
            {
                write(STDOUT_FILENO, *env, strlen(*env));
                write(STDOUT_FILENO, "\n", 1);
                env++;
            }
        }
        else
        {
            /*Fork a child process*/
            child_pid = fork();
            if (child_pid == -1)
            {
                perror("tsh: fork error");
            }
            else if (child_pid == 0)
            { 
                if (access(args[0], X_OK) == 0)
                                {
                                        if (execve(args[0], args, environ) == -1)
                                                perror(argv[0]);
                                }
                        else
                                {
                                        char *path = getenv("PATH");
                                        char progpath[20];
                                        int found = 0;
                                        char *token = strtok(path, ":");

                                        while (token != NULL)
                                        {
                                                strcpy(progpath, token);
                                                strcat(progpath, "/");
                                                strcat(progpath, args[0]);
                                                strcat(progpath, "\0");
                                                if (access(progpath, X_OK) == 0)
                                                {
                                                        found = 1;
                                                        break;
                                                }
                                                token = strtok(NULL, ":");
                                        }
                                        if (found)
                                        {
                                                if (execve(progpath, args, environ) == -1)
                                                        perror(argv[0]);
                                        }
                                        else
                                        {
                                                perror(argv[0]);
                                                exit(EXIT_FAILURE);
                                        }
                                }
                      
                }
            else
            {
                /* Parent process */
                if (wait(&status) == -1)
                    perror("wait failed");
            }
        }
        free(args);
        free(lineptr);
        lineptr = NULL;
        i = 0;
    }

    return (0);
}
