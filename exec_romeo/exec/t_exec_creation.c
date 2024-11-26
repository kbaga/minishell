#include "../minishell.h"

void free_exec_node(t_exec *node)
{
	if (!node)
		return;

	if (node->execs)
	{
		for (int i = 0; node->execs[i]; i++)
			free(node->execs[i]);
		free(node->execs);
	}
	free(node);
}

t_exec *create_exec_node(int id)
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
	node->execs = NULL;
	if (!node->execs)
	{
		free(node);
		return NULL;
	}
	node->prev = NULL;
	node->next = NULL;

	return node;
}

void init_exec_context(t_exec_context *context, t_shell *shell)
{
	context->current_lexer = shell->lex_head;
	context->lex_head = shell->lex_head;
	context->current_exec = NULL;
	context->exec_head = NULL;
	context->exec_id = 0;
	context->lex_id = 0;
}

char **tab_command(t_exec_context *context)
{
	t_lexer_list *lexer;
	int command_count;
	char **result;

	command_count = 0;
	lexer = context->current_lexer;
	while (lexer && lexer->type == COMMAND)
	{
		command_count++;
		lexer = lexer->next;
	}
	result = malloc(sizeof(char *) * (command_count + 1));
	if (!result)
		return NULL;
	lexer = context->current_lexer; // Reset lexer to the original position
	command_count = 0;    
	while (lexer && lexer->type == COMMAND)// Assign each command token to the result array
	{
		result[command_count++] = strdup(lexer->str);
		lexer = lexer->next;
	}
	printf("test\n");
	result[command_count] = NULL; // Null-terminate the array
	context->current_lexer = lexer; // Update the context to the next unprocessed lexer
	printf("doubletest\n");
	return result;
}

void	assign_command(t_shell *shell, t_exec_context *context)
{
	t_exec	*current_e;

	printf("assign command  test1\n");
	context->current_exec->execs = tab_command(context);
	printf("assign command  test2\n");
	while (context->current_lexer->type == COMMAND)
		context->current_lexer = context->current_lexer->next;

}

void assign_redirection(t_shell *shell, t_exec_context *context)
{
}

t_exec *create_exec_list(t_shell *shell)
{
	t_exec_context *context;
	t_exec *new_exec_node;
	t_exec *result_head;

	context = malloc(sizeof(t_exec_context));
	if (!context)
		return (NULL);
	init_exec_context(context, shell);
	while(context->current_lexer)
	{
		printf("test\n");
		new_exec_node = create_exec_node(context->exec_id);
		context->exec_id++;
		printf("test2\n");
		if (context->exec_head == NULL)
			context->exec_head = new_exec_node;
		else
			context->current_exec->next = new_exec_node;
		context->current_exec = new_exec_node;
		printf("test3\n");
		if (context->current_lexer->type != COMMAND)
			assign_redirection(shell, context);
		if(context->current_lexer->type == COMMAND)
			assign_command(shell, context);
		if(context->current_lexer->type != COMMAND)
			assign_redirection(shell, context);
		printf("test4\n");
	}

	free(context);
	return (context->exec_head);
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell.h"

// Mock lexer creation for testing
t_lexer_list *create_mock_lexer()
{
    t_lexer_list *head = malloc(sizeof(t_lexer_list));
    t_lexer_list *node2 = malloc(sizeof(t_lexer_list));
    t_lexer_list *node3 = malloc(sizeof(t_lexer_list));

    if (!head || !node2 || !node3)
        return NULL;

    // First command
    head->str = strdup("echo");
    head->type = COMMAND;
    head->next = node2;

    // Second command
    node2->str = strdup("Hello, world!");
    node2->type = COMMAND;
    node2->next = node3;
    node2->prev = head;

    // Third command
    node3->str = strdup("Minishell!");
    node3->type = COMMAND;
    node3->next = NULL;
    node3->prev = node2;

    return head;
}

void print_exec_list(t_exec *exec_list)
{
    t_exec *current = exec_list;

    while (current)
    {
        printf("Exec ID: %d\n", current->id);
        if (current->execs)
        {
            for (int i = 0; current->execs[i]; i++)
                printf("  Command[%d]: %s\n", i, current->execs[i]);
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

int main()
{
    t_shell shell;
    t_exec *exec_list;

    // Initialize the mock lexer
    shell.lex_head = create_mock_lexer();
    if (!shell.lex_head)
    {
        fprintf(stderr, "Failed to create mock lexer.\n");
        return EXIT_FAILURE;
    }

    // Create the execution list
    exec_list = create_exec_list(&shell);
	printf("main test1\n");
    if (!exec_list)
    {
        fprintf(stderr, "Failed to create execution list.\n");
        return EXIT_FAILURE;
    }

    // Print the execution list for verification
    printf("Execution List:\n");
    print_exec_list(exec_list);

    // Free resources
    free_exec_list(exec_list);

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
