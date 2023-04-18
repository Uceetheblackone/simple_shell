0. Tread lightly, she is near
o       Should print something on stderr on failure
10. cd
Simple shell 1.0 +
Implement the builtin command cd:
•       Changes the current directory of the process.
•       Command syntax: cd [DIRECTORY]
•       If no argument is given to cd the command must be interpreted like cd $HOME
•       You have to handle the command cd -
•       You have to update the environment variable PWD when you change directory
11. ;
Simple shell 1.0 +
•       Handle the commands separator ;
12. && and ||
Simple shell 1.0 +
•       Handle the && and || shell logical operators
13. alias
Simple shell 1.0 +
•       Implement the alias builtin command
•       Usage: alias [name[='value'] ...]
o       alias: Prints a list of all aliases, one per line, in the form name='value'
o       alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
o       alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value
14. Variables
Simple shell 1.0 +
•       Handle variables replacement
•       Handle the $? variable
•       Handle the $$ variable
15. Comments
Simple shell 1.0 +
•       Handle comments (#)
16. File as input
Simple shell 1.0 +
•       Usage: simple_shell [filename]
•       Your shell can take a file as a command line argument
•       The file contains all the commands that your shell should run before exiting
•       The file should contain one command per line
•       In this mode, the shell should not print a prompt and should not read from stdin

