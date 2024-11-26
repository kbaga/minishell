#include "../minishell.h"

char *my_getenv(char *name, t_env_list *env_list)
{
	t_env_node *current;

	current = env_list->head;
	while (current != NULL)
{
	if (ft_strcmp(current->key, name) == 0)
		return (current->val);
	current = (current->next);
}
	return (NULL);
}

char	*get_path(char *cmd, t_env_list *env_list)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env_list), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])// Iterate through each path directory
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0) {
			ft_free_tab(allpath);
			ft_free_tab(s_cmd);
			return (exec); // Return the valid executable path
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (NULL);
}

void execute_command(t_exec *node, t_env_list *env_list)
{
	char *resolved_path;

	resolved_path = get_path(node->execs[0], env_list);
	if (node->fd_in != 0)// Redirect stdin if needed
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			error_command("dup2 fd_in");
		close(node->fd_in);
	}
	if (node->fd_out != 1)// Redirect stdout if needed
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			error_command("dup2 fd_out");
		close(node->fd_out);
	}
	//if (!resolved_path)
	// {
	// 	command_not_found(node->execs[0]);
	// 	exit(EXIT_FAILURE);
	// } 
	if (execve(resolved_path, node->execs, NULL) == -1) // Execute the command using execve
	{
		write(STDERR_FILENO, "Error: Command execution failed\n", 32);
		if (resolved_path)
			free(resolved_path);
		free_env_list(env_list);
		exit(EXIT_FAILURE); // Ensure child process terminates
	}
}

