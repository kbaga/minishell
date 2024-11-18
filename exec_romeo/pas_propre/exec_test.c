#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

typedef struct	s_exec
{
	int		id;
	int		size;
	int		fd_in;
	int		fd_out;
	int		trunc;
	int		append;
	int		redir_input;
	int		heredoc;
	char	**path;
	char	**execs;
	struct s_exec	*prev;
	struct s_exec	*next;
}	t_exec;

typedef struct	s_env_node
{
	char	*key;
	char	*val;
	struct s_env_node	*next;
}	t_env_node;

typedef struct	s_env_list
{
	struct s_env_node	*head;
}	t_env_list;

void	ft_free_tab(char **tab);
void fork_external(t_exec *head, t_env_list *env_list);

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len_s1 + 1);
	ft_strlcpy(res + len_s1, s2, len_s2 + 1);
	res[len_s1 + len_s2] = 0;
	return (res);
}

int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}


// Array of built-in commands (definition)
const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

/*int execute_builtin(const char *cmd, char **args, t_env_list *env)
{
    if (strcmp(cmd, "echo") == 0) 
        return ft_echo(args);
    else if (strcmp(cmd, "cd") == 0)
        return ft_cd(args);
    else if (strcmp(cmd, "pwd") == 0)
        return ft_pwd();
    else if (strcmp(cmd, "export") == 0)
        return ft_export(args);///////////
    else if (strcmp(cmd, "unset") == 0)
        return ft_unset(args);///////////
    else if (strcmp(cmd, "env") == 0)
        return ft_env(env);
    else if (strcmp(cmd, "exit") == 0)
        return ft_exit(args);
    fprintf(stderr, "Unknown built-in command: %s\n", cmd);
    return (1);
}*/

// Function to check if a command is a built-in
int is_builtin(const char *command)
{
	int i;
	
	i = 0;
	while (builtins[i])
	{
		if (strcmp(command, builtins[i]) == 0)
			return (1);
		i++;
	}		// Execute the command using execve
	return (0);
}


// Function to separate execution between built-in and execve
void send_to_exec(t_exec *cmd, t_env_list *env) 
{
		if (cmd == NULL || cmd->execs == NULL || cmd->execs[0] == NULL)
		{
			write(STDERR_FILENO, "Invalid command.\n", 17);
			return;
		}
		if (is_builtin(cmd->execs[0]))
			printf("it s a built-in"); //execute_builtin(cmd->execs[0], cmd->execs);
		else
			fork_external(cmd, env);
}

void execute_exec_list(t_exec *cmd_list, t_env_list *env) {
    t_exec *current = cmd_list;
	int i = 0;

    while (current != NULL)
	{
        send_to_exec(current, env); // Execute the current command
        current = current->next;   // Move to the next command in the list
	}
}


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


char *my_getenv(char *name, t_env_list *env_list)
{
	t_env_node *current;

	current = env_list->head;
	while (current != NULL)
{
	if (ft_strcmp(current->key, name) == 0)
		return (current->val);
	current = (current->next);
}
	return (NULL);
}

char	*get_path(char *cmd, t_env_list *env_list)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env_list), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])// Iterate through each path directory
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0) {
			ft_free_tab(allpath);
			ft_free_tab(s_cmd);
			return (exec); // Return the valid executable path
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (NULL);
}

static void error_command(const char *message)
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
	//exit(EXIT_FAILURE); // Quitte uniquement le processus enfant
}




void execute_command(t_exec *node, t_env_list *env_list)
{
	char *resolved_path;

	resolved_path = get_path(node->execs[0], env_list);
	if (node->fd_in != 0)// Redirect stdin if needed
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			error_command("dup2 fd_in");
		close(node->fd_in);
	}
	if (node->fd_out != 1)// Redirect stdout if needed
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			error_command("dup2 fd_out");
		close(node->fd_out);
	}
	// if (!resolved_path)
	// {
	// 	command_not_found(node->execs[0]);
	// 	exit(EXIT_FAILURE);
	// }
	if (execve(resolved_path, node->execs, NULL) == -1) // Execute the command using execve
	{
		write(STDERR_FILENO, "Error: Command execution failed\n", 32);
		if (resolved_path)
			free(resolved_path);
		exit(EXIT_FAILURE); // Ensure child process terminates
	}
}

void fork_external(t_exec *head, t_env_list *env_list)
{
	t_exec *current;
	pid_t pid;

	current = head;
	pid = fork();
	if (pid < 0) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("pid = 0\n");
		execute_command(current, env_list); // Execute command in child
	}
	else
	{
		// Close FDs in parent to avoid leaks
		if (current->fd_in != 0) close(current->fd_in);
		if (current->fd_out != 1) close(current->fd_out);
	}
	while (wait(NULL) > 0); // Wait for all children
}

int main(int argc, char **argv, char **env) {
    t_env_list env_list;
    t_env_node *current_node, *new_node;

    // Initialize the environment list
    env_list.head = NULL;

    // Convert char **env to t_env_list
    for (int i = 0; env[i]; i++) {
        char *delimiter = strchr(env[i], '=');
        if (!delimiter)
            continue;

        // Create a new environment node
        new_node = malloc(sizeof(t_env_node));
        if (!new_node) {
            perror("malloc");
            return EXIT_FAILURE;
        }

        // Split the key and value
        new_node->key = strndup(env[i], delimiter - env[i]);
        new_node->val = strdup(delimiter + 1);
        new_node->next = NULL;

        // Append to the list
        if (!env_list.head) {
            env_list.head = new_node;
        } else {
            current_node->next = new_node;
        }
        current_node = new_node;
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
    cmd2.execs = (char *[]){"da333te", NULL /**"-a"*/, NULL};
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
    t_env_node *tmp;
    

	while (env_list.head) 
	{
        tmp = env_list.head;
        env_list.head = env_list.head->next;
        free(tmp->key);
        free(tmp->val);
        free(tmp);
    }

    return 0;
}
