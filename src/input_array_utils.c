/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:38 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/24 18:07:52 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	skip_quotes(char *str)
{
	char	quote;
	int		i;

	i = 1;
	quote = *str;
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
		else
			(*len)++;
	}
}

int	is_token(char to_check)
{
	char	*tokens;

	tokens = "<>|";
	if (ft_strchr(tokens, to_check))
		return (1);
	return (0);
}

int	is_token2(char to_check)
{
	char	*tokens;

	tokens = "<>";
	if (ft_strchr(tokens, to_check))
		return (1);
	return (0);
}
