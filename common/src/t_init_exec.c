/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_init_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:07:38 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 18:30:59 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_exec	*create_exec_node(int id)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->id = id;
	node->size = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->trunc = 0;
	node->append = 0;
	node->redir_input = 0;
	node->heredoc = 0;
	node->path = NULL;
	node->execs = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->pipe = 0;
	return (node);
}

void	init_exec_context(t_exec_context *context, t_shell *shell)
{
	context->current_lexer = shell->lex_head;
	context->lex_head = shell->lex_head;
	context->current_exec = NULL;
	context->exec_head = NULL;
	context->exec_id = 0;
	context->lex_id = 0;
	context->fd_pipe = 0;
}

void	free_exec_node(t_exec *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->execs)
	{
		while (node->execs[i])
		{
			free(node->execs[i]);
			i++;
		}
		free(node->execs);
	}
	free(node);
}
