#include "../inc/minishell.h"

// Handling > (Truncate) Redirection
void handle_truncate_redirection(t_exec *node, t_lx *current)
{
	int fd;

	current = current->next;
	fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror("open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1) {
		perror("dup2");
		close(fd);
		return;
	}
	close(fd);
	node->fd_out = STDOUT_FILENO;
	node->trunc = 1;
}

// Handling >> (Append) Redirection
void handle_append_redirection(t_exec *node, t_lx *current)
{
	int fd;

	if (!node || !current) {
    fprintf(stderr, "Invalid node or current pointer\n");
    return;
}if (!current->next) {
    fprintf(stderr, "Invalid next pointer in lexer list\n");
    return;
}

	current = current->next;
	fd = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1) {
		perror("open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1) {
		perror("dup2");
		close(fd);
		return;
	}
	close(fd);
	node->fd_out = STDOUT_FILENO;
	node->append = 1;
}

// Handling < (Input) Redirection
void handle_input_redirection(t_exec *node, t_lx *current)
{
	int fd;

	current = current->next;
	fd = open(current->str, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;
	}
	if (dup2(fd, STDIN_FILENO) == -1) {
		perror("dup2");
		close(fd);
		return;
	}
	close(fd);
	node->fd_in = STDIN_FILENO;
	node->redir_input = 1;
}

// Check if we have to redirect
void handle_redirection(t_shell *shell, t_exec_context *c)
{
	(void)shell;
	// fprintf(stderr, "before handle spec : %s\n", c->current_lexer->str);
	if (!c || !c->current_lexer->next || !c->current_lexer)
	{
        fprintf(stderr, "Redirection syntax error: missing argument\n");
		return ;
	}
	if (c->current_lexer->type == TRUNCATE)
	{
		handle_truncate_redirection(c->current_exec, c->current_lexer);
		// c->current_lexer = c->current_lexer->next;
	}
	else if (c->current_lexer->type == APPEND)
	{
		handle_append_redirection(c->current_exec, c->current_lexer);
		// c->current_lexer = c->current_lexer->next;
	}
	else if (c->current_lexer->type == REDIRECT_INPUT) {
		handle_input_redirection(c->current_exec, c->current_lexer);
		// c->current_lexer = c->current_lexer->next;

	}
	else if (c->current_lexer->type == HEREDOC) {
		handle_heredoc_redirection(c->current_exec, c->current_lexer);
		//c->current_lexer = c->current_lexer->next;
	}
	else if (c->current_lexer->type == PIPE)
	{
		link_exec_with_pipe(c->current_exec, c);
		c->current_lexer = c->current_lexer->next;
		return;
	}
	if (c->current_lexer && c->current_lexer->next)
		c->current_lexer = c->current_lexer->next->next;
	else
		c->current_lexer = NULL;
	
}
