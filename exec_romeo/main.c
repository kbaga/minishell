#include "./minishell.h"

int main(int argc, char **argv, char **env)
{
    t_env_list env_list;
    t_env_node *current_node, *new_node;

	(void)argc;
	(void)argv;
	current_node = NULL;

    // Initialize the environment list
    env_list.head = NULL;

    // Convert char **env to t_env_list
	current_node = NULL;

for (int i = 0; env[i]; i++) {
    char *delimiter = strchr(env[i], '=');
    if (!delimiter) { 
        continue; // Skip malformed environment variables
    }

    // Allocate new node
    new_node = malloc(sizeof(t_env_node));
    if (!new_node) {
        perror("malloc");
        // Add cleanup here if partial allocations have occurred
        return EXIT_FAILURE;
    }

    // Allocate key and value
    new_node->key = strndup(env[i], delimiter - env[i]);
    if (!new_node->key) {
        free(new_node);
        perror("strndup");
        return EXIT_FAILURE;
    }

    new_node->val = strdup(delimiter + 1);
    if (!new_node->val) {
        free(new_node->key);
        free(new_node);
        perror("strdup");
        return EXIT_FAILURE;
    }

    new_node->next = NULL;

    // Append to the list
    if (!env_list.head) {
        env_list.head = new_node; // Initialize head if list is empty
    } else {
        current_node->next = new_node; // Link the new node
    }

    current_node = new_node; // Move to the new node
}

    // Commands for testing
    t_exec cmd1, cmd2, cmd3;

    // Command 1: "ls -l"
    cmd1.id = 1;
    cmd1.fd_in = 0;
    cmd1.fd_out = 1;
    cmd1.execs = (char *[]){"ps", NULL, NULL};
    cmd1.next = &cmd2;
    cmd1.prev = NULL;

    // Command 2: "grep txt"
    cmd2.id = 2;
    cmd2.fd_in = 0;
    cmd2.fd_out = 1;
    cmd2.execs = (char *[]){"pwd", NULL /**"-a"*/, NULL};
    cmd2.next = &cmd3;
    cmd2.prev = &cmd1;



// Command 3: "wc -l"
    cmd3.id = 3;
    cmd3.fd_in = 0;
    cmd3.fd_out = 1;
    cmd3.execs = (char *[]){"ls", NULL, NULL};
    cmd3.next = NULL;
    cmd3.prev = &cmd2;

    // Execute the command list
   execute_exec_list(&cmd1, &env_list);
    

	// Free environment list
	//printf("free de la env_list :\n");
	free_env_list(&env_list);




    return 0;
}
