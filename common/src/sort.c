/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:01 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/24 11:19:52 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_env_nodes(t_env *env)
{
	t_env_node	*node;
	int			count;

	count = 0;
	node = env->head;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

t_pair	*create_env_array(t_env *env, int count)
{
	t_env_node	*node;
	t_pair		*pairs;
	int			i;

	pairs = malloc(sizeof(t_pair) * count);
	if (!pairs)
		return (NULL);
	i = 0;
	node = env->head;
	while (node)
	{
		pairs[i].key = node->key;
		pairs[i].val = node->val;
		node = node->next;
		i++;
	}
	return (pairs);
}

void	sort_env_array(t_pair *pairs, int count)
{
	int		i;
	int		j;
	t_pair	temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(pairs[i].key, pairs[j].key) > 0)
			{
				temp = pairs[i];
				pairs[i] = pairs[j];
				pairs[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_array(t_pair *pairs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pairs[i].val)
			printf("declare -x %s=\"%s\"\n", pairs[i].key, pairs[i].val);
		else
			printf("declare -x %s=\n", pairs[i].key);
		i++;
	}
}

void	free_env_arr(t_pair *pairs, int count)
{
	(void)count;
	free(pairs);
}
