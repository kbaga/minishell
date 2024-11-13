#include "../minishell.h"

int ft_cd(char **args)
{
	if (!args[1])
	{
		write(STDERR_FILENO, "cd: missing argument\n", 21);
		return 1;
	}
	if (args[1][0] != '/' && strcmp(args[1], "..") != 0 
		&& strncmp(args[1], "../", 3) != 0 
		&& strncmp(args[1], "./", 2) != 0)
	{
		write(STDERR_FILENO, "cd: only relative or absolute paths allowed\n", 44);
		return 1;
	}
	if (chdir(args[1]) == -1) {
		perror("cd");
		return 1;
	}
	return (0);
}
