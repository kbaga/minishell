#include "../inc/minishell.h"

void free_env_list(t_env *env_list) {
    t_env_node *tmp;
    while (env_list->head != NULL) 
	{
        tmp = env_list->head;
        env_list->head = env_list->head->next;
        free(tmp->key);
        free(tmp->val);
        free(tmp);
    }
}

void error_command(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void command_not_found(const char *cmd)
{
    const char *error_message = "Command not found: ";
    write(STDERR_FILENO, error_message, strlen(error_message));
    write(STDERR_FILENO, cmd, strlen(cmd));
    write(STDERR_FILENO, "\n", 1);
	return;
}
