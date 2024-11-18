/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:15:16 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/14 18:10:24 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*empty_env(t_env *env)
{
	char		cwd[1024];
	t_env_node	*pwd_node;
	t_env_node	*shlvl_node;

	if (!env)
		return (NULL);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (NULL);
	}
	pwd_node = create_node(ft_strjoin("PWD=", cwd));
	if (!pwd_node || !add_node(env, pwd_node))
	{
		node_free(pwd_node);
		return (NULL);
	}
	shlvl_node = create_node("SHLVL=1");
	if (!shlvl_node || !add_node(env, shlvl_node))
	{
		node_free(shlvl_node);
		return (NULL);
	}
	return (env);
}

t_env	*init_env(char **envp)
{
	t_env		*env;
	t_env_node	*node;
	int	i;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->head = NULL;
	if (!envp || !envp[0])
		return (empty_env(env));
	while (envp[i])
	{
		node = create_node(envp[i]);
		if (!node || !add_node(env, node))
		{
			node_free(node);
			free_env(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->environ = init_env(envp);
	if (!shell->environ)
	{
		free(shell);
		return (NULL);
	}
	shell->rl_input = NULL;
	shell->rl_copy = NULL;
	shell->lex_head = NULL;
	shell->executor = NULL;
	return (shell);
}
/*
int	main (int ac, char **av, char **envp)
{
	t_shell	*shell = init_shell(envp);

	if (!shell)
	{
		printf("Erreur lors de l'initialisation du shell\n");
		return (1);
	}
	printf("Environnement initialise: \n");
	exporting(shell, NULL);
	free_env(shell->environ);
	free(shell);

	return (0);
}
*/
