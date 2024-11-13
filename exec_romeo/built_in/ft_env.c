#include "../minishell.h"

int ft_env(t_env_node *env)
{
	t_env_node	*temp;

	if (!env)
		return (0);
	temp = env;
	while (temp)
	{
		if (temp->key && temp->val)
			printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
	return (0);
}
