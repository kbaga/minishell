/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_from_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:21:12 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/24 18:03:19 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	redirect_io(t_exec *current)
{
	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
			error_command("dup2 fd_in");
		close(current->fd_in);
	}
	if (current->fd_out != STDOUT_FILENO)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
			error_command("dup2 fd_out");
		close(current->fd_out);
	}
}

static void	close_fds(t_exec *current)
{
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	if (current->fd_out != STDOUT_FILENO)
		close(current->fd_out);
}

void	fork_builtin(t_shell *shell, t_exec *head, t_env *env_list)
{
	pid_t	pid;

	(void)env_list;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		redirect_io(head);
		handle_builtin(shell, head);
		_exit(EXIT_SUCCESS);
	}
	else
	{
		close_fds(head);
		while (wait(NULL) > 0)
			;
	}
}

void	fork_external(t_exec *head, t_env *env_list)
{
	t_exec	*current;
	pid_t	pid;

	current = head;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute_command(current, env_list);
		perror("execve failed");
	}
	else
	{
		if (current->fd_in != 0)
			close(current->fd_in);
		if (current->fd_out != 1)
			close(current->fd_out);
	}
	wait(NULL);
}

void	send_to_exec(t_shell *shell, t_exec *cmd, t_env *env)
{
	if (cmd == NULL || cmd->execs == NULL || cmd->execs[0] == NULL)
	{
		write(STDERR_FILENO, "Invalid command.\n", 17);
		return ;
	}
	if (is_builtin(cmd->execs[0]) && cmd->pipe == 0)
	{
		if (cmd->fd_in != 0)
		{
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				error_command("dup2 fd_in");
			close(cmd->fd_in);
		}
		if (cmd->fd_out != 1)
		{
			if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
				error_command("dup2 fd_out");
			close(cmd->fd_out);
		}
		handle_builtin(shell, cmd);
	}
	else if (is_builtin(cmd->execs[0]) && cmd->pipe == 1)
		fork_builtin(shell, cmd, env);
	else
		fork_external(cmd, env);
}
