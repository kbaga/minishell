#include "../inc/minishell.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char	*get_env_var(t_env_node *env, const char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return (env->val);
        env = env->next;
    }
    return (NULL);
}

static void	update_env_var(t_env_node *env, const char *key, const char *value)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
        {
            free(env->val);
            env->val = strdup(value);
            return;
        }
        env = env->next;
    }
}

void	handle_cd_dash(t_env *env)
{
	char	*oldpwd = get_env_var(env->head, "OLDPWD");
	char	*current_pwd;

	if (!oldpwd)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 20);
		return;
	}
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd || chdir(oldpwd) == -1)
	{
		perror("cd");
		free(current_pwd);
		return;
	}
	write(STDOUT_FILENO, oldpwd, strlen(oldpwd));
	write(STDOUT_FILENO, "\n", 1);
	update_env_var(env->head, "OLDPWD", current_pwd);
	free(current_pwd);
	current_pwd = getcwd(NULL, 0);
	update_env_var(env->head, "PWD", current_pwd);
	free(current_pwd);
}

void	ft_cd(t_env *env, char **args)
{
	char	*current_pwd;
	char	*new_pwd;

	if (!args[1])
	{
		write(STDERR_FILENO, "cd: missing argument\n", 21);
		return;
	}
	if (strcmp(args[1], "-") == 0)
		return (handle_cd_dash(env));
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd || chdir(args[1]) == -1)
	{
		perror("cd");
		free(current_pwd);
		return;
	}
	new_pwd = getcwd(NULL, 0);
	update_env_var(env->head, "OLDPWD", current_pwd);
	update_env_var(env->head, "PWD", new_pwd);
	free(current_pwd);
	free(new_pwd);
}
