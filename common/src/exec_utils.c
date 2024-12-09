/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:38:53 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/05 23:39:37 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env_node *tmp;
	while (env_list->head != NULL) 
	{
		tmp = env_list->head;
		env_list->head = env_list->head->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}

void	error_command(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	command_not_found(const char *cmd)
{
	const char	*error_message;

	error_message = "Command not found: ";
	write(STDERR_FILENO, error_message, strlen(error_message));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
	return ;
}

char	**tab_command(t_exec_context *context)
{
	t_lx	*lexer;
	int		command_count;
	char	**result;

	command_count = 0;
	lexer = context->current_lexer;
	while (lexer && lexer->type == COMMAND)
	{
		command_count++;
		lexer = lexer->next;
	}
	result = malloc(sizeof(char *) * (command_count + 1));
	if (!result)
		return (NULL);
	lexer = context->current_lexer;// Reset lexer to the original position
	command_count = 0;
	while (lexer && lexer->type == COMMAND)// Assign each command token to the result array
	{
		result[command_count++] = strdup(lexer->str);
		lexer = lexer->next;
	}
	result[command_count] = NULL; // Null-terminate the array
	context->current_lexer = lexer; // Update the context to the next unprocessed lexer
	return (result);
}
