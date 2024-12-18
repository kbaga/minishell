#include "../inc/minishell.h"

// t_exec *create_exec_node(int id, char **cmd)
// {
// 	t_exec *node;
	
// 	node = malloc(sizeof(t_exec));
// 	if (!node)
// 		return NULL;
// 	node->id = id;
// 	node->size = 0;
// 	node->fd_in = 0;
// 	node->fd_out = 1;
// 	node->trunc = 0;
// 	node->append = 0;
// 	node->redir_input = 0;
// 	node->heredoc = 0;
// 	node->path = NULL;
// 	node->execs = cmd;
// 	node->prev = NULL;
// 	node->next = NULL;

// 	return node;
// }

// static void print_pipe_content(int fd_pipe)
// {
//     char buffer[4096]; // Taille de lecture
//     ssize_t bytes_read;

//     // Lire le contenu du pipe et l'afficher
//     while ((bytes_read = read(fd_pipe, buffer, sizeof(buffer) - 1)) > 0)
//     {
//         buffer[bytes_read] = '\0'; // Assurer que le buffer est terminé par '\0'
//         write(STDOUT_FILENO, buffer, bytes_read); // Écrire sur stdout
//     }

//     if (bytes_read == -1)
//         perror("read pipe");
// }

void link_exec_with_pipe(t_exec *node_exec, t_exec_context *context)
{
	int pipe_fds[2];
	
	if (pipe(pipe_fds) == -1) 
	{
		perror("pipe");
		return;
	}
	node_exec->fd_out = pipe_fds[1];
	context->fd_pipe = pipe_fds[0];
	node_exec->pipe = 1;
	
	  // Exemple : écrire quelque chose dans le pipe
    // write(node_exec->fd_out, "Hello from pipe!\n", 17);
    // close(node_exec->fd_out); // Fermer l'extrémité d'écriture

    // // Afficher le contenu du pipe
    // print_pipe_content(context->fd_pipe);
    // close(context->fd_pipe); // Fermer l'extrémité de lecture	
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
