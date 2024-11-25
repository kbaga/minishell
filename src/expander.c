/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:17:38 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/25 15:37:31 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
int	expand_var(t_shell *shell, char **s, t_exp *exp, int i)
{
	char	var_name[256];
	int		var_len;
	char	*var_val;
	char	*copy_s = *s;
	char	*remaining;
	
	if (!shell || !s || !*s || !exp)
	{
		printf("expand_var: Invalid param passed\n");
		return (-1);
	}
	i++;
	var_len = 0;
	printf("expand_var: Starting with i=%d, *s=[%s]\n", i, copy_s);
	while (copy_s[i] && copy_s[i] != ' ' && copy_s[i] != '$' && copy_s[i] != '\'' && copy_s[i] != '\"' && var_len < 255 && copy_s[i] != '/')
	{
		printf("expand_var: Inspecting char [%c] at i=%d\n", copy_s[i], i);
		var_name[var_len++] = copy_s[i++];
	}
	var_name[var_len] = '\0';
	var_val = getenv(var_name);
	printf("expand_var: FOund variable name [%s]\n", var_name);
	if (!var_val)
		var_val = "";
	printf("expand_var: resolved value [%s]\n", var_val);
	exp->res = ft_join_exp(exp->res, var_val);
	if (!exp->res)
		return (-1);
	if (copy_s[i])
	{
		remaining =  ft_strdup(copy_s + i);
		if (!remaining)
			return (-1);
		printf("expand_var: Remaining string [%s]\n", remaining);
		exp->res = ft_join_exp(exp->res, remaining);
		free(remaining);
	}
	printf("expand_var: Updated res=[%s]\n", exp->res);
	return (i);
}
*/

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
	i = extract_var_name(*s, i + 1, var_name, 256);
	var_val = get_var_value(shell, var_name);
	exp->res = ft_join_exp(exp->res, var_val);
	if (!exp->res)
		return (-1);
	return (i - 1);
}

// int	expand_var(t_shell *shell, char **s, t_exp *exp, int i)
// {
// 	char	var_name[256];
// 	int		var_len;
// 	char	*var_val;

// 	if (!shell || !s || !*s || !exp)
// 		return (-1);
// 	i++;
// 	var_len = 0;
// 	while ((*s)[i] && (*s)[i] != ' ' && (*s)[i] != '$' && (*s)[i] != '\'' && (*s)[i] != '\"' && (*s)[i] != '/' && var_len < 255)
// 		var_name[var_len++] = (*s)[i++];
// 	var_name[var_len] = '\0';
// 	var_val = get_var_value(shell, var_name); //Ce sera notre array a la place
// 	if (!var_val)
// 		var_val = "[undefined]";
// 	exp->res = ft_join_exp(exp->res, var_val);
// 	if (!exp->res)
// 		return (-1);
// 	return (i - 1);
// }

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

/*
t_env	*init_env()
{
	t_env	*env = malloc(sie space to scroll downeof(t_env));
	t_env_node *user = malloc(sizeof(t_env_node));
	user->key = ft_strdup("USER");
	user->val = ft_strdup("kbaga");
	user->next = NULL;
	env->head = user;
	return env;
}

void	free_env(t_env *env)
{
	t_env_node *node = env->head;
	while (node)
	{
		t_env_node *temp = node;
		node = node->next;
		free(temp->key);
		free(temp->val);
		free(temp);
	}
	free(env);
}

int	main()
{
	t_shell	shell;
	shell.environ = init_env();
	shell.rl_input = ft_strdup("echo hello, $SYSTEMD_EXEC_PID");
	shell.rl_copy = ft_strdup(shell.rl_input);
	printf("BEFORE EXPANDER : %s \n", shell.rl_input);
	if (expander(&shell))
	{
		printf("Expanded command: %s\n", shell.rl_copy);
	}
	else
		printf("Expansion failed.\n");
	free(shell.rl_input);
	free(shell.rl_copy);
	free_env(shell.environ);
	return (0);
}
*/
