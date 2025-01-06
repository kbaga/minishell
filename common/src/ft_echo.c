/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:39:39 by lakamba           #+#    #+#             */
/*   Updated: 2024/12/19 18:39:43 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(char **execs, t_shell *shell)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (execs[i] && ft_strcmp(execs[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (execs[i])
	{
		printf("%s", execs[i]);
		if (execs[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	shell->exit_status = 0;
}
