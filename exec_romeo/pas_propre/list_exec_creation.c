#include "../minishell.h"

char **copy_cmd(char **cmd)
{
    int count;
	int i;

	i  = 0;
	count = 0;
    while (cmd[count])
        count++;

    char **new_cmd = malloc(sizeof(char *) * (count + 1));
    if (!new_cmd)
        return NULL;

    while (i < count)
    {
        new_cmd[i] = strdup(cmd[i]); // Dupliquer chaque chaîne
        if (!new_cmd[i]) 
        {
            while (i > 0)
                free(new_cmd[--i]);
            free(new_cmd);
            return NULL;
        }
        i++;
    }
    new_cmd[count] = NULL; // Terminer par NULL
    return new_cmd;
}

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
	node->execs = copy_cmd(cmd); // Copier le tableau
	if (!node->execs)
	{
		free(node);
		return NULL;
	}
	node->prev = NULL;
	node->next = NULL;

	return node;
}

// t_exec create_exec_list(t_shell *shell)
// {
// 	t_lexer_list	*current_lexer;
// 	t_exec			*current_exec;
// 	int				i;

// 	i = 0;
// 	current_lexer = shell->lex_head;
// 	current_exec = shell->exec;
// 	while (current_lexer)
// 	{
// 		shell->exec =  create_exec_node(i, );

// 	}
// }


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

int main(void)
{
    // Input commands to test
    char *cmd[] = {"ls", "-l", "/tmp", NULL};

    // Create the exec node
    t_exec *node = create_exec_node(1, cmd);

    if (!node)
    {
        printf("Failed to create exec node.\n");
        return EXIT_FAILURE;
    }

    // Print the contents of the node for testing
    printf("Node ID: %d\n", node->id);
    printf("Execs:\n");
    for (int i = 0; node->execs[i]; i++)
        printf("  [%d]: %s\n", i, node->execs[i]);

    // Free the node
    free_exec_node(node);

    return EXIT_SUCCESS;
}
