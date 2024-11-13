/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:11:11 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/11 20:08:54 by kbaga            ###   ########.fr       */
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

int	unset(t_shell *shell, char **args)
{
	int	i;
	int	fails;

	i = 0;
	fails = 0;
	if (!shell || !args)
		return (0); //EXIT FAILURE;
	while (args[i])
	{
		unset_arg(shell, args[i], &fails);
		i++;
	}
	if (fails > 0)
		return (0); //EXIT FAILURE;
	return (1);//EXIT SUCCESS;
}
