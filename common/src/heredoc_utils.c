#include "../inc/minishell.h"

int is_delimiter(const char *buffer, const char *delimiter)
{
	return (strncmp(buffer, delimiter, strlen(delimiter)) == 0 &&
		   buffer[strlen(delimiter)] == '\n');
}

static int	ft_num_len(int n)
{
	int	len;

	len = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*my_ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	num = n;
	len = ft_num_len(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (--len >= 0 && str[len] != '-')
	{
		str[len] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

void	int_to_string(int n, char *buffer, size_t size)
{
	char	*temp_str;

	temp_str = my_ft_itoa(n);
	if (!temp_str)
	{
		buffer[0] = '\0';
		return;
	}
	strncpy(buffer, temp_str, size - 1);
	buffer[size - 1] = '\0';
	free(temp_str);
}