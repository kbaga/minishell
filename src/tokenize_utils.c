/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:11:39 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/16 01:34:49 by lakamba          ###   ########.fr       */
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

	if (!array || !array[i])
	{
		printf("ERROR: chaine vide ou NULL array[%d]", i);
		return (NULL);
	}

	if (i < 0 || array[i][0] == '\0') {
        fprintf(stderr, "ERROR: Index invalide ou chaîne vide à index %d\n", i);
        return (NULL);
    }
	new_node = malloc(sizeof(t_lx));
	if (!new_node)
		return (NULL);
	if (!array[i])
	{
		printf("ERROR: array[%d] est NULL\n", i);
		free(new_node);
		return (NULL);
	}
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
