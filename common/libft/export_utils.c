/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:44:59 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/28 04:00:17 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env_node	*get_node(t_env *env, char *key)
{
	t_env_node	*curr;

	if (!env || !key)
		return (NULL);
	curr = env->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[i]) && arg[i] != '_'))
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//RISQUE DE LEAKS ! MAIS FLEMME DE SECURISER

t_env_node	*create_node(char *var)
{
	t_env_node	*new_node;
	int			i;

	if (!var)
		return (NULL);
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	new_node->key = ft_strndup(var, i);
	if (var[i] == '=')
		i++;
	new_node->val = ft_strdup(var + i);
	new_node->next = NULL;
	return (new_node);
}

t_env_node	*add_node(t_env *env, t_env_node *node)
{
	t_env_node	*curr;

	if (!env || !node)
		return (NULL);
	if (!env->head)
	{
		env->head = node;
		node->next = NULL;
		return (node);
	}
	curr = env->head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->next = NULL;
	return (node);
}


/////////////////////


int	ext_val(char *arg, t_env_node *node)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i] != '=')
		i++;
	node->key = ft_strndup(arg, i);
	if (arg[i] == '=')
		i++;
	node->val = ft_strdup(arg + i);
	if (arg[i] == '=' && !node->val)
	{
		free(node->key);
		return (0);
	}
	return (1);
}

/*
int main()
{
	t_env	env = {NULL};
	// Création de nœuds d'exemple
    t_env_node *node1 = create_node("USER=kbaga");
    t_env_node *node2 = create_node("HOME=/home/kbaga");

    // Ajout des nœuds à la liste
    add_node(&env, node1);
    add_node(&env, node2);

    // Affichage de la liste pour vérifier
    t_env_node *curr = env.head;
    while (curr)
    {
        printf("Clé : %s, Valeur : %s\n", curr->key, curr->val);
        curr = curr->next;
    }

    // Libération de la mémoire
    curr = env.head;
    while (curr)
    {
        t_env_node *temp = curr;
        curr = curr->next;
        free(temp->key);
        free(temp->val);
        free(temp);
    }

    return 0;
}
*/
