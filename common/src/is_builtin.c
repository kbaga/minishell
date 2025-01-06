/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:04:29 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/06 16:37:01 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_export(t_shell *shell, char **execs)
{
	int	i;

	if (!execs[1])
		exp_no_args(shell->environ);
	else
	{
		i = 1;
		while (execs[i])
		{
			exporting(shell, execs[i]);
			i++;
		}
	}
}

static void	handle_unset(t_shell *shell, char **execs)
{
	if (!execs[1])
	{
		printf("unset: not enough arguments\n");
		shell->exit_status = 127;
	}
	else
		unset(shell, &execs[1]);
}

void	handle_builtin(t_shell *shell, t_exec *exec_node)
{
	char	**execs;

	if (!exec_node || !exec_node->execs || !exec_node->execs[0])
		return ;
	execs = exec_node->execs;
	if (ft_strcmp(execs[0], "cd") == 0)
		ft_cd(execs);
	if (ft_strcmp(execs[0], "echo") == 0)
		ft_echo(execs, shell);
	else if (ft_strcmp(execs[0], "export") == 0)
		handle_export(shell, execs);
	else if (ft_strcmp(execs[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(execs[0], "unset") == 0)
		handle_unset(shell, execs);
	else if (ft_strcmp(execs[0], "env") == 0)
		exp_no_args(shell->environ);
	else if (ft_strcmp(execs[0], "exit") == 0)
		ft_exit(shell, execs);
}
