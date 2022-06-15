#include "shell.h"
/**
 * main - reads commands and executes
 * @ac: number of args
 * @av: pointer to args
 * @envp: pointer to env variables
 * Return: 0
 */

int main(int ac, char **av, char *envp[])
{
char *line = NULL, *command_args = NULL, *path = NULL;
size_t bufsize = 0;
ssize_t lsize = 0;
char **command = NULL, **path_args = NULL;
(void)envp, (void)av;

if (ac < 1)
return (-1);
signal(SIGINT, test_signal);
while (1)
{
free_buff(command);
free_buff(path_args);
free(command_args);
prompt();
lsize = getline(&line, &bufsize, stdin);
if (lsize < 0)
break;
info.ln_count++;
if (line[lsize - 1] == '\n')
line[lsize - 1] = '\0';
command = token(line);
if (command == NULL || *command == NULL || **command == '\0')
continue;
if (check(command, line))
continue;
path = get_path();
path_args = token(path);
command_args = check_path(path_args, command[0]);
if (!command_args)
perror(av[0]);
else
execute(command_args, command);
}
if (lsize < 0 && flags.interactive)
write(STDERR_FILENO, "\n", 1);
free(line);
return (0);
}
