/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:28:16 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/19 17:54:18 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (s2[i] && i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	while (i < len)
	{
		s1[i] = '\0';
		i++;
	}
	return (s1);
}
