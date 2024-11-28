/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:47:09 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/28 16:31:02 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	equal_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	existing_node(t_env_node *node, char *arg, int pos)
{
	if (arg[pos] == '=')
	{
		free(node->val);
		node->val = ft_strdup(arg + pos + 1);
	}
}

char	*ext_key(char *str, int *pos)
{
	if (!str || !is_valid_id(str))
		return (NULL);
	*pos = equal_pos(str);
	return (ft_strndup(str, *pos));
}

void	new_node(t_env *env, char *key, char *arg, int pos)
{
	t_env_node	*node;

	if (arg[pos] != '=')
	{
		free(key);
		return ;
	}
	pos++;
	node = malloc(sizeof(t_env_node));
	if (!node)
		return ;
	node->key = key;
	node->val = ft_strdup(arg + pos);
	node->next = NULL;
	if (!add_node(env, node))
		node_free(node);
}

// int	exp_no_args(t_shell *shell)
// {
// 	t_env		*env;
// 	t_env_node	*node;

// 	env = shell->environ;
// 	node = env->head;
// 	if (!node)
// 		return (0);
// 	while (node != NULL)
// 	{
// 		printf("declare -x %s=%s\n", node->key, node->val);
// 		node = node->next;
// 	}
// 	return (1);
// }

int	exp_no_args(t_env *env)
{
	t_pair	*pairs;
	int		count;

	if (!env || !env->head)
		return (0);
	count = count_env_nodes(env);
	pairs = create_env_array(env, count);
	if (!pairs)
		return (0);
	sort_env_array(pairs, count);
	print_env_array(pairs, count);
	free_env_arr(pairs, count);
	return (1);
}

void	node_free(t_env_node *node)
{
	free(node->key);
	free(node->val);
	free(node);
}
