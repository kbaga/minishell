/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:08:30 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/24 18:06:07 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*add_substr(char *str, int i, int k)
{
	char	*substr;

	substr = (char *)malloc(sizeof(char) * (k + 1));
	if (!substr)
		return (NULL);
	ft_strncpy(substr, str + i, k);
	substr[k] = '\0';
	return (substr);
}

int	proc_tok(char **arr, char *s, int *i, int *j)
{
	arr[*i] = add_substr(s, *j, 1);
	if (!arr[*i])
		return (-1);
	(*i)++;
	(*j)++;
	return (0);
}
