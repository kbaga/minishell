#include "../minishell.h"

void free_exec_node(t_exec *node)
{
	if (!node)
		return;

	if (node->execs)
	{
		for (int i = 0; node->execs[i]; i++)
			free(node->execs[i]);
		free(node->execs);
	}
	free(node);
}

t_exec *create_exec_node(int id)
{
	t_exec *node;
	
	node = malloc(sizeof(t_exec));
	if (!node)	
		return NULL;
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
	

	return node;
}

void init_exec_context(t_exec_context *context, t_shell *shell)
{
	context->current_lexer = shell->lex_head;
	context->lex_head = shell->lex_head;
	context->current_exec = NULL;
	context->exec_head = NULL;
	context->exec_id = 0;
	context->lex_id = 0;
	context->fd_pipe = 0;
}
// #include <stdio.h>

// void print_tab(char **tab)
// {
//     if (!tab)
//     {
//         printf("Tab is NULL\n");
//         return;
//     }

//     for (int i = 0; tab[i] != NULL; i++)
//         printf("tab[%d]: %s\n", i, tab[i]);
// }

char **tab_command(t_exec_context *context)
{
	t_lexer_list *lexer;
	int command_count;
	char **result;

	command_count = 0;
	lexer = context->current_lexer;
	while (lexer && lexer->type == COMMAND)
	{
		command_count++;
		lexer = lexer->next;
	}
	result = malloc(sizeof(char *) * (command_count + 1));
	if (!result)
		return NULL;
	lexer = context->current_lexer; // Reset lexer to the original position
	command_count = 0;
	while (lexer && lexer->type == COMMAND)// Assign each command token to the result array
	{
		result[command_count++] = strdup(lexer->str);
		lexer = lexer->next;
	}
	result[command_count] = NULL; // Null-terminate the array
	context->current_lexer = lexer; // Update the context to the next unprocessed lexer
	return result;
}


void	assign_command(t_shell *shell, t_exec_context *context)
{
	(void)shell;
	context->current_exec->execs = tab_command(context);
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
	if (context->current_lexer->type == COMMAND)
		assign_command(shell, context);
	else
		handle_redirection(shell, context);
	if (context->current_lexer && context->current_lexer->next)
		context->current_lexer = context->current_lexer->next;
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

// t_exec *create_exec_list(t_shell *shell)
// {
// 	t_exec_context	*context;
// 	t_exec			*new_exec_node;
// 	t_exec			*result_head;

// 	context = malloc(sizeof(t_exec_context));
// 	if (!context)
// 		return (NULL);
// 	init_exec_context(context, shell);
// 	result_head = NULL;
// 	while (context->current_lexer)
// 	{
// 		if (!context->current_lexer)
// 			break ;
// 		new_exec_node = create_exec_node(context->exec_id++);
// 		if (!new_exec_node)
// 		{
// 			perror("Failed to allocate exec node");
// 			free(context);
// 			return (NULL);
// 		}
// 		if (!context->exec_head)
// 			context->exec_head = new_exec_node;
// 		else
// 			context->current_exec->next = new_exec_node;
// 		context->current_exec = new_exec_node;
// 		if (context->exec_id > 1 && context->current_lexer->prev
// 			&& context->current_lexer->prev->type == PIPE)
// 			context->current_exec->fd_in = context->fd_pipe;
// 		if (context->current_lexer->type == COMMAND)
// 			assign_command(shell, context);
// 		else if (context->current_lexer->type != COMMAND)
// 			handle_redirection(shell, context);
// 		if (context->current_lexer && context->current_lexer->next)
// 			context->current_lexer = context->current_lexer->next;
// 	}
// 	result_head = context->exec_head;
// 	free(context);
// 	return (result_head);
// }
