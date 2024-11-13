/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_spit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:40:53 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/03 18:29:20 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ischar(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

static int	count_words(char const *s)
{
	int	i;
	int	count;
	int	trigger;
	int	in_quote;

	i = 0;
	count = 0;
	trigger = 0;
	in_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && in_quote == 0)
			in_quote = s[i];
		else if (s[i] == in_quote)
			in_quote = 0;
		if (!ischar(s[i]) && trigger == 0 && in_quote == 0)
		{
			trigger = 1;
			count++;
		}
		else if (ischar(s[i]) && in_quote == 0)
			trigger = 0;
		i++;
	}
	return (count);
}

static int	count_char(const char *s, int pos)
{
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (s[pos + i] && (!ischar(s[pos + i]) || in_quote != 0))
	{
		if ((s[pos + i] == '\'' || s[pos + i] == '\"') && in_quote == 0)
			in_quote = s[pos + i];
		else if (s[pos + i] == in_quote)
			in_quote = 0;
		i++;
	}
	return (i);
}

static char	*create_new(char const *str, int *pos)
{
	char	*nstr;
	int		i;
	int		len;

	i = 0;
	len = count_char(str, *pos);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (NULL);
	while (i < len)
	{
		nstr[i++] = str[*pos];
		(*pos)++;
	}
	nstr[i] = '\0';
	return (nstr);
}

char	**input_split(const char *s)
{
	int		i;
	int		y;
	char	**list;

	if (!s)
		return (NULL);
	list = (char **)malloc(sizeof(*list) * (count_words(s) + 1));
	if (!list)
		return (NULL);
	i = 0;
	y = 0;
	while (s[i])
	{
		while (ischar(s[i]) && s[i])
			i++;
		if (s[i])
		{
			list[y] = create_new(s, &i);
			y++;
		}
		while (!ischar(s[i]) && s[i])
			i++;
	}
	list[y] = NULL;
	return (list);
}
