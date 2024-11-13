/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:11:39 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/08 18:20:28 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	assign_type(char tok)
{
	if (tok == '|')
		return (PIPE);
	else if (tok == '>')
		return (TRUNCATE);
	else if (tok == '<')
		return (REDIRECT_INPUT);
	else
		return (COMMAND);
}

t_token	which_type(char *s)
{
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(s, ">") == 0)
		return (TRUNCATE);
	else if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(s, "<") == 0)
		return (REDIRECT_INPUT);
	else if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	else
		return (COMMAND);
}

t_lx	*create_token(char **array, t_lx *curr, int i)
{
	t_lx	*new_node;

	if (!array[i])
		return (NULL);
	new_node = malloc(sizeof(t_lx));
	if (new_node == NULL)
	{
		perror("Failed alloc");
		exit(1);
	}
	new_node->str = ft_strdup(array[i]);
	new_node->type = which_type(array[i]);
	new_node->index = i;
	new_node->is_command = (new_node->type == COMMAND);
	new_node->prev = curr;
	new_node->next = NULL;
	return (new_node);
}
