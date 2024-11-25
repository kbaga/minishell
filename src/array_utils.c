/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:08:30 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/24 17:40:11 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*add_substr(char *str, int i, int k)
{
	char	*substr;

	if (!str || k <= 0)
	{
		printf("ERROR:invalid substring param\n");
		return (NULL);
	}
	substr = (char *)malloc(sizeof(char) * (k + 1));
	if (!substr)
		return (NULL);
	ft_strncpy(substr, str + i, k);
	substr[k] = '\0';
	return (substr);
}

int	proc_tok(char **arr, char *s, int *i, int *j)
{
	if (!arr || !s || !j || !j || *i < 0 || *j < 0)
	{
		printf("ERROR: Invalid input or index out of bounds");
		return (-1);
	}
	printf("proc_tok: Adding token [%c] at index %d\n", s[*j], *i);
	arr[*i] = add_substr(s, *j, 1);
	if (!arr[*i])
		return (-1);
	(*i)++;
	(*j)++;
	return (0);
}

int	handle_token(t_token_ctx *ctx, int start, int len)
{
	if (ctx->index >= ctx->arr_size)
	{
		printf("ERROR: Out of bounds write at index %d\n", ctx->index);
		return (-1);
	}
	ctx->arr[ctx->index++] = add_substr(ctx->s, start, len);
	if (!ctx->arr[ctx->index - 1])
		return (-1);
	return (0);
}

int	process_token(t_token_ctx *ctx, int *i)
{
	int	start;

	start = *i;
	while (ctx->s[*i] && !is_token(ctx->s[*i]) && ctx->s[*i] != ' ')
	{
		if (ft_strchr("\'\"", ctx->s[*i]))
			no_delim_found(ctx->s, i);
		else
			(*i)++;
	}
	if (*i > start && handle_token(ctx, start, *i - start) == -1)
		return (-1);
	if (ctx->s[*i] && is_token(ctx->s[*i]))
	{
		if (handle_token(ctx, *i, 1) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}
