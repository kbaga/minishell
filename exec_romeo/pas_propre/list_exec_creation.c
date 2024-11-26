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

void free_tab_command(char **tab)
{
    int i = 0;

    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
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
    result[command_count] = NULL; // Null-terminate the array
    context->current_lexer = lexer; // Update the context to the next unprocessed lexer
    return result;
}




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
    // Simulated lexer list for testing
    t_lexer_list lex1 = {"echo", COMMAND, 0, 1, NULL, NULL};
    t_lexer_list lex2 = {"Hello", COMMAND, 1, 0, &lex1, NULL};
    t_lexer_list lex3 = {"World", COMMAND, 2, 0, &lex2, NULL};
	t_lexer_list lex4 = {">", PIPE, 2, 0, &lex3, NULL};
    t_lexer_list lex4 = {"", PIPE, 2, 0, &lex4, NULL};
	lex1.next = &lex2;
    lex2.next = &lex3;
	lex3.next = &lex4;

    // Simulated context
t_exec_context context = {
    .current_lexer = &lex1, // Initialize with the first lexer node
    .exec_head = NULL,
    .current_exec = NULL,
    .lex_head = &lex1,
    .exec_tail = NULL,
    .lex_id = 0,
    .exec_id = 0
};

    // Test the tab_command function
    char **commands = tab_command(&context);

    // Print the result
    if (commands)
    {
        printf("Commands array:\n");
        for (int i = 0; commands[i]; i++)
            printf("  [%d]: %s\n", i, commands[i]);

        // Free the commands array
        free_tab_command(commands);
    }
    else
    {
        printf("Error: Failed to create commands array.\n");
    }

    return 0;
}

// int main(void)
// {
//     // Input commands to test
//     char *cmd[] = {"ls", "-l", "/tmp", NULL};

//     // Create the exec node
//     t_exec *node = create_exec_node(1, cmd);

//     if (!node)
//     {
//         printf("Failed to create exec node.\n");
//         return EXIT_FAILURE;
//     }

//     // Print the contents of the node for testing
//     printf("Node ID: %d\n", node->id);
//     printf("Execs:\n");
//     for (int i = 0; node->execs[i]; i++)
//         printf("  [%d]: %s\n", i, node->execs[i]);

//     // Free the node
//     free_exec_node(node);

//     return EXIT_SUCCESS;
// }
// \FUNCTION create_exec_list(shell)
//     SET current_lexer TO shell->lex_head
//     SET exec_list_head TO NULL
//     SET current_exec TO NULL
//     SET id_counter TO 0

//     WHILE current_lexer IS NOT NULL
//         IF current_lexer->type IS T_COMMAND
//             INCREMENT id_counter
//             CREATE a new t_exec node with create_exec_node(id_counter, current_lexer->str)

//             IF exec_list_head IS NULL
//                 SET exec_list_head TO new t_exec node
//             ELSE
//                 LINK current_exec->next TO new t_exec node
//                 LINK new t_exec node->prev TO current_exec

//             SET current_exec TO new t_exec node
//         ELSE IF current_lexer->type IS REDIRECTION
//             CALL handle_redirection(current_exec, current_lexer)
//         ELSE IF current_lexer->type IS PIPE
//             LINK current_exec->fd_out TO a pipe output
//             LINK the next t_exec node's fd_in TO the pipe input
//         END IF

//         MOVE TO current_lexer->next
//     END WHILE

//     RETURN exec_list_head
// END FUNCTION


// Règles générales pour le parsing :
// Redirections (>, >>, <, <<) :

// Après une redirection (>, >>, <, <<), le token suivant doit obligatoirement être un chemin de fichier ou un nom valide.
// Les redirections ne peuvent pas être suivies immédiatement par une autre redirection ou un opérateur (|).
// Si une redirection est suivie d'un token invalide, une erreur de syntaxe doit être levée.
// Pipes (|) :

// Le token précédent et le token suivant un pipe doivent obligatoirement être des commandes valides.
// Un pipe en début ou en fin de commande est une erreur de syntaxe.
// Les pipes divisent les commandes en sous-sections à exécuter séquentiellement.
// Commandes :

// Une commande est toujours le premier token d'une section (ou après un pipe).
// Si un token commence par un caractère alphanumérique ou /, il est interprété comme une commande.
// Les commandes peuvent être suivies de :
// Options : tokens commençant par - (exemple : ls -l).
// Arguments : tokens qui ne sont ni des redirections ni des opérateurs (|).
// Arguments et options :

// Tout token après une commande qui n'est pas une redirection, un opérateur, ou une fin de ligne est considéré comme un argument ou une option.
// Les arguments suivent l'ordre strict d'apparition et ne doivent pas être mélangés avec des opérateurs.
// Quotations (', ") :

// Les chaînes entre guillemets simples (') ne permettent aucune expansion (exemple : $USER est traité comme une chaîne littérale).
// Les guillemets doubles (") permettent l'expansion de variables ($USER sera interprété).
// Les guillemets doivent être fermés avant la fin de la ligne.
// Variables d'environnement ($) :

// Un token commençant par $ est interprété comme une variable d'environnement à développer.
// Si la variable n'existe pas, elle est remplacée par une chaîne vide.
// Fin de ligne :

// La ligne est terminée lorsqu'il n'y a plus de tokens.
// Une redirection ou un pipe non suivi d'un autre token est une erreur de syntaxe.
