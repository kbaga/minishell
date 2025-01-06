/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:38:02 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/06 16:38:10 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_env_node *env)
{
	t_env_node	*temp;

	if (!env)
		return ;
	temp = env;
	while (temp)
	{
		if (temp->key && temp->val)
			printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
}
