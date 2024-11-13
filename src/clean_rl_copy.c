/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_rl_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:11:58 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/16 16:29:57 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*clean_str(char *rl_copy, size_t start, size_t end)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc(sizeof(char) * ((end - start) + 2));
	if (!newstr)
		return (NULL);
	while (rl_copy[start] && start <= end)
	{
		newstr[i] = rl_copy[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*clean_rl(char *rl_copy)
{
	size_t	start;
	size_t	end;
	char	*clean_cpy;

	start = 0;
	end = ft_strlen(rl_copy) - 1;
	while (ft_isspace(rl_copy[start]))
		start++;
	while (end > start && ft_isspace(rl_copy[end]))
		end--;
	if (!pars_check(rl_copy))
		return (NULL);
	clean_cpy = clean_str(rl_copy, start, end);
	free(rl_copy);
	return (clean_cpy);
}
