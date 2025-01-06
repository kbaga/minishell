/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:55:55 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/06 15:57:14 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(char **args)
{
	if (!args[1])
	{
		write(STDERR_FILENO, "cd: missing argument\n", 21);
		return ;
	}
	if (args[1][0] != '/' && strcmp(args[1], "..") != 0
		&& strncmp(args[1], "../", 3) != 0
		&& strncmp(args[1], "./", 2) != 0)
	{
		write(STDERR_FILENO, "cd: only relative or absolute\
		paths allowed\n", 44);
		return ;
	}
	if (chdir(args[1]) == -1)
		perror("cd");
	return ;
}
