/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:04:29 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/08 10:52:45 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	ft_echo(char **execs, t_shell *shell)
// {
// 	int	flag;
// 	int i;

// 	flag = 0;
// 	i = 1;
// 	if (execs[i] && ft_strcmp(execs[i], "-n") == 0)
// 	{
// 		flag = 1;
// 		i++;
// 	}
// 	while (execs[i])
// 	{
// 		printf("%s", execs[i]);
// 		if (execs[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (!flag)
// 		printf("\n");
// 	shell->exit_status = 0;
// }

// void	ft_pwd(t_shell *shell)
// {
// 	char	pwd[1024];

// 	if (getcwd(pwd, sizeof(pwd)) != NULL)
// 	{
// 		printf("%s\n", pwd);
// 		shell->exit_status = 0;
// 	}
// 	else
// 	{
// 		perror("getcwd");
// 		shell->exit_status = 1;
// 	}
// }

static void	handle_export(t_shell *shell, char **execs)
{
	int i;
	
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

void	handle_builtin(t_shell *shell, t_exec *exec_node)
{
	char	**execs;

	if (!exec_node || !exec_node->execs || !exec_node->execs[0])
		return ;
	execs = exec_node->execs;
	if(ft_strcmp(execs[0], "cd") == 0)
		ft_cd(shell->environ, execs);
	if (ft_strcmp(execs[0], "echo") == 0)
		ft_echo(execs, shell);
	else if (ft_strcmp(execs[0], "export") == 0)
		handle_export(shell, execs);
	else if (ft_strcmp(execs[0], "pwd") == 0)
		ft_pwd();/////shell a remodif exitreturn
	else if (ft_strcmp(execs[0], "unset") == 0)
	{
		if (!execs[1])
		{
			printf("unset: not enough arguments\n");
			shell->exit_status = 127;
		}
		else
			unset(shell, &execs[1]);
	}
	else if (ft_strcmp(execs[0], "env") == 0)
		exp_no_args(shell->environ);
	// else if (ft_strcmp(execs[0], "exit") == 0)
	// 	ft_exit(shell, &execs[1]);
	// else if (shell->exit_status == 127)
	// 	printf("Command not found: %s\n", execs[0]);
}

// int	is_builtin(const char *cmd)
// {
// 	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
// 		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
// 		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "export") == 0
// 		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0);
// }

// void	execute_cmd(t_shell *shell, t_exec *exec_node)
// {
// 	if (!exec_node || !exec_node->execs || exec_node->execs[0])
// 		return ;
// 	if (is_builtin(exec_node->execs[0]))
// 		handle_builtin(shell, exec_node);
// 	else
// 		handle_builtin(shell, exec_node);
// }