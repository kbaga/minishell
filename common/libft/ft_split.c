/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:02:37 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 18:32:33 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nb_str_split(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

int	split_strlentgh(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char	*write_malloc(const char	*str, char c)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = split_strlentgh(str, c);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str[i] != c && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[len] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		tab_count;
	char	**splitted;

	splitted = malloc(sizeof(char *) * (nb_str_split(s, c) + 1));
	if (!s || !splitted)
		return (NULL);
	tab_count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		splitted[tab_count] = write_malloc(s, c);
		if (!splitted[tab_count])
		{
			ft_free_tab(splitted);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		tab_count++;
	}
	splitted[tab_count] = NULL;
	return (splitted);
}
