/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:31:05 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/19 18:05:28 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int i)
{
	char	*dup;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > i)
		len = i;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strncpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
