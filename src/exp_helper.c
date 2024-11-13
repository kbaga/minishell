/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:59:54 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/08 17:58:32 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_var(t_shell *shell, t_exp *exp, int i)
{
	i = expand_var(shell, &shell->rl_copy, exp, i);
	if (i == -1)
	{
		free_exp(exp);
		return (-1);
	}
	return (i);
}

int	handle_char(t_exp *exp, char c)
{
	exp->res = ft_join_char(exp->res, c);
	if (!exp->res)
	{
		printf("Echec de l'ajout du caractere : %c\n", c);
		free_exp(exp);
		return (0);
	}
	return (1);
}

void	free_exp(t_exp *exp)
{
	if (!exp)
		return ;
	if (exp->begining)
		free(exp->begining);
	if (exp->res)
		free(exp->res);
	if (exp->invalid)
		free(exp->invalid);
	if (exp->env_val)
		free(exp->env_val);
	if (exp->var)
		free(exp->var);
	if (exp->str)
		free(exp->str);
	if (exp->conv)
		free(exp->conv);
	free(exp);
}

char	*ft_join_char(char *s, char c)
{
	char	*newstr;
	int		len;
	int		i;

	len = 0;
	if (s)
		len = ft_strlen(s);
	newstr = (char *)malloc(len + 2);
	if (!newstr)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	free(s);
	return (newstr);
}
