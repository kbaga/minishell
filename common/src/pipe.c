/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:30:28 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 18:30:53 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	link_exec_with_pipe(t_exec *node_exec, t_exec_context *context)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return ;
	}
	node_exec->fd_out = pipe_fds[1];
	context->fd_pipe = pipe_fds[0];
	node_exec->pipe = 1;
}
