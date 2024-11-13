#include "../minishell.h"

int ft_exit(char **args)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (!args[1])
		exit(0);
	return (0); 
}
