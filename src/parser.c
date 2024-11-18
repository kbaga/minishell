/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:31:25 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/16 01:52:46 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	check_pipe(t_lx *lexer)
{
	t_lx	*curr;

	curr = lexer;
	if (!lexer)
		return (0);
	while (curr != NULL)
	{
		if (curr->type == PIPE)
		{
			if (curr->prev == NULL
				|| curr->prev->type == PIPE)
				return (0);
			if (curr->next == NULL
				|| curr->next->type == PIPE)
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
t_lx	*lexer(t_shell *shell)
{
	char	*new_str;

	if (shell->rl_copy)
		free(shell->rl_copy);
	new_str = clean_rl(shell->rl_input);
	if (new_str == NULL)
	{
		perror("ERROR ; Bad syntax");
		return (NULL);
	}
	shell->rl_input = new_str;
	shell->lex_head = tokenize(shell);
	if (!check_pipe(shell->lex_head))
	{
		perror("ERR: invalid pipe syntax");
		free_lex(shell->lex_head);
		shell->rl_input = NULL;
		return (NULL);
	}
	shell->rl_copy = new_str;
	return (shell->lex_head);
}
*/

t_lx	*lexer(t_shell *shell)
{
	char	**input_arr;
	t_lx	*lex_head;
	char	*new_str;

	new_str = clean_rl(shell->rl_input);
	if (!new_str)
	{
		perror("ERROR: Bad syntax");
		return (NULL);
	}
	if (shell->rl_copy)
	{
		free(shell->rl_copy);
		shell->rl_copy = NULL;
	}
	shell->rl_copy = ft_strdup(new_str);
	free(new_str);
	input_arr = create_arr(shell);
	if (!input_arr)
	{
		perror("Erreur: Allocation tableau tokenss");
		return (NULL);
	}
	lex_head = create_lexer_list(input_arr);
	free_tab(input_arr);
	if (!check_pipe(lex_head))
	{
		perror("ERROR: invalid syntax");
		free_lex(lex_head);
		return (NULL);
	}
	return (lex_head);
}

int	parser(t_shell *shell)
{
	if (shell->lex_head)
	{
		free_lex(shell->lex_head);
		shell->lex_head = NULL;
	}
	shell->lex_head = lexer(shell);
	if (shell->lex_head == NULL)
	{
		if (shell->rl_copy)
		{
			free(shell->rl_copy);
			shell->rl_copy = NULL;
		}
		return (0);
	}
	return (1);
}

void print_tokens(t_lx *lex_head)
{
	t_lx *current = lex_head;
	while (current != NULL)
	{
		// Affiche le token et son type
		printf("Token: %s, Type: ", current->str);
		switch (current->type)
		{
			case COMMAND:
				printf("COMMAND\n");
				break;
			case PIPE:
				printf("PIPE\n");
				break;
			case TRUNCATE:
				printf("TRUNCATE (>)\n");
				break;
			case APPEND:
				printf("APPEND (>>)\n");
				break;
			case REDIRECT_INPUT:
				printf("REDIRECT_INPUT (<)\n");
				break;
			case HEREDOC:
				printf("HEREDOC (<<)\n");
				break;
			default:
				printf("UNKNOWN\n");
				break;
		}
		current = current->next;
	}
}

int	main()
{
	t_shell	*shell;
	
	shell = malloc(sizeof(t_shell));
	shell->lex_head = NULL;
	shell->rl_input = ft_strdup("echo hello >> file.txt | cat < input.txt |");
	shell->rl_copy = NULL;
	if (!parser(shell))
	{
		printf("Error: parsing input\n");
		free(shell);
		return (1);
	}
	print_tokens(shell->lex_head);
	if (shell->rl_copy)
		free(shell->rl_copy);
	free_lex(shell->lex_head);
	free(shell);
	return (0);
}
