/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:40:08 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/05 23:39:51 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_whitespace(char *s, int i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	reset_shell(t_shell *shell)
{
	if (shell->lex_head)
	{
		free_lex(shell->lex_head);
		shell->lex_head = NULL;
	}
}

void	handle_line(t_shell *shell, char *line)
{
	if (!line || !*line)
		return ;
	shell->rl_input = ft_strdup(line);
	if (!shell->rl_input)
	{
		perror("Failed to allocate input string");
		return ;
	}
	if (!parser(shell))
	{
		printf("Parsing failed for input: %s\n", line);
		shell->exit_status = 1;
	}
	free(shell->rl_input);
	shell->rl_input = NULL;
}

t_lx	*lexer_clean(t_shell *shell, t_lx *lex_head)
{
	if (shell->rl_copy)
	{
		free(shell->rl_copy);
		shell->rl_copy = NULL;
	}
	if (lex_head)
		free_lex(lex_head);
	return (NULL);
}
