/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:04:57 by lakamba           #+#    #+#             */
/*   Updated: 2024/11/25 11:26:21 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  is_numeric(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isalnum(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    ft_exit(t_shell *shell, t_lx *args)
{
    int exit_code;

    if (args && args->next)
    {
        printf("exit: too many arguments\n");
        shell->exit_status = 127;
        return ;
    }
    printf("exit\n");
    if (args && args->str && !is_numeric(args->str))
    {
        printf("exit: %s: numeric argument required\n", args->str);
        exit_code = 2;
    }
    else if (args && args->str)
        exit_code = atoi(args->str);
    else
        exit_code = shell->exit_status;
    free_env(shell->environ);
    free_lex(shell->lex_head);
    //free(shell);
    exit(exit_code);
}