/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:31:25 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/08 17:59:44 by kbaga            ###   ########.fr       */
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
		if (shell->rl_input)
		{
			free(shell->rl_input);
			shell->rl_input = NULL;
		}
		return (0);
	}
	return (1);
}

/*
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

int main(void)
{
    t_shell shell;  // Initialisation de la structure shell
    char *input = NULL;  // Pointeur qui contiendra la ligne saisie
    size_t len = 0;      // Taille de la ligne lue
    ssize_t read_len;    // Nombre de caractères lus
    int result;

    // Boucle infinie simulant un shell avec des entrées utilisateur
    while (1)
    {
        // Afficher le prompt et lire l'entrée utilisateur avec getline
        printf("minishell> ");
        read_len = getline(&input, &len, stdin);  // Lire l'entrée utilisateur

        if (read_len == -1)  // Si l'utilisateur tape Ctrl-D ou qu'il y a une erreur
        {
            printf("exit\n");
            break;
        }

        // Retirer le caractère de nouvelle ligne à la fin de la ligne lue
        if (input[read_len - 1] == '\n')
            input[read_len - 1] = '\0';

        // Stocker l'entrée utilisateur dans la structure shell
        shell.rl_input = ft_strdup(input);  // On copie l'entrée utilisateur pour la manipuler
        shell.lex_head = NULL;
        shell.rl_copy = NULL;

        // Appeler la fonction parser pour traiter l'entrée
        result = parser(&shell);
        if (result == 1)
        {
            printf("Parsing réussi !\n");
            // Appeler la fonction pour afficher les tokens générés
            print_tokens(shell.lex_head);
        }
        else
        {
            printf("Échec du parsing.\n");
        }

        // Libérer les ressources allouées par parser et autres
        if (shell.lex_head)
		{
			free_lex(shell.lex_head);
			shell.lex_head = NULL;
		}
        if (shell.rl_copy)
		{
            free(shell.rl_copy);
			shell.rl_copy = NULL;
		}
    }

    // Libérer l'entrée utilisateur allouée par getline
    free(input);

    return 0;
}

*/
