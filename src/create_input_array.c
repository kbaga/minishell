/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:23:14 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/24 18:09:24 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	len_substr(char *str)
{
	int		i;
	char	*tokens;

	i = 0;
	tokens = "<>|";
	//printf("len_substr: Processing substring [%s]\n", str);
	while (str[i])
	{
		if (str[i] == ' ' || ft_strchr(tokens, str[i]))
			return (i);
		if (ft_strchr("\'\"", str[i]))
		{
			//printf("len_substr:	Quote detected at index %d, skipping.\n", i);
			no_delim_found(str, &i);
		}
		else
			i++;
	}
	//printf("len_substr: Length determined to be %d\n", i);
	return (i);
}

/*
int	find_token(char **arr, char *s, int index)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	j = 0;
	start = 0;
	if (!arr || !s)
	{
		printf("ERROR: NULL arr or string passed to find_token\n");
		return (-1);
	}
	while (s[i])
	{
		while (s[i] && !is_token(s[i]) && s[i] != ' ')
			i++;
		if (i > start)
		{
			if (j >= index)
			{
				printf("ERROR: Out of bounds write at index %d\n", j);
				return (-1);
			}
			arr[j++] = add_substr(s, start, i - start);
			if (!arr[index])
				return (-1);
			index++;
		}
		if (s[i] && is_token(s[i]))
		{
			if (j >= index)
			{
				printf("ERROR: out of bounds write at index %d\n", index);
				return (-1);
			}
			printf("find_token: Processing token [%c] at index %d \n", s[i], index);
			arr[j++] = add_substr(s, i, 1);
			i++;
			//if (proc_tok(arr, s, &index, &i) == -1)
			//	return (-1);
		}
		while (s[i] == ' ')
			i++;
		start = i;
	}
	//MODIFIED
	arr[j] = NULL;
	printf("find_token: completed with index %d\n", index);
	return (j);
}
*/

/*
int	find_token(char **arr, char *s, int arr_size)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	index = 0;
	start = 0;
	if (!arr || !s)
		return (-1);
	while (s[i])
	{
		while (s[i] && !is_token(s[i]) && s[i] != ' ')
		{
			if (ft_strchr("\'\"", s[i]))
				no_delim_found(s, &i);
			else
				i++;
		}
		if (i > start)
		{
			if (index >= arr_size)
				return (-1);
			arr[index++] = add_substr(s, start, i - start);
			if (!arr[index - 1])
				return (-1);
		}
		if (s[i] && is_token(s[i]))
		{
			if (index > arr_size)
				return (-1);
			arr[index++] = add_substr(s, i, 1);
			i++;
		}
		while (s[i] == ' ')
			i++;
		start = i;
	}
	return (index);
}
*/

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
	//printf("find_token: completed with index %d\n", ctx.index);
	return (ctx.index);
}

//int process_substr()

/*
int	find_token(char **arr, char *s, int arr_size)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	index = 0;
	start = 0;
	if (!arr || !s)
	{
		printf("ERROR: NULL arr or string passed to find_token\n");
		return (-1);
	}
	while (s[i])
	{
		while (s[i] && !is_token(s[i]) && s[i] != ' ')
		{
			if (ft_strchr("\'\"", s[i]))
			{
				no_delim_found(s, &i);
			}
			else
			{
				i++;
			}
		}
		if (i > start)
		{
			if (index >= arr_size)
			{
				printf("ERROR: Out of bounds write at index %d\n", index);
				return (-1);
			}
			arr[index++] = add_substr(s, start, i - start);
			if (!arr[index - 1])
				return (-1);
		}
		if (s[i] && is_token(s[i]))
		{
			if (index > arr_size)
			{
				printf("ERROR: out of bounds write at index %d\n", index);
				return (-1);
			}
			printf("find_token: Processing token [%c] at index %d \n", s[i], index);
			arr[index++] = add_substr(s, i, 1);
			i++;
			//if (proc_tok(arr, s, &index, &i) == -1)
			//	return (-1);
		}
		while (s[i] == ' ')
			i++;
		start = i;
	}
	//MODIFIED
	//if (index < arr_size)
	//	arr[index] = NULL;
	printf("find_token: completed with index %d\n", index);
	return (index);
}
*/

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
		if (is_token(rl_copy[i]))
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
	int		index;
	int		arr_size;

	index = 0;
	if (!arr || !input)
	{
		perror("Allocation error fill_arr");
		return (NULL);
	}
	arr_size = count_el(input);
	index = find_token(arr, input, arr_size);
	if (index == -1)
	{
		perror("Error fill array");
		free_arr(arr, arr_size);
		return (NULL);
	}
	arr[index] = NULL;
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
/*	
int	main()
{
	t_shell	shell;

	shell.rl_copy =  ft_strdup("echo hello > file.txt | cat < input.txt");

	char	**output = create_arr(&shell);
	if (!output)
	{
		printf("Eroor");
		return (1);
	}

	printf("Tokens and substrings found:\n");
	for (int j = 0; output[j] != NULL; j++)
	{
		printf("output[%d]: %s\n", j, output[j]);
		free(output[j]);
	}
	free(output);
	free(shell.rl_copy);
	return (0);
}
*/
