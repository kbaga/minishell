#include "../inc/minishell.h"

void fork_external(t_exec *head, t_env *env_list)
{
	t_exec *current;
	pid_t pid;

	current = head;
	pid = fork();
	if (pid < 0) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute_command(current, env_list); // Execute command in child
		perror("execve failed");
	}
	else
	{
		// Close FDs in parent to avoid leaks
		if (current->fd_in != 0) close(current->fd_in);
		if (current->fd_out != 1) close(current->fd_out);
	}
	while (wait(NULL) > 0); // Wait for all children
}

// Function to separate execution between built-in and execve
void send_to_exec(t_shell *shell, t_exec *cmd, t_env *env) 
{
		if (cmd == NULL || cmd->execs == NULL || cmd->execs[0] == NULL)
		{
			write(STDERR_FILENO, "Invalid command.\n", 17);
			return;
		}
		if (is_builtin(cmd->execs[0]))
		{
			write(2, "test error, is builtin\n", 24);
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
			execute_builtin(shell, cmd->execs[0], cmd->execs, env);
		}
		else
			fork_external(cmd, env);
}

void execute_exec_list(t_shell *shell, t_exec *cmd_list, t_env *env)
{
    t_exec *current;
	
	current = cmd_list;
    while (current != NULL)
	{
        send_to_exec(shell, current, env); // Execute the current command
        current = current->next;   // Move to the next command in the list
	}
}
