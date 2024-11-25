/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:27:08 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/25 17:46:30 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_single_quote(char *str, int i, t_exp *exp)
{
	int	start;

	start = ++i;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (-1);
	while (start < i)
	{
		if (!handle_char(exp, str[start++]))
			return (-1);
	}
	return (i);
}

int	skip_double_quote(t_shell *shell, char *str, int i, t_exp *exp)
{
	++i;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && (str[i + 1] != '\"' && str[i + 1] != ' '))
			i = expand_var(shell, &str, exp, i);
		else if (!handle_char(exp, str[i]))
			return (-1);
		i++;
	}
	if (!str[i])
		return (-1);
	return (i);
}
