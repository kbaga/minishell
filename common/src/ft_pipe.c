/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:32:03 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/06 16:41:37 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	handle_forks(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return (-1);
	}
	return (pid);
}

int	handle_pipes(int fildes[2])
{
	if (pipe(fildes) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	return (0);
}
