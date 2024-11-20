#include "../minishell.h"

t_exec *create_exec_node(int id, char **cmd)
{
	t_exec *node;
	
	node = malloc(sizeof(t_exec));
	if (!node)
		return NULL;
	node->id = id;
	node->size = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->trunc = 0;
	node->append = 0;
	node->redir_input = 0;
	node->heredoc = 0;
	node->path = NULL;
	node->execs = cmd;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

void link_exec_with_pipe(t_exec *left, t_exec *right)
{
	int pipe_fds[2];
	
	if (pipe(pipe_fds) == -1) {
		perror("pipe");
		return;
	}
	left->fd_out = pipe_fds[1];
	right->fd_in = pipe_fds[0];
	left->next = right;
	right->prev = left;
}
/*
//Precision : we will use execve after I implement it
void execute_command(t_exec *node)
{
	if (node->fd_in != 0) {
		dup2(node->fd_in, 0);
		close(node->fd_in);
	}
	if (node->fd_out != 1) {
		dup2(node->fd_out, 1);
		close(node->fd_out);
	}
	execvp(node->execs[0], node->execs);
	perror("execvp");
	exit(EXIT_FAILURE);
}*/
