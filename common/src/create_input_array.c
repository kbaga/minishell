/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:23:14 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/09 14:38:36 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	len_substr(char *str)
{
	int		i;
	char	*tokens;

	i = 0;
	tokens = "<>|";
	while (str[i])
	{
		if (str[i] == ' ' || ft_strchr(tokens, str[i]))
			return (i);
		if (ft_strchr("\'\"", str[i]))
		{
			no_delim_found(str, &i);
		}
		else
			i++;
	}
	return (i);
}

int	find_token(char **arr, char *s, int arr_size)
{
	t_token_ctx	ctx;
	int			i;

	ctx.arr = arr;
	ctx.s = s;
	ctx.arr_size = arr_size;
	ctx.index = 0;
	i = 0;
	if (!arr || !s)
	{
		printf("ERROR: NULL arr or string passed to find_token\n");
		return (-1);
	}
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (process_token(&ctx, &i) == -1)
			return (-1);
	}
	return (ctx.index);
}

int	count_el(char *rl_copy)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	word = 0;
	while (rl_copy[i])
	{
		while (rl_copy[i] == ' ' || rl_copy[i] == '\t')
			i++;
		if (rl_copy[i] == '\0')
			break ;
		len = is_token(rl_copy + i);
		if (len > 0)
		{
			word++;
			i++;
		}
		else
		{
			len = len_substr(rl_copy + i);
			if (len > 0)
				word++;
			i += len;
		}
	}
	return (word);
}

char	**fill_arr(char **arr, char *input)
{
	int		arr_size;

	if (!arr || !input)
	{
		perror("Allocation error fill_arr");
		return (NULL);
	}
	arr_size = count_el(input);
	if (find_token(arr, input, arr_size) == -1)
	{
		perror("Error filling array with tokens");
		free_arr(arr, arr_size);
		return (NULL);
	}
	arr[arr_size] = NULL;
	return (arr);
}

char	**create_arr(t_shell *shell)
{
	char	**arr;
	char	*inp_copy;
	int		index;

	inp_copy = shell->rl_copy;
	if (!inp_copy)
		exit(1);
	index = count_el(inp_copy);
	arr = (char **)malloc(sizeof(char *) * (index + 1));
	if (!arr)
	{
		perror("Error create_arr");
		return (NULL);
	}
	for (int i = 0; i <= index; i++)
		arr[i] = NULL;
	if (!fill_arr(arr, inp_copy))
	{
		free_arr(arr, index);
		return (NULL);
	}
	return (arr);
}
