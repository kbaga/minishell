#include "./minishell.h"

// Handling > (Truncate) Redirection
void handle_truncate_redirection(t_exec *node, t_lexer_list *current)
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
void handle_append_redirection(t_exec *node, t_lexer_list *current)
{
    int fd;

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
void handle_input_redirection(t_exec *node, t_lexer_list *current)
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
void handle_redirection(t_exec *node, t_lexer_list *current)
{
	if (current->type == TRUNCATE) {
		handle_truncate_redirection(node, current);
	}
	else if (current->type == APPEND) {
		handle_append_redirection(node, current);
	}
	else if (current->type == REDIRECT_INPUT) {
		handle_input_redirection(node, current);
	}
	else if (current->type == HEREDOC) {
        handle_heredoc_redirection(node, current);
    }
}
