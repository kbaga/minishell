/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:35:05 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/18 20:32:30 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*void	free_env(t_env *env)
{
	t_env_node	*curr;
	t_env_node	*next_node;

	curr = env->head;
	while (curr != NULL)
	{
		next_node = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->val)
			free(curr->val);
		free(curr);
		curr = next_node;
	}
	env->head = NULL;
	free(env);
}
*/

void	free_arr(char **arr, int size)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < size)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_exec(t_exec *list)
{
	t_exec	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		if (temp->path)
			free_tab(temp->path);
		if (temp->execs)
			free_tab(temp->execs);
		free(temp);
	}
	list = NULL;
}

void	free_heap(t_shell *shell)
{
	if (shell->rl_input)
		free(shell->rl_input);
	if (shell->rl_copy)
		free(shell->rl_copy);
	if (shell->environ)
		free_env(shell->environ);
	if (shell->lex_head)
		free_lex(shell->lex_head);
	if (shell->executor)
		free_exec(shell->executor);
}

t_lx	*free_lex(t_lx *lex_head)
{
	t_lx	*curr;
	t_lx	*next_node;

	curr = lex_head;
	while (curr != NULL)
	{
		next_node = curr->next;
		if (curr->str)
			free(curr->str);
		free(curr);
		curr = next_node;
	}
	return (lex_head);
}
/*
int main() {
    // Allouer la structure shell
    t_shell *shell = malloc(sizeof(t_shell));

    // Allouer la mémoire pour rl_input et rl_copy 
	// (simulant une entrée utilisateur)
    shell->rl_input = ft_strdup("Commande de l'utilisateur");
    shell->rl_copy = ft_strdup("Copie de la commande");

    // Allouer et initialiser l'environnement
    shell->environ = malloc(sizeof(t_env));
    shell->environ->head = malloc(sizeof(t_env_node));
    shell->environ->head->key = ft_strdup("HOME");
    shell->environ->head->val = ft_strdup("/home/username");
    shell->environ->head->next = malloc(sizeof(t_env_node));
    shell->environ->head->next->key = ft_strdup("PATH");
    shell->environ->head->next->val = ft_strdup("/usr/bin:/bin");
    shell->environ->head->next->next = NULL;

    // Allouer et initialiser la liste lexer (tokens)
    shell->lex_head = malloc(sizeof(t_lx));
    shell->lex_head->str = ft_strdup("echo");
    shell->lex_head->type = COMMAND;
    shell->lex_head->next = malloc(sizeof(t_lx));
    shell->lex_head->next->str = ft_strdup("hello world");
    shell->lex_head->next->type = COMMAND;
    shell->lex_head->next->next = NULL;

    // Allouer et initialiser l'executor
    shell->executor = malloc(sizeof(t_exec));
    shell->executor->path = malloc(3 * sizeof(char *));
    shell->executor->path[0] = ft_strdup("/bin/echo");
    shell->executor->path[1] = ft_strdup("/bin/ls");
    shell->executor->path[2] = NULL;

    shell->executor->execs = malloc(3 * sizeof(char *));
    shell->executor->execs[0] = ft_strdup("echo");
    shell->executor->execs[1] = ft_strdup("ls");
    shell->executor->execs[2] = NULL;
    shell->executor->next = NULL;

    // Tester la fonction free_heap pour libérer tout ce qui a été alloué
    free_heap(shell);

    // Libérer la structure shell elle-même
    free(shell);

    printf("Toutes les ressources ont été libérées correctement.\n");

    return 0;
}
*/
