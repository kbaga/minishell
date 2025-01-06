/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:41:55 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/24 17:37:00 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_delimiter(char *buffer, char *delimiter)
{
	return (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0
		&& buffer[strlen(delimiter)] == '\n');
}

static int	ft_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*my_ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	num = n;
	len = ft_num_len(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (--len >= 0 && str[len] != '-')
	{
		str[len] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

void	int_to_string(int n, char *buffer, size_t size)
{
	char	*temp_str;

	temp_str = my_ft_itoa(n);
	if (!temp_str)
	{
		buffer[0] = '\0';
		return ;
	}
	ft_strncpy(buffer, temp_str, size - 1);
	buffer[size - 1] = '\0';
	free(temp_str);
}
