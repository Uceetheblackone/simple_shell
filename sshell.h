#ifndef _SSHELL_H_
#define _SSHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LENGTH 1024

int _putchar(char);
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);

void printPrompt(void);
void executeCommand(const char *command);


#endif
