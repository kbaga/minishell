
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./minishell.h"

// Mock lexer creation for testing
t_lexer_list *create_mock_lexer()
{
	// t_lexer_list *head = malloc(sizeof(t_lexer_list));
	// t_lexer_list *node2 = malloc(sizeof(t_lexer_list));
	t_lexer_list *node3 = malloc(sizeof(t_lexer_list));
	//t_lexer_list *node4 = malloc(sizeof(t_lexer_list));
	t_lexer_list *node5 = malloc(sizeof(t_lexer_list));
	t_lexer_list *node6 = malloc(sizeof(t_lexer_list));
	//t_lexer_list *node7 = malloc(sizeof(t_lexer_list));


	if (/*!head || !node2 || */!node3 /*|| !node4 */|| !node5 || !node6 /*|| !node7*/)
		return NULL;

	// First command
	// head->str = strdup("ls");
	// head->type = COMMAND;
	// head->next =  node2;//node2;

	// // // Second command
	// node2->str = strdup("|");
	// node2->type = PIPE;
	// node2->next = node3;
	// node2->prev = head;

	// Third command
	node3->str = strdup("pwd");
	node3->type = COMMAND;
	node3->next = node5;
	node3->prev = NULL;//node2;

	// 	// Third command
	// node4->str = strdup("world uoiououou jjjjjjjjjjjj");
	// node4->type = COMMAND;
	// node4->next = node5;
	// node4->prev = node3;

	 // Third command
	node5->str = strdup("|");
	node5->type = PIPE;
	node5->next = node6;
	node5->prev = node3;

	 // Third command
	node6->str = strdup("wc");
	node6->type = COMMAND;
	node6->next = NULL;//node7;
	node6->prev = node5;

	// node7->str = strdup("-l");
	// node7->type = COMMAND;
	// node7->next = NULL;
	// node7->prev = node6;

return node3;
}

void print_exec_list(t_exec *exec_list)
{
	t_exec *current = exec_list;

	while (current)
	{
		printf("Exec ID: %d\n", current->id);
		printf("  FD_IN = %d\n", current->fd_in);
		printf("  FD_OUT = %d\n", current->fd_out);
		if (current->execs)
		{
			for (int i = 0; current->execs[i]; i++)
				printf("    Command[%d]: %s\n", i, current->execs[i]);
		}
		current = current->next;
	}
}

void free_exec_list(t_exec *exec_list)
{
	t_exec *tmp;
	while (exec_list)
	{
		tmp = exec_list;
		exec_list = exec_list->next;
		free_exec_node(tmp);
	}
}


void print_fd_content(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    // Rewind the FD to the start if it's a file (optional)
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the string
        printf("%s", buffer);     // Print the buffer content
    }

    if (bytes_read == -1) {
        perror("read");
    }
}

// void free_env_list(t_env_list *env_list) {
//     t_env_node *tmp;
//     while (env_list->head != NULL) 
// 	{
//         tmp = env_list->head;
//         env_list->head = env_list->head->next;

// 		// printf("key : %s\n", tmp->key);
// 		// printf("value : %s\n", tmp->val);
//         // Free key and val
//         free(tmp->key);
//         free(tmp->val);
//         // Free the node
//         free(tmp);
//     }
// }

int main(int ac, char** av, char **env)
{
	t_shell shell;
	t_exec *exec_list;

	t_env_list env_list;
	t_env_node *current_node, *new_node;


	(void)ac;
	(void)av;
	current_node = NULL;

	// Initialize the environment list
	env_list.head = NULL;

	// Convert char **env to t_env_list
	current_node = NULL;

	for (int i = 0; env[i]; i++) {
		char *delimiter = strchr(env[i], '=');
		if (!delimiter) { 
			continue; // Skip malformed environment variables
		}

		// Allocate new node
		new_node = malloc(sizeof(t_env_node));
		if (!new_node) {
			perror("malloc");
			// Add cleanup here if partial allocations have occurred
			return EXIT_FAILURE;
		}

		// Allocate key and value
		new_node->key = strndup(env[i], delimiter - env[i]);
		if (!new_node->key) {
			free(new_node);
			perror("strndup");
			return EXIT_FAILURE;
		}

		new_node->val = strdup(delimiter + 1);
		if (!new_node->val) {
			free(new_node->key);
			free(new_node);
			perror("strdup");
			return EXIT_FAILURE;
		}

		new_node->next = NULL;

		// Append to the list
		if (!env_list.head) {
			env_list.head = new_node; // Initialize head if list is empty
		} else {
			current_node->next = new_node; // Link the new node
		}

		current_node = new_node; // Move to the new node
	}
	// Initialize the mock lexer
	shell.lex_head = create_mock_lexer();
	if (!shell.lex_head)
	{
		fprintf(stderr, "Failed to create mock lexer.\n");
		return EXIT_FAILURE;
	}

	// Create the execution list
	exec_list = create_exec_list(&shell);
	if (!exec_list)
	{
		fprintf(stderr, "Failed to create execution list.\n");
		return EXIT_FAILURE;
	}

		// Print the execution list for verification
	printf("Execution List:\n");
	print_exec_list(exec_list);
	printf("\n\nEXECUTION :\n\n");
	execute_exec_list(exec_list, &env_list);


	// Free resources
	free_exec_list(exec_list);
	
	free_env_list(&env_list);

	// Free lexer list
	t_lexer_list *tmp;
	while (shell.lex_head)
	{
		tmp = shell.lex_head;
		shell.lex_head = shell.lex_head->next;
		free(tmp->str);
		free(tmp);
	}

	return 0;
}
