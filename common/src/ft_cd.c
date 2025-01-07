#include "../inc/minishell.h"

// void	ft_cd(char **args)
// {
// 	if (!args[1])
// 	{
// 		write(STDERR_FILENO, "cd: missing argument\n", 21);
// 		return;
// 	}
// 	if (args[1][0] != '/' && strcmp(args[1], "..") != 0 
// 		&& strncmp(args[1], "../", 3) != 0 
// 		&& strncmp(args[1], "./", 2) != 0)
// 	{
// 		write(STDERR_FILENO, "cd: only relative or absolute paths allowed\n", 44);
// 		return;
// 	}
// 	if (chdir(args[1]) == -1)
// 		perror("cd");
// 	return;
// }

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	update_env_var(char *key, char *value);
char	*get_env_var(const char *key);
void	print_error(const char *msg);

void	ft_cd(char **args)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!args[1])
		return (print_error("cd: missing argument\n"));
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd"));
	if (strcmp(args[1], "-") == 0)
	{
		new_pwd = get_env_var("OLDPWD");
		if (!new_pwd)
			return (free(old_pwd), print_error("cd: OLDPWD not set\n"));
		if (chdir(new_pwd) == -1)
			return (free(old_pwd), perror("cd"));
	}
	else if (chdir(args[1]) == -1)
		return (free(old_pwd), perror("cd"));
	update_env_var("OLDPWD", old_pwd);
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		update_env_var("PWD", new_pwd);
	free(new_pwd);
}

void	update_env_var(char *key, char *value)
{
	if (!key || !value)
		return ;
	setenv(key, value, 1);
}

char	*get_env_var(const char *key)
{
	return (getenv(key));
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, msg, strlen(msg));
}

