/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:11:11 by kbaga             #+#    #+#             */
/*   Updated: 2025/01/06 15:57:56 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_var(t_shell *shell, char *arg)
{
	t_env_node	*prev;
	t_env_node	*curr;
	t_env		*env;

	if (!shell || !arg)
		return ;
	env = shell->environ;
	curr = env->head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, arg) == 0)
		{
			if (prev == NULL)
				env->head = curr->next;
			else
				prev->next = curr->next;
			node_free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	unset_arg(t_shell *shell, char *arg, int *fails)
{
	if (!shell || !arg)
		return ;
	if (!is_valid_id(arg))
	{
		(*fails)++;
		return ;
	}
	delete_var(shell, arg);
}

int	unset(t_shell *shell, char **execs)
{
	int	fails;
	int	i;

	fails = 0;
	if (!shell || !execs || !execs[0])
	{
		shell->exit_status = 127;
		return (0);
	}
	i = 0;
	while (execs[i] != NULL)
	{
		unset_arg(shell, execs[i], &fails);
		i++;
	}
	if (fails > 0)
	{
		shell->exit_status = 127;
		return (0);
	}
	shell->exit_status = 0;
	return (1);
}
