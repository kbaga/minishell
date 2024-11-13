/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:17:38 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/08 17:52:14 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_var(t_shell *shell, char **s, t_exp *exp, int i)
{
	char	var_name[256];
	int		var_len;
	char	*var_val;

	var_len = 0;
	i++;
	while ((*s)[i] && ((*s)[i] != ' ' && (*s)[i] != '$'
			&& (*s)[i] != '\'' && (*s)[i] != '\"' && var_len < 255))
		var_name[var_len++] = (*s)[i++];
	var_name[var_len] = '\0';
	var_val = getenv(var_name);
	if (!var_val)
		var_val = "";
	exp->res = ft_join_exp(exp->res, var_val);
	if (!exp->res)
		return (-1);
	return (i);
}

//RISQUE DE LEAKS DANS EXP s
int	expander(t_shell *shell)
{
	t_exp	*exp;
	int		i;

	if (!shell || !shell->rl_copy)
		return (0);
	i = 0;
	exp = init_exp(shell->rl_copy);
	while (exp->str[i] != '\0')
	{
		if (exp->str[i] == '$')
			i = expand_var(shell, &shell->rl_copy, exp, i);
		else
		{
			if (!handle_char(exp, exp->str[i]))
				return (0);
			i++;
		}	
		if (i == -1)
			return (0);
	}
	free(shell->rl_copy);
	shell->rl_copy = ft_strdup(exp->res);
	free_exp(exp);
	return (1);
}

/*
t_env	*init_env()
{
	t_env	*env = malloc(sizeof(t_env));
	t_env_node *user = malloc(sizeof(t_env_node));
	user->key = ft_strdup("USER");
	user->val = ft_strdup("kbaga");
	user->next = NULL;
	env->head = user;
	return env;
}

void	free_env(t_env *env)
{
	t_env_node *node = env->head;
	while (node)
	{
		t_env_node *temp = node;
		node = node->next;
		free(temp->key);
		free(temp->val);
		free(temp);
	}
	free(env);
}

int	main()
{
	t_shell	shell;
	shell.environ = init_env();
	shell.rl_input = ft_strdup("echo hello, $SYSTEMD_EXEC_PID");
	shell.rl_copy = ft_strdup(shell.rl_input);
	printf("BEFORE EXPANDER : %s \n", shell.rl_input);
	if (expander(&shell))
	{
		printf("Expanded command: %s\n", shell.rl_copy);
	}
	else
		printf("Expansion failed.\n");
	free(shell.rl_input);
	free(shell.rl_copy);
	free_env(shell.environ);
	return (0);
}
*/
