/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FAKE_UTILS.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:43:00 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 18:32:22 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

size_t	ft_strlcpy(char	*dst, const char *src, size_t	dstsize)
{
	size_t	len;

	len = 0;
	if (dstsize > 0)
	{
		while ((len + 1) < dstsize && src[len])
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = 0;
	}
	while (src[len])
		len++;
	return (len);
}
