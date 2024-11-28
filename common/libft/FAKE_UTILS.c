#include "./libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// size_t	ft_strlen(const char *c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (c[i])
// 		i++;
// 	return (i);
// }

size_t	ft_strlcpy(char	*dst, const char *src, size_t	dstsize)
{
	size_t	len;

	len = 0;
	if (dstsize > 0)
	{
		while ((len + 1) < dstsize && src[len])
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = 0;
	}
	while (src[len])
		len++;
	return (len);
}

int	nb_str_split(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str && *str != c)
			str++;
	}
	return (count);
}

int	split_strlentgh(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char	*write_malloc(const char	*str, char c)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = split_strlentgh(str, c);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str[i] != c && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[len] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		tab_count;
	char	**splitted;

	splitted = malloc(sizeof(char *) * (nb_str_split(s, c) + 1));
	if (!s || !splitted)
		return (NULL);
	tab_count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		splitted[tab_count] = write_malloc(s, c);
		if (!splitted[tab_count])
		{
			ft_free_tab(splitted);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		tab_count++;
	}
	splitted[tab_count] = NULL;
	return (splitted);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	res = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len_s1 + 1);
	ft_strlcpy(res + len_s1, s2, len_s2 + 1);
	res[len_s1 + len_s2] = 0;
	return (res);
}

// int ft_strcmp(const char *s1, const char *s2) {
//     while (*s1 && (*s1 == *s2)) {
//         s1++;
//         s2++;
//     }
//     return *(unsigned char *)s1 - *(unsigned char *)s2;
// }
