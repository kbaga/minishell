/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:31:25 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/24 19:35:22 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	check_pipe(t_lx *lexer)
{
	t_lx	*curr;

	curr = lexer;
	if (!lexer)
		return (0);
	while (curr != NULL)
	{
		if (curr->type == PIPE)
		{
			if (curr->prev == NULL
				|| curr->prev->type == PIPE)
				return (0);
			if (curr->next == NULL
				|| curr->next->type == PIPE)
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
t_lx	*lexer(t_shell *shell)
{
	char	*new_str;

	if (shell->rl_copy)
		free(shell->rl_copy);
	new_str = clean_rl(shell->rl_input);
	if (new_str == NULL)
	{
		perror("ERROR ; Bad syntax");
		return (NULL);
	}
	shell->rl_input = new_str;
	shell->lex_head = tokenize(shell);
	if (!check_pipe(shell->lex_head))
	{
		perror("ERR: invalid pipe syntax");
		free_lex(shell->lex_head);
		shell->rl_input = NULL;
		return (NULL);
	}
	shell->rl_copy = new_str;
	return (shell->lex_head);
}
*/
/*
t_lx	*lexer(t_shell *shell)
{
	char	**input_arr;
	t_lx	*lex_head;
	char	*new_str;
	
	if (!shell || !shell->rl_input)
		return (NULL);
	new_str = clean_rl(shell->rl_input);
	if (!new_str)
	{
		perror("ERROR: Bad syntax");
		exit(1);
		//return (NULL);
	}
	if (shell->rl_copy)
		free(shell->rl_copy);
	//shell->rl_copy = ft_strdup(new_str);
	shell->rl_copy = new_str;
	input_arr = create_arr(shell);
	if (!input_arr)
	{
		free(shell->rl_copy);
		shell->rl_copy = NULL;
		return (NULL);
	}
	for (int i = 0; input_arr[i]; i++)
		printf("input_array[%d] = %s\n", i, input_arr[i]);
	lex_head = create_lexer_list(input_arr);
	free_tab(input_arr);
	if (!lex_head)
	{
		perror("ERROR: Lexer list is empty");
		free(shell->rl_copy);
		shell->rl_copy = NULL;
		return (NULL);
	}

	if (!check_pipe(lex_head))
	{
		perror("ERROR: invalid pipe syntax");
		free_lex(lex_head);
		free(shell->rl_copy);
		shell->rl_copy = NULL;
		return (NULL);
	}
	//ATTENTION
	free(shell->rl_copy);
	return (lex_head);
}
*/

t_lx	*lexer_clean(t_shell *shell, t_lx *lex_head)
{
	if (shell->rl_copy)
	{
		free(shell->rl_copy);
		shell->rl_copy = NULL;
	}
	if (lex_head)
		free_lex(lex_head);
	return (NULL);
}

t_lx	*lexer(t_shell *shell)
{
	char	**input_arr;
	t_lx	*lex_head;

	if (!shell || !shell->rl_input)
		return (NULL);
	shell->rl_copy = clean_rl(shell->rl_input);
	if (!shell->rl_copy)
		return (NULL);
	input_arr = create_arr(shell);
	if (!input_arr)
		return (lexer_clean(shell, NULL));
	lex_head = create_lexer_list(input_arr);
	free_tab(input_arr);
	if (!lex_head)
		return (lexer_clean(shell, NULL));
	if (!check_pipe(lex_head))
		return (lexer_clean(shell, lex_head));
	free(shell->rl_copy);
	shell->rl_copy = NULL;
	return (lex_head);
}

void	process_tokens(t_shell *shell, t_lx *tokens)
{
	t_lx *curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == COMMAND)
		{
			execute_cmd(shell, curr);
			if (shell->exit_status != 0)
				break ;
		}
		else if (curr->type == PIPE)
		{
			printf("Pipe detected but not yet implemented\n");
			shell->exit_status = 127;
		}
		curr = curr->next;
	}
}

int	parser(t_shell *shell)
{
	if (shell->lex_head)
	{
		free_lex(shell->lex_head);
		shell->lex_head = NULL;
	}
	shell->lex_head = lexer(shell);
	if (shell->lex_head == NULL)
	{
		if (shell->rl_copy)
		{
			free(shell->rl_copy);
			shell->rl_copy = NULL;
		}
		return (0);
	}
	interpolate_tokens(shell);
	process_tokens(shell, shell->lex_head);
	return (1);
}

void print_tokens(t_lx *lex_head)
{
	t_lx *current = lex_head;
	while (current != NULL)
	{
		// Affiche le token et son type
		printf("Token: %s, Type: ", current->str);
		switch (current->type)
		{
			case COMMAND:
				printf("COMMAND\n");
				break;
			case PIPE:
				printf("PIPE\n");
				break;
			case TRUNCATE:
				printf("TRUNCATE (>)\n");
				break;
			case APPEND:
				printf("APPEND (>>)\n");
				break;
			case REDIRECT_INPUT:
				printf("REDIRECT_INPUT (<)\n");
				break;
			case HEREDOC:
				printf("HEREDOC (<<)\n");
				break;
			default:
				printf("UNKNOWN\n");
				break;
		}
		current = current->next;
	}
}
/*
int	main()
{
	t_shell	*shell;
	
	shell = malloc(sizeof(t_shell));
	shell->lex_head = NULL;
	shell->rl_input = ft_strdup("echo hello >> file.txt | cat < input.txt |");
	shell->rl_copy = NULL;
	if (!parser(shell))
	{
		printf("Error: parsing input\n");
		free(shell);
		return (1);
	}
	print_tokens(shell->lex_head);
	if (shell->rl_copy)
		free(shell->rl_copy);
	free_lex(shell->lex_head);
	free(shell);
	return (0);
}
*/
// // Fonction principale
// int main()
// {
//     t_shell *shell;

//     shell = malloc(sizeof(t_shell));
//     if (!shell)
//     {
//         perror("Failed to allocate shell");
//         return (1);
//     }

//     shell->lex_head = NULL;
//     shell->rl_input = ft_strdup(" echo    |     $1bomaye echo  $SHELL/input.txt      |             grep .");
//     shell->rl_copy = NULL;

//     if (!parser(shell))
//     {
//         printf("Error: parsing input\n");
//         free(shell->rl_input);
// 		shell->rl_input = NULL;
//         free(shell);
//         return (1);
//     }
//     print_tokens(shell->lex_head);

// 	if (shell->rl_input)
// 		free(shell->rl_input);
// 	free_lex(shell->lex_head);
// 	free(shell);
//     return (0);
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_shell *shell;

//     // Initialize shell structure
// 	(void)argv;
// 	(void)argc;
// 	shell = init_shell(envp);
// 	if (!shell->environ)
//     {
//         perror("Failed to initialize environment");
//         return (1);
//     }
// 	// Input for testing
//     shell->rl_input = ft_strdup("env");
//     if (!shell->rl_input)
//     {
//         perror("Failed to allocate input");
//         return (1);
//     }

//     printf("Testing parser and command execution...\n");
//     if (!parser(shell))
//     {
//         printf("Error: parsing input failed.\n");
//     }

//     // Cleanup
//     free_env(shell->environ);
//     return (0);
// }

// Function to handle input line
void handle_line(t_shell *shell, char *line)
{
    if (!line || !*line)
        return;

    // Set the shell's input
    shell->rl_input = ft_strdup(line);
    if (!shell->rl_input)
    {
        perror("Failed to allocate input string");
        return;
    }

    // Parse and execute the input
    if (!parser(shell))
    {
        printf("Parsing failed for input: %s\n", line);
        shell->exit_status = 1;
    }

    // Cleanup after execution
    free(shell->rl_input);
    shell->rl_input = NULL;
}

// Reset any necessary shell states after each command
void reset_shell(t_shell *shell)
{
    if (shell->lex_head)
    {
        free_lex(shell->lex_head);
        shell->lex_head = NULL;
    }
}

// Main loop for minishell
int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    char *line;

    (void)argc;
    (void)argv;

    // Initialize the shell structure
    shell.environ = init_env(envp);
    if (!shell.environ)
    {
        perror("Failed to initialize environment");
        return (1);
    }
    shell.lex_head = NULL;
    shell.rl_input = NULL;
    shell.rl_copy = NULL;
    shell.exit_status = 0;

    while (1)
    {
        // Signal handling (customize run_signal for your shell)

        // Prompt for input
        line = readline("minishell> ");
        if (!line)
        {
            printf("\nexit\n"); // Handle Ctrl+D (end-of-file)
			ft_exit(&shell, NULL);
		}
		// Process the line
        handle_line(&shell, line);
        // Reset shell state
        reset_shell(&shell);
        // Free the input line
        free(line);
        line = NULL;
    }

    // Cleanup before exiting
    free_env(shell.environ);
    return (0);
}
