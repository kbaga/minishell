/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:38:46 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/24 11:17:23 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0);
}

void	execute_builtin(t_shell *shell, t_exec *exec_node)
{
	(void)shell;
	if (!exec_node || !exec_node->execs || exec_node->execs[0])
		return ;
	if (strcmp(exec_node->execs[0], "cd") == 0)
		ft_cd(exec_node->execs);
	if (is_builtin(exec_node->execs[0]))
		handle_builtin(shell, exec_node);
	else
		handle_builtin(shell, exec_node);
}
