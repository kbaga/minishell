/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:42:39 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/08 18:20:06 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*lexer_assign(t_lx **head, t_lx **curr,
		char **input_array, int i)
{
	t_lx	*new_node;

	new_node = create_token(input_array, *curr, i);
	if (!*head)
		*head = new_node;
	else
		(*curr)->next = new_node;
	*curr = new_node;
	return (NULL);
}

t_lx	*create_lexer_list(char **input_array)
{
	t_lx	*head;
	t_lx	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	if (!input_array)
		return (NULL);
	while (input_array[i])
	{
		lexer_assign(&head, &current, input_array, i);
		i++;
	}
	return (head);
}

t_lx	*tokenize(t_shell *shell)
{
	char	**input_arr;
	t_lx	*lex_head;

	if (!shell || !shell->rl_input)
		return (NULL);
	input_arr = input_split(shell->rl_input);
	if (!input_arr)
	{
		perror("Failed alloc: input");
		return (NULL);
	}
	lex_head = create_lexer_list(input_arr);
	free_tab(input_arr);
	return (lex_head);
}

/*
int	main(int argc, char **argv)
{
	t_shell	shell;
	char	*input = NULL;
	size_t	len = 0;
	t_lx	*lex_head;

	shell.rl_input = NULL;
	if(argc > 1)
	{
		printf("Args: \n");
		for (int i = 1; i < argc; i++)
			printf("%s\n", argv[i]);
	}
	while (1)
	{
		printf("%s", PROMPT);
		if (getline(&input, &len, stdin) == -1)
		{
			perror("Error reading input");
			break;
		}
		input[strcspn(input, "\n")] = 0;
		shell.rl_input = input;
		lex_head = tokenize(&shell);
		if (!lex_head)
		{
			fprintf(stderr, "Err: TOKENIZATION FAILED\n");
			continue;
		}
		printf("Tokens:\n");
		t_lx	*curr = lex_head;
		while (curr)
		{
			printf("Token: %s, Type: %d\n", curr->str, curr->type);
			curr = curr->next;
		}
		curr = lex_head;
		while (curr)
		{
			t_lx	*next = curr->next;
			free(curr->str);
			free(curr);
			curr = next;
		}
	}
	free(input);
	return (0);
}
*/
