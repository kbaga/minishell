/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:48:49 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/24 00:38:36 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_id(char *arg)
{
	if (!is_valid(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (0);
	}
	return (1);
}

int	create_add(t_shell *shell, char *args)
{
	t_env_node	*node;
	t_env		*env;

	env = shell->environ;
	node = malloc(sizeof(t_env_node));
	if (!node || !ext_val(args, node))
	{
		node_free(node);
		return (0);
	}
	if (!add_node(env, node))
	{
		node_free(node);
		return (0);
	}
	return (1);
}

void	free_env(t_env *env)
{
	t_env_node	*current;
	t_env_node	*temp;

	current = env->head;
	while (current)
	{
		temp = current;
		current = current->next;
		node_free(temp);
	}
	free(env);
}

// void	handle_exit_status(char **token, int exit_status)
// {
// 	char 	*exit_code;

// 	exit_code = ft_itoa(exit_status);
// 	if (!exit_code)
// 		return ;
// 	//*input += 2;
// 	free(*token);
// 	*token = exit_code;
// }