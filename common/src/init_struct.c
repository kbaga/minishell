/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:48 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/18 22:13:14 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_lx *cmd)
{
	cmd->str = NULL;
	cmd->type = -1;
	cmd->index = -1;
	cmd->is_command = -1;
	cmd->prev = NULL;
	cmd->next = NULL;
}

void	init_exec(t_exec *exec)
{
	exec->id = 0;
	exec->size = 0;
	exec->fd_in = dup(0);
	exec->fd_out = dup(1);
	exec->trunc = 0;
	exec->append = 0;
	exec->redir_input = 0;
	exec->heredoc = 0;
	exec->execs = NULL;
	exec->prev = NULL;
	exec->next = NULL;
}
