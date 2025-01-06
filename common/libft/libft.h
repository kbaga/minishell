/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:57:34 by kbaga             #+#    #+#             */
/*   Updated: 2024/12/19 18:36:04 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
void	ft_free_tab(char **tab);
char	*ft_strndup(char *s, int i);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_itoa(int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin2(const char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *s1, char *s2, int len);
char	*ft_strpbrk(const char *s1, const char *c);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
#endif
