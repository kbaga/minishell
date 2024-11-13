/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:31:21 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/03 18:31:39 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
	{
		printf("Malloc alloc failed\n");
		free(ptr);
	}
	return (ptr);
}

void	error_exit(const char *msg)
{
	printf("%s\n", msg);
	return ;
}

void	safe_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		printf("pipe failed");
}
