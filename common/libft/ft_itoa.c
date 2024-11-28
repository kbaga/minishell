/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:01:00 by lakamba           #+#    #+#             */
/*   Updated: 2024/11/23 19:27:25 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(int n)
{
	int	count;

	count = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*nb;
	int			len;
	long int	num;

	num = n;
	len = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		len++;
	}
	nb = malloc(sizeof(char) * len + 1);
	if (nb == 0)
		return (nb);
	nb[len--] = '\0';
	while (len >= 0)
	{
		nb[len--] = num % 10 + 48;
		num /= 10;
	}
	if (n < 0)
		nb[0] = '-';
	return (nb);
}
