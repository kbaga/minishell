#include "../minishell.h"

const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

int is_builtin(const char *command)
{
	int i;
	
	i = 0;
	while (builtins[i])
	{
		if (strcmp(command, builtins[i]) == 0)
			return (1);
		i++;
	}		// Execute the command using execve
	return (0);
	
}

int execute_builtin(const char *cmd, char **args, t_env_list *env)
{
	if (strcmp(cmd, "echo") == 0) 
		return ft_echo(args);
	else if (strcmp(cmd, "cd") == 0)
		return ft_cd(args);
	else if (strcmp(cmd, "pwd") == 0)
		return ft_pwd();
	// else if (strcmp(cmd, "export") == 0)
	//     return ft_export(args);///////////
	// else if (strcmp(cmd, "unset") == 0)
	//     return ft_unset(args);///////////
	else if (strcmp(cmd, "env") == 0)
		return ft_env(env->head);
	else if (strcmp(cmd, "exit") == 0)
		return ft_exit(args);
	fprintf(stderr, "Unknown built-in command: %s\n", cmd);
	return (1);
}
