#include "../inc/minishell.h"

// static int	check_new_line(char *str) {
// 	int	i;

// 	i = 0;
// 	if (str[i] && str[i] == '-') {
// 		++i;
// 		while (str[i] && str[i] == 'n')
// 			i++;
// 		if (i == (int)ft_strlen(str))
// 			return (1);
// 	}
// 	return (0);
// }

// static void	write_echo(int count, int i, char **args) {
// 	int add_newline = 1;

// 	// Skip all -n options
// 	while (args[i] && check_new_line(args[i])) {
// 		++i;
// 		add_newline = 0;
// 	}

// 	// Write all arguments
// 	while (i < count) {
// 		write(1, args[i], ft_strlen(args[i]));
// 		if (i != count - 1)
// 			write(1, " ", 1);
// 		++i;
// 	}

// 	// Add newline if not suppressed
// 	if (add_newline)
// 		write(1, "\n", 1);
// }

// void	ft_echo(char **args) 
// {
// 	int	count;
// 	int	i;

// 	if (!args || !args[0]) 
// 	{
// 		write(1, "\n", 1);
// 		//return (0);
// 	}

// 	count = 0;
// 	while (args[count])
// 		++count;

// 	i = 1;
// 	write_echo(count, i, args);
// }



void	ft_echo(char **execs, t_shell *shell)
{
	int	flag;
	int i;

	flag = 0;
	i = 1;
	if (execs[i] && ft_strcmp(execs[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (execs[i])
	{
		printf("%s", execs[i]);
		if (execs[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	shell->exit_status = 0;
}
