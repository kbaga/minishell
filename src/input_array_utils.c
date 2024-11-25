/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:38 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/21 12:25:21 by kbaga            ###   ########.fr       */
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
	printf("skip_quotes: Starting at [%s] with quote [%c]\n", str, quote);
	while (str[i])
	{
		if (str[i] == quote)
		{
			printf("skip_quotes: Closing quote [%c] found at index %d\n", quote, i);
			return (i + 1);
		}
		i++;
	}
	printf("skip_quotes: Unterminated quote [%c] starting at [%s]\n", quote, str);
	return (i);
}

void	no_delim_found(char *str, int *len)
{
	char	*quote;

	quote = "\"\'";
	printf("no_delim_found: Starting at [%s]\n", str + *len);
	//(*len)++; //just changed
	while (str[*len])
	{
		if (str[*len] && ft_strchr(quote, str[*len]))
		{
			printf("no_delim_found: Quote found at index %d, skipping\n", *len);
			*len += skip_quotes(str + *len);
		}
		else if (str[*len] == ' ' || is_token(str[*len]))
		{
			printf("no_delim_found: FOund delimiter [%c] at index %d\n", str[*len], *len);
			return ;
		}
		else
		{
			(*len)++;
			printf("no_delim_found: Advancing to index %d\n", *len);
		}
	}
	printf("no_delim_found: FInished at index %d\n", *len);
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
