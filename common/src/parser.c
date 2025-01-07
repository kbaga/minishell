/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:31:25 by kbaga             #+#    #+#             */
/*   Updated: 2025/01/02 12:11:54 by romeo            ###   ########.fr       */
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

t_lx	*lexer(t_shell *shell)
{
	char	**input_arr;
	t_lx	*lex_head;

	if (!shell || !shell->rl_input)
		return (NULL);
	shell->rl_copy = clean_rl(shell->rl_input);
	if (!shell->rl_copy)
		return (NULL);
	input_arr = create_arr(shell);
	if (!input_arr)
		return (lexer_clean(shell, NULL));
	lex_head = create_lexer_list(input_arr);
	free_tab(input_arr);
	if (!lex_head)
		return (lexer_clean(shell, NULL));
	if (!check_pipe(lex_head))
		return (lexer_clean(shell, lex_head));
	free(shell->rl_copy);
	shell->rl_copy = NULL;
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
	interpolate_tokens(shell);
	shell->executor = create_exec_list(shell);
	shell->pid_list = init_pid_list();
	execute_exec_list(shell, shell->executor, shell->environ);
	wait_all_pids(shell->pid_list);
	free_pid_list(shell->pid_list);
	//process_tokens(shell, shell->lex_head);
	return (1);
}

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	char		*line;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell->environ || !shell)
	{
		perror("Failed to initialize environment");
		return (1);
	}
	while (1)
	{
		t_fd_backup fd_backup = save_fds(); //////
		line = readline("minishell> ");
		if (!line)
		{
			printf("\nexit\n"); // Handle Ctrl+D (end-of-file)
			ft_exit(shell, NULL);
		}
		if (*line)
			add_history(line);
		handle_line(shell, line);
		//free_exec_list(shell->executor);
		reset_shell(shell);
		free(line);
		line = NULL;
		restore_fds(&fd_backup); /////////
	}
	free_env(shell->environ);
	return (0);
}
