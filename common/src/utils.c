/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:40:08 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/27 19:01:09 by romeo            ###   ########.fr       */
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

/*
int	handle_quotes(char **arr, char *s, int *k, int *i)
{
	char	qte;
	int		start;

	qte = s[*k];
	(*k)++;
	start = *k;
	while (s[*k] && s[*k] != qte)
		(*k)++;
	if (add_str(arr, s, start, *k, i) == -1)
		return (-1);
	(*k)++;
	return (0);
}

int	handle_substr(char **arr, char *s, int *k, int *i)
{
	int	start;

	start = *k;
	while (s[*k] && !is_token(s[*k])
		&& !is_whitespace(s[*k]))
		(*k)++;
	if (add_subtr(arr, s, start, *k, i) == -1)
		return (-1);
	return (0);
}
*/
