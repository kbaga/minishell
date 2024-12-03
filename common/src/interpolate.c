/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:50:16 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/29 03:54:28 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_exit_status(t_exp *exp, int *i, int exit_status)
{
	char	*exit_code;
	int		j;

	exit_code = ft_itoa(exit_status);
	if (!exit_code)
	{
		perror("Failed to convert exit status");
		return ;
	}
	j = 0;
	while (exit_code[j])
	{
		if (!handle_char(exp, exit_code[j]))
		{
			free(exit_code);
			return ;
		}
		j++;
	}
	free(exit_code);
	*i += 1; // Avance de 1 pour sauter le `?`
}

static int	process_char(t_shell *shell, t_exp *exp, int *i)
{
	if (exp->str[*i] == '\'')
	{
		*i = skip_single_quote(exp->str, *i, exp);
		printf("skip line");
		return (*i != -1);
	}
	else if (exp->str[*i] == '\"')
	{
		*i = skip_double_quote(shell, exp->str, *i, exp);
		printf("skip line");
		return (*i != -1);
	}
	if (exp->str[*i] == '$')
	{
		if (exp->str[*i + 1] == '?')
		{
			handle_exit_status(exp, i, shell->exit_status);
			return (1);
		}
		*i = expand_var(shell, &exp->str, exp, *i);
		if (*i == -1 || *i >= (int)(ft_strlen(exp->str)))
			return (0);
	}
	else if (!handle_char(exp, exp->str[*i]))
		return (0);
	return (1);
}

static char	*cleanup_and_return(t_exp *exp, char *result)
{
	free_exp(exp);
	return (result);
}

char	*interpolate(t_shell *shell, char *str)
{
	t_exp	*exp;
	char	*result;
	int		i;

	if (!shell || !str)
		return (NULL);
	exp = init_exp(str);
	i = 0;
	while (exp->str[i] && exp->str)
	{
		if (!process_char(shell, exp, &i))
			return (cleanup_and_return(exp, NULL));
		i++;
	}
	result = ft_strdup(exp->res);
	//free_exp(exp);
	return (cleanup_and_return(exp, result));
}

void	interpolate_tokens(t_shell *shell)
{
	t_lx	*curr;
	char	*expanded;

	if (!shell || !shell->lex_head)
		return ;
	curr = shell->lex_head;
	while (curr)
	{
		expanded = interpolate(shell, curr->str);
		if (expanded)
		{
			free(curr->str);
			curr->str = expanded;
		}
		else
		{
			printf("Interpolation failed for token: %s\n", curr->str);
		}
		curr = curr->next;
	}
}
