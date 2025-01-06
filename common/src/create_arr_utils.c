/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arr_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:39:18 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 19:40:49 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	len_substr(char *str)
{
	int		i;
	char	*tokens;

	i = 0;
	tokens = "<>|";
	while (str[i])
	{
		if (str[i] == ' ' || ft_strchr(tokens, str[i]))
			return (i);
		if (ft_strchr("\'\"", str[i]))
		{
			no_delim_found(str, &i);
		}
		else
			i++;
	}
	return (i);
}

int	skip_spaces(char *rl_copy, int i)
{
	while (rl_copy[i] == ' ' || rl_copy[i] == '\t')
		i++;
	return (i);
}

int	process_token_or_substr(char *rl_copy, int *i)
{
	int	len;

	len = is_token(rl_copy + *i);
	if (len > 0)
	{
		(*i)++;
		return (1);
	}
	len = len_substr(rl_copy + *i);
	if (len > 0)
	{
		*i += len;
		return (1);
	}
	return (0);
}

int	count_el(char *rl_copy)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (rl_copy[i])
	{
		i = skip_spaces(rl_copy, i);
		if (rl_copy[i] == '\0')
			break ;
		word += process_token_or_substr(rl_copy, &i);
	}
	return (word);
}
