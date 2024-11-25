/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:53:43 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/21 12:44:01 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*realloc_str(char *res, int pos)
{
	char	*new_res;
	int		new_size;

	new_size = pos * 2;
	new_res = malloc(new_size);
	if (!new_res)
	{
		free(res);
		return (NULL);
	}
	ft_memcpy(new_res, res, pos);
	free(res);
	return (new_res);
}

t_exp	*init_exp(char *str)
{
	t_exp	*exp;

	exp = malloc(sizeof(t_exp));
	exp->begining = NULL;
	exp->res = ft_strdup("");
	exp->invalid = NULL;
	exp->env_val = NULL;
	exp->var = NULL;
	exp->conv = NULL;
	exp->str = ft_strdup(str);
	exp->pos = 0;
	exp->len = 0;
	exp->recently_invalid = 0;
	exp->expanded = 0;
	exp->flag = 0;
	return (exp);
}

static int	get_len(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	return (len1 + len2 + 1);
}

static void	copy_str(char *des, char *s, int *index)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		des[*index] = s[i];
		(*index)++;
		i++;
	}
}

char	*ft_join_exp(char *s1, char *s2)
{
	char	*newstr;
	int		total_len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	total_len = get_len(s1, s2);
	newstr = (char *)malloc(total_len);
	if (!newstr)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	if (s1)
		copy_str(newstr, s1, &i);
	if (s2)
		copy_str(newstr, s2, &i);
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}
