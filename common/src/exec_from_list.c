#include "../inc/minishell.h"

void fork_builtin(t_shell *shell, t_exec *head, t_env *env_list)
{
	t_exec *current;
	pid_t pid;

	(void)env_list;
	current = head;
	pid = fork();
	if (pid < 0) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (current->fd_in != 0)
		{
			fprintf(stderr, "node -> %s ; fd_in = %d\n", current->execs[0], current->fd_in);
			if (dup2(current->fd_in, STDIN_FILENO) == -1)
				error_command("dup2 fd_in");
			close(current->fd_in);
		}
		if (current->fd_out != 1)
		{
			fprintf(stderr, "node -> %s ; fd_out = %d\n", current->execs[0], current->fd_out);
			if (dup2(current->fd_out, STDOUT_FILENO) == -1)
				error_command("dup2 fd_out");
			close(current->fd_out);
		}
		handle_builtin(shell, current); // Execute command in child
		_exit(0);
	}
	else
	{
		// Close FDs in parent to avoid leaks
		if (current->fd_in != 0) close(current->fd_in);
		if (current->fd_out != 1) close(current->fd_out);
	}
	// fprintf(stderr, "waiting for child\n");
	while (wait(NULL) > 0); // Wait for all children
	// fprintf(stderr, "_______\nend of waiting for child\n");
}
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
	// fprintf(stderr, "waiting for child\n");
	while (wait(NULL) > 0); // Wait for all children
	// fprintf(stderr, "_______\nend of waiting for child\n");
}

// Function to separate execution between built-in and execve
void send_to_exec(t_shell *shell, t_exec *cmd, t_env *env) 
{
	if (cmd == NULL || cmd->execs == NULL || cmd->execs[0] == NULL)
	{
		write(STDERR_FILENO, "Invalid command.\n", 17);
		return;
	}
	if (is_builtin(cmd->execs[0]) && cmd->pipe == 0)
	{
		if (cmd->fd_in != 0)
		{
			fprintf(stderr, "node -> %s ; fd_in = %d\n", cmd->execs[0], cmd->fd_in);
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				error_command("dup2 fd_in");
			close(cmd->fd_in);
		}
		if (cmd->fd_out != 1)
		{
			fprintf(stderr, "node -> %s ; fd_out = %d\n", cmd->execs[0], cmd->fd_out);
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
	// fprintf(stderr, "scooby send to exec\n");
}

void execute_exec_list(t_shell *shell, t_exec *cmd_list, t_env *env)
{
    t_exec *current;
	
	current = cmd_list;
    while (current != NULL)
	{
		// t_fd_backup fd_backup = save_fds();
        send_to_exec(shell, current, env); // Execute the current command
		// restore_fds(&fd_backup);
        current = current->next;   // Move to the next command in the list
	}

}


/**************** fonction pour les backups de fd ************/



t_fd_backup save_fds(void) 
{
    t_fd_backup backup;
    backup.saved_stdin = dup(STDIN_FILENO);
    backup.saved_stdout = dup(STDOUT_FILENO);
    if (backup.saved_stdin == -1 || backup.saved_stdout == -1)
        perror("Failed to save file descriptors");
    return backup;
}

void restore_fds(t_fd_backup *backup) 
{
    if (backup->saved_stdin != -1 && dup2(backup->saved_stdin, STDIN_FILENO) == -1) {
        perror("Failed to restore stdin");
    }
    if (backup->saved_stdout != -1 && dup2(backup->saved_stdout, STDOUT_FILENO) == -1) {
        perror("Failed to restore stdout");
    }
    close(backup->saved_stdin);
    close(backup->saved_stdout);
}
