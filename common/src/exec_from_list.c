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
	if (is_builtin(cmd->execs[0]))
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
	// if (!isatty(STDIN_FILENO))
    // 	fprintf(stderr, "stdin is not a terminal\n");
	// else
	// 	printf("stdin restored to terminal\n");
	// printf("\ntest stdout\n");
	// fprintf(stderr, "finishe exec\n");
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
