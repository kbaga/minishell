/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:04:04 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/24 18:04:28 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_exec_list(t_shell *shell, t_exec *cmd_list, t_env *env)
{
	t_exec	*current;

	current = cmd_list;
	while (current != NULL)
	{
		send_to_exec(shell, current, env);
		current = current->next;
	}
}

t_fd_backup	save_fds(void)
{
	t_fd_backup	backup;

	backup.saved_stdin = dup(STDIN_FILENO);
	backup.saved_stdout = dup(STDOUT_FILENO);
	if (backup.saved_stdin == -1 || backup.saved_stdout == -1)
		perror("Failed to save file descriptors");
	return (backup);
}

void	restore_fds(t_fd_backup *backup)
{
	if (backup->saved_stdin != -1
		&& dup2(backup->saved_stdin, STDIN_FILENO) == -1)
		perror("Failed to restore stdin");
	if (backup->saved_stdout != -1
		&& dup2(backup->saved_stdout, STDOUT_FILENO) == -1)
		perror("Failed to restore stdout");
	close(backup->saved_stdin);
	close(backup->saved_stdout);
}
