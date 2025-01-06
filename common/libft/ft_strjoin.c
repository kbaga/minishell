/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:42 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/19 18:05:11 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcopy(char *dest, char *src, int *index)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[*index] = src[i];
		(*index)++;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		total_len;
	char	*res;
	int		i;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	ft_strcopy(res, s1, &i);
	ft_strcopy(res, s2, &i);
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	res = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len_s1 + 1);
	ft_strlcpy(res + len_s1, s2, len_s2 + 1);
	res[len_s1 + len_s2] = 0;
	return (res);
}
