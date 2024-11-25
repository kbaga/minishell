/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:04:29 by lakamba           #+#    #+#             */
/*   Updated: 2024/11/25 11:39:29 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_lx *curr, t_shell *shell)
{
	int	flag;

	flag = 0;
	if (curr && curr->next && ft_strcmp(curr->next->str, "-n") == 0)
	{
		flag = 1;
		curr = curr->next;
	}
	curr = curr->next;
	while (curr)
	{
		if (curr->type != COMMAND)
			break ;
		printf("%s", curr->str);
		if (curr->next)
			printf(" ");
		curr = curr->next;
	}
	if (!flag)
		printf("\n");
	shell->exit_status = 0;
}

void	ft_pwd(t_shell *shell)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		shell->exit_status = 0;
	}
	else
	{
		perror("getcwd");
		shell->exit_status = 1;
	}
}

static void	handle_export(t_shell *shell, t_lx *args)
{
	while (args)
	{
		exporting(shell, args->str);
		args = args->next;
	}
}

static void	handle_builtin(t_shell *shell, t_lx *curr)
{
	if (!curr || !curr->str)
		return ;
	if (ft_strcmp(curr->str, "echo") == 0)
		ft_echo(curr, shell);
	else if (ft_strcmp(curr->str, "export") == 0)
		handle_export(shell, curr->next);
	else if (ft_strcmp(curr->str, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(curr->str, "unset") == 0)
	{
		if (!curr->next)
		{
			printf("unset: not enough arguments\n");
			shell->exit_status = 127;
		}
		else
			unset(shell, curr->next);
	}
	else if (ft_strcmp(curr->str, "env") == 0)
		exp_no_args(shell);
	else if (ft_strcmp(curr->str, "exit") == 0)
		ft_exit(shell, curr->next);
	else if (shell->exit_status == 127)
		printf("Command not found: %s\n", curr->str);
}

void	execute_cmd(t_shell *shell, t_lx *curr)
{
	if (!curr || !curr->str)
		return ;
	handle_builtin(shell, curr);
	// if (shell->exit_status == 0)
	// printf("Command not found: %s\n", curr->str);
}
