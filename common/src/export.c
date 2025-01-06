/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:28:15 by kbaga             #+#    #+#             */
/*   Updated: 2025/01/06 15:42:02 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	ext_val(char *arg, t_env_node *node)
// {
// 	int	i;

// 	i = 0;
// 	if (!arg)
// 		return (0);
// 	while (arg[i] != '=')
// 		i++;
// 	node->key = ft_strndup(arg, i);
// 	if (arg[i] == '=')
// 		i++;
// 	node->val = ft_strdup(arg + i);
// 	if (arg[i] == '=' && !node->val)
// 	{
// 		free(node->key);
// 		return (0);
// 	}
// 	return (1);
// }

// void	node_free(t_env_node *node)
// {
// 	free(node->key);
// 	free(node->val);
// 	free(node);
// }
void	node_free(t_env_node *node)
{
	free(node->key);
	free(node->val);
	free(node);
}

int	export_args(t_shell *shell, char **args)
{
	int			i;

	i = 0;
	while (args[i] != NULL)
	{
		if (!is_valid_id(args[i]))
		{
			i++;
			continue ;
		}
		if (!ft_strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		if (!create_add(shell, args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	export(t_shell *shell, char **args)
{
	if (!args || !*args)
	{
		if (!exp_no_args(shell->environ))
			return (0);
		return (1);
	}
	if (!export_args(shell, args))
		return (0);
	return (1);
}

void	exporting(t_shell *shell, char *str)
{
	t_env_node	*node;
	int			pos;
	char		*key;

	if (!shell || !str)
	{
		export(shell, NULL);
		return ;
	}
	pos = 0;
	key = ext_key(str, &pos);
	if (!key)
		return ;
	node = get_node(shell->environ, key);
	if (node)
	{
		existing_node(node, str, pos);
		free(key);
		return ;
	}
	new_node(shell->environ, key, str, pos);
}

// void	exporting(t_shell *shell, t_lx *curr)
// {
// 	t_env_node	*node;
// 	int			pos;
// 	char		*key;

// 	if (!shell || !curr->str || curr)
// 	{
// 		export(shell, NULL);
// 		return ;
// 	}
// 	pos = 0;
// 	key = ext_key(curr->str, &pos);
// 	if (!key)
// 		return ;
// 	node = get_node(shell->environ, key);
// 	if (node)
// 	{
// 		existing_node(node, curr->str, pos);
// 		free(key);
// 		return ;
// 	}
// 	else
// 		new_node(shell->environ, key, curr->str, pos);
// 	free(key);
// 	curr = curr->next;
// }

/*
int main() {
    t_shell shell;
    shell.environ = malloc(sizeof(t_env));
	char *str = NULL;
    if (!shell.environ)
        return 1;
    shell.environ->head = NULL;

    // Cas 1 : Ajout d'une nouvelle variable
	exporting(&shell, "USER=kbaga");
    exporting(&shell, "HOME=/home/kbaga");
    exporting(&shell, "PATH=/usr/bin:/bin");

    // Affichage des variables
    printf("\nVariables d'environnement actuelles :\n");
    exporting(&shell, str);
	exporting(&shell, "HOME=pipicaca");
    // Cas 2 : Mise à jour d'une variable existante
	char *unset_args[] = {"PATH", "USER", NULL};
	unset(&shell, unset_args);

    // Affichage des variables
    printf("\nVariables d'environnement après mise à jour :\n");
    exporting(&shell, NULL);

    // Nettoyage de la mémoire
    free_env(shell.environ);

    return 0;
}
*/
