/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:17:38 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/19 18:52:10 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	extract_var_name(char *input, int i, char *var_name, int max_len)
{
	int	var_len;

	var_len = 0;
	while (input[i] && input[i] != ' ' && input[i] != '$' && input[i] != '\''
		&& input[i] != '\"' && input[i] != '/' && var_len < max_len - 1)
		var_name[var_len++] = input[i++];
	var_name[var_len] = '\0';
	return (i);
}

char	*get_var_value(t_shell *shell, char *var_name)
{
	t_env_node	*node;

	node = get_node(shell->environ, var_name);
	if (!node)
		return ("[undefined]");
	return (node->val);
}

int	expand_var(t_shell *shell, char **s, t_exp *exp, int i)
{
	char	var_name[256];
	char	*var_val;

	if (!shell || !s || !*s || !exp)
		return (-1);
	printf("expand var\n");
	i = extract_var_name(*s, i + 1, var_name, 256);
	var_val = get_var_value(shell, var_name);
	exp->res = ft_join_exp(exp->res, var_val);
	if (!exp->res)
		return (-1);
	return (i - 1);
}

//RISQUE DE LEAKS DANS EXP s
int	expander(t_shell *shell)
{
	t_exp	*exp;
	int		i;

	if (!shell || !shell->rl_copy)
		return (0);
	i = 0;
	exp = init_exp(shell->rl_copy);
	while (exp->str[i] != '\0')
	{
		if (exp->str[i] == '$')
			i = expand_var(shell, &shell->rl_copy, exp, i);
		else
		{
			if (!handle_char(exp, exp->str[i]))
				return (0);
			i++;
		}
		if (i == -1)
			return (0);
	}
	free(shell->rl_copy);
	shell->rl_copy = ft_strdup(exp->res);
	free_exp(exp);
	return (1);
}
