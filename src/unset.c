/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:11:11 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/24 17:21:36 by lakamba          ###   ########.fr       */
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

int	unset(t_shell *shell, t_lx *curr)
{
	int	fails;

	fails = 0;
	if (!shell || !curr)
	{
		shell->exit_status = 127;
		return (0); // EXIT FAILURE;
	}
	while (curr)
	{
		unset_arg(shell, curr->str, &fails);
		curr = curr->next;
	}
	if (fails > 0)
	{
		shell->exit_status = 127;
		return (0); //EXIT FAILURE;
	}
	return (1);//EXIT SUCCESS;
}
