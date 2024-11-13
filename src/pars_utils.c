/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:07:26 by kbaga             #+#    #+#             */
/*   Updated: 2024/10/16 15:29:25 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pars_check(char *str)
{
	int		i;
	char	*invalid;
	int		s_quote;
	int		d_quote;

	i = 0;
	invalid = "\\;&()";
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_quote = !s_quote;
		else if (str[i] == '\"')
			d_quote = !d_quote;
		i++;
	}
	if (d_quote || s_quote)
		return (0);
	if (ft_strpbrk(str, invalid) != NULL)
		return (0);
	return (1);
}

/*
int main() {
    // Quelques exemples de chaînes de test
    char *test1 = "Hello 'world'";   // Correct
    char *test2 = "Hello 'world";    // Incorrect (guillemet simple non fermé)
    char *test3 = "Hello \"world\""; // Correct
    char *test4 = "Hello \"world";   // Incorrect (guillemet double non fermé)
    char *test5 = "Hello \\world";   // Incorrect (caractère invalide '\')
    char *test6 = "Hello (world)";   // Incorrect (caractère invalide '(' et ')')

    // Test de la fonction pars_check sur les différentes chaînes
    printf("Test 1: %s\n", pars_check(test1) ? "Valid" : "Invalid");
    printf("Test 2: %s\n", pars_check(test2) ? "Valid" : "Invalid");
    printf("Test 3: %s\n", pars_check(test3) ? "Valid" : "Invalid");
    printf("Test 4: %s\n", pars_check(test4) ? "Valid" : "Invalid");
    printf("Test 5: %s\n", pars_check(test5) ? "Valid" : "Invalid");
    printf("Test 6: %s\n", pars_check(test6) ? "Valid" : "Invalid");

    return 0;
}
*/
