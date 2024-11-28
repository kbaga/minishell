/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:42 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/14 17:49:11 by kbaga            ###   ########.fr       */
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
