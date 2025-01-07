/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:38:53 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/18 22:15:28 by romeo            ###   ########.fr       */
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
	return (result);
}

void free_exec_node2(t_exec *node)
{
    if (!node)
        return;
    if (node->execs) {
        for (int i = 0; node->execs[i]; i++)
            free(node->execs[i]); // Libère chaque chaîne
        free(node->execs);        // Libère le tableau de chaînes
    }
    free(node); // Libère le nœud lui-même
}

void free_exec_list(t_exec *head)
{
    t_exec *tmp;

    while (head)
    {
        tmp = head->next;  // Sauvegarde le suivant
        free_exec_node2(head); // Libère le nœud actuel
        head = tmp;        // Passe au suivant
    }
}