/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:38 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/25 19:47:07 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	skip_quotes(char *str)
{
	char	quote;
	int		i;

	if (!str || (*str != '\'' && *str != '"'))
		return (0);
	quote = *str;
	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (i);
}

void	no_delim_found(char *str, int *len)
{
	char	*quote;

	quote = "\"\'";
	while (str[*len])
	{
		if (str[*len] && ft_strchr(quote, str[*len]))
			*len += skip_quotes(str + *len);
		else if (str[*len] == ' ' || is_token(&str[*len]))
			return ;
		else
			(*len)++;
	}
}

int	is_token(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (*str == '>' || *str == '<' || *str == '|')
		return (1);
	return (0);
}
