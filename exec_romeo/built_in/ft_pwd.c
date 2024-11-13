#include "../minishell.h"

int ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	else 
	{
		perror("pwd");
		return (1);
	}
}
