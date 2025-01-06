/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:55:14 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/06 17:15:47 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*my_getenv(char *name, t_env *env_list)
{
	t_env_node	*current;

	current = env_list->head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, name) == 0)
			return (current->val);
		current = (current->next);
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env *env_list)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env_list), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin2(allpath[i], "/");
		exec = ft_strjoin2(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(allpath);
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (NULL);
}

static void	redirect_io(int fd, int std_fd, const char *err_msg)
{
	if (fd != std_fd)
	{
		if (dup2(fd, std_fd) == -1)
			error_command(err_msg);
		close(fd);
	}
}

static void	handle_exec_error(char *resolved_path, t_env *env_list)
{
	write(STDERR_FILENO, "Error: Command execution failed\n", 32);
	free(resolved_path);
	free_env_list(env_list);
	exit(EXIT_FAILURE);
}

void	execute_command(t_exec *node, t_env *env_list)
{
	char	*resolved_path;

	resolved_path = get_path(node->execs[0], env_list);
	redirect_io(node->fd_in, STDIN_FILENO, "dup2 fd_in");
	redirect_io(node->fd_out, STDOUT_FILENO, "dup2 fd_out");
	if (!resolved_path)
	{
		write(STDERR_FILENO, "Command not found\n", 19);
		command_not_found(node->execs[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(resolved_path, node->execs, NULL) == -1)
		handle_exec_error(resolved_path, env_list);
}

// void	execute_command(t_exec *node, t_env *env_list)
// {
// 	char	*resolved_path;

// 	resolved_path = get_path(node->execs[0], env_list);
// 	if (node->fd_in != 0)
// 	{
// 		if (dup2(node->fd_in, STDIN_FILENO) == -1)
// 			error_command("dup2 fd_in");
// 		close(node->fd_in);
// 	}
// 	if (node->fd_out != 1)
// 	{
// 		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
// 			error_command("dup2 fd_out");
// 		close(node->fd_out);
// 	}
// 	if (!resolved_path)
// 	{
// 		write (2, "pas resolved path\n", 19);
// 		command_not_found(node->execs[0]);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (execve(resolved_path, node->execs, NULL) == -1)
// 	{
// 		write(STDERR_FILENO, "Error: Command execution failed\n", 32);
// 		if (resolved_path)
// 			free(resolved_path);
// 		free_env_list(env_list);
// 		exit(EXIT_FAILURE);
// 	}
// }
