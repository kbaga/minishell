/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:56:56 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/08 19:25:04 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *c)
{
	const char *a;

	while (*s)
	{
		a = c;
		while (*a)
		{
			if (*s == *a)
				return ((char *)s);
			a++;
		}
		s++;
	}
	return (NULL);
}

