/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:11:47 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/15 23:14:49 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(char *s)
{
	int	len;

	if (!s)
	{
		printf("Error: pointeur passé à ft_strlen");
		return (0);
	}
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
