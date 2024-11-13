/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:23:14 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/13 15:11:35 by kbaga            ###   ########.fr       */
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
			no_delim_found(str, &i);
		else
			i++;
	}
	return (i);
}

int	find_token(char **arr, char *s, int index)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (s[i])
	{
		while (s[i] && !is_token(s[i]) && s[i] != ' ')
			i++;
		if (i > start)
		{
			arr[index] = add_substr(s, start, i - start);
			if (!arr[index])
				return (-1);
			index++;
		}
		if (s[i] && is_token(s[i]))
		{
			if (proc_tok(arr, s, &index, &i) == -1)
				return (-1);
		}
		while (s[i] == ' ')
			i++;
		start = i;
	}
	return (index);
}

int	count_el(char *rl_copy)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	word = 0;
	while (rl_copy)
	{
		while (rl_copy[i] == ' ' || rl_copy[i] == '\t')
			i++;
		if (rl_copy[i] == '\0')
			break ;
		len = len_substr(rl_copy + i);
		if (len > 0)
			word++;
		i += len;
		if (rl_copy[i] && is_token(rl_copy[i]))
		{
			word++;
			i++;
		}
	}
	return (word);
}

char	**fill_arr(char **arr, char *input)
{
	int		index;

	if (!arr)
	{
		perror("Allocation error fill_arr");
		return (NULL);
	}
	index = find_token(arr, input, 0);
	if (index == -1)
	{
		perror("Error fill array");
		return (NULL);
	}
	return (arr);
}

char	**create_arr(t_shell *shell)
{
	char	**arr;
	char	*inp_copy;
	int		index;

	inp_copy = shell->rl_copy;
	if (!inp_copy)
	{
		perror("shell_copy is empty");
		exit(1);
	}
	printf("%s\n", inp_copy);
	index = count_el(inp_copy);
	arr = (char **)malloc(sizeof(char *) * (index + 1));
	if (!arr)
	{
		perror("Error create_arr");
		exit(1);
	}
	if (!fill_arr(arr, inp_copy))
	{
		perror("Memory alloc failed!");
		free(arr);
		exit(1);
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
