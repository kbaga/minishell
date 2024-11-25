/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:11:39 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/25 19:42:37 by lakamba          ###   ########.fr       */
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
	if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	if (ft_strchr(s, '>') != NULL)
		return (TRUNCATE);
	if (ft_strchr(s, '<') != NULL)
		return (REDIRECT_INPUT);
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	return (COMMAND);
}

t_lx	*create_token(char **array, t_lx *curr, int i)
{
	t_lx	*new_node;

	if (!array || !array[i] || array[i][0] == '\0')
		return (NULL);
	new_node = malloc(sizeof(t_lx));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(array[i]);
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->prev = curr;
	new_node->next = NULL;
	new_node->index = i;
	new_node->type = which_type(new_node->str);
	return (new_node);
}
