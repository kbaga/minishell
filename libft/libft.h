/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:57:34 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/08 15:33:18 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strndup(char *s, int i);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *s1, char *s2, int len);
char	*ft_strpbrk(const char *s1, const char *c);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
#endif
