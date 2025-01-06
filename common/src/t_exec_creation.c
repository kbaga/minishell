/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:06:45 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 18:10:19 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	assign_command(t_shell *shell, t_exec_context *c)
{
	(void)shell;
	c->current_exec->execs = tab_command(c);
	while (c->current_lexer && c->current_lexer->type == COMMAND)
		c->current_lexer = c->current_lexer->next;
}

static void	update_exec_links(t_exec_context *context, t_exec *new_exec_node)
{
	if (!context->exec_head)
		context->exec_head = new_exec_node;
	else
		context->current_exec->next = new_exec_node;
	context->current_exec = new_exec_node;
	if (context->exec_id > 1 && context->current_lexer->prev
		&& context->current_lexer->prev->type == PIPE)
		context->current_exec->fd_in = context->fd_pipe;
}

static int	process_lexer_node(t_shell *shell, t_exec_context *context)
{
	while (context->current_lexer && context->current_lexer->type != COMMAND)
		handle_redirection(shell, context);
	if (context->current_lexer->type == COMMAND)
		assign_command(shell, context);
	while (context->current_lexer && context->current_lexer->type != COMMAND)
		handle_redirection(shell, context);
	return (1);
}

t_exec	*create_exec_list(t_shell *shell)
{
	t_exec_context	*context;
	t_exec			*new_exec_node;
	t_exec			*result_head;

	context = malloc(sizeof(t_exec_context));
	if (!context)
		return (NULL);
	init_exec_context(context, shell);
	while (context->current_lexer)
	{
		new_exec_node = create_exec_node(context->exec_id++);
		if (!new_exec_node)
			break ;
		update_exec_links(context, new_exec_node);
		if (!process_lexer_node(shell, context))
			break ;
	}
	result_head = context->exec_head;
	free(context);
	return (result_head);
}
