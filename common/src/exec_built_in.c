#include "../inc/minishell.h"

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

int execute_builtin(t_shell *shell, const char *cmd, char **args, t_env *env)
{
	(void)shell;
	if (strcmp(cmd, "echo") == 0) 
		ft_echo(args);
	else if (strcmp(cmd, "cd") == 0)
		ft_cd(args);
	else if (strcmp(cmd, "pwd") == 0)
		ft_pwd();
	// else if (strcmp(cmd, "export") == 0)
	// 	handle_export(args);///////////
	// else if (strcmp(cmd, "unset") == 0)
	// 	ft_unset(args);///////////
	else if (strcmp(cmd, "env") == 0)
		ft_env(env->head);
	// else if (strcmp(cmd, "exit") == 0)
	// 	 ft_exit(shell, shell->);
	fprintf(stderr, "Unknown built-in command: %s\n", cmd);
	return (1);
}
