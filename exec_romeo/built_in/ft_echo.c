#include "../minishell.h"

static int	check_new_line(char *str) {
	int	i;

	i = 0;
	if (str[i] && str[i] == '-') {
		++i;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

static void	write_echo(int count, int i, char **args) {
	int add_newline = 1;

	// Skip all -n options
	while (args[i] && check_new_line(args[i])) {
		++i;
		add_newline = 0;
	}

	// Write all arguments
	while (i < count) {
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		++i;
	}

	// Add newline if not suppressed
	if (add_newline)
		write(1, "\n", 1);
}

int	ft_echo(char **args) {
	int	count;
	int	i;

	if (!args || !args[0]) {
		write(1, "\n", 1);
		return (0);
	}

	count = 0;
	while (args[count])
		++count;

	i = 1;
	write_echo(count, i, args);
	return (0);
}
