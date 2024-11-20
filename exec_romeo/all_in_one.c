#include "../minishell.h"

int ft_cd(char **args)
{
	if (!args[1])
	{
		write(STDERR_FILENO, "cd: missing argument\n", 21);
		return 1;
	}
	if (args[1][0] != '/' && strcmp(args[1], "..") != 0 
		&& strncmp(args[1], "../", 3) != 0 
		&& strncmp(args[1], "./", 2) != 0)
	{
		write(STDERR_FILENO, "cd: only relative or absolute paths allowed\n", 44);
		return 1;
	}
	if (chdir(args[1]) == -1) {
		perror("cd");
		return 1;
	}
	return (0);
}
#include "../minishell.h"


size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

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
#include "../minishell.h"

int ft_exit(char **args)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (!args[1])
		exit(0);
	return (0); 
}
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
#include "../minishell.h"

const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

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

int execute_builtin(const char *cmd, char **args, t_env_list *env)
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
}
#include "../minishell.h"

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
	//if (!resolved_path)
	// {
	// 	command_not_found(node->execs[0]);
	// 	exit(EXIT_FAILURE);
	// }
	if (execve(resolved_path, node->execs, NULL) == -1) // Execute the command using execve
	{
		write(STDERR_FILENO, "Error: Command execution failed\n", 32);
		if (resolved_path)
			free(resolved_path);
		free_env_list(env_list);
		exit(EXIT_FAILURE); // Ensure child process terminates
	}
}

#include "../minishell.h"



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
		perror("execve failed");
	}
	else
	{
		// Close FDs in parent to avoid leaks
		if (current->fd_in != 0) close(current->fd_in);
		if (current->fd_out != 1) close(current->fd_out);
	}
	while (wait(NULL) > 0); // Wait for all children
}
#include "../minishell.h"

void free_env_list(t_env_list *env_list) {
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
}
//#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

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
#include "minishell.h"

void setup_heredoc_redirection(t_exec *node, const char *tmp_filename)
{
	int tmp_fd;
	
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd == -1) {
		perror("open");
		return;
	}
	if (dup2(tmp_fd, STDIN_FILENO) == -1) {
		perror("dup2");
		close(tmp_fd);
		return;
	}
	close(tmp_fd);
	unlink(tmp_filename);
	node->fd_in = STDIN_FILENO;
	node->heredoc = 1;
}

int read_heredoc_content(const char *delimiter, int fd)
{
	char buffer[1024];
	size_t bytes_read;

	while (1)
	{
		write(1, "> ", 2);
		bytes_read = read(0, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0) {
			break;
		}
		buffer[bytes_read] = '\0';
		if (is_delimiter(buffer, delimiter)) {
			break;
		}
		write(fd, buffer, bytes_read);
	}
	return 1;
}

int	append_str(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest[i] && i < dest_size)
		i++;
	j = 0;
	while (src[j] && (i + j + 1) < dest_size)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i + j < dest_size)
		dest[i + j] = '\0';
	return (i + j);
}

int	create_temp_file(char *filename, size_t size, int *fd)
{
	static int	heredoc_count = 0;
	char		num_str[10];
	size_t		len;

	int_to_string(heredoc_count++, num_str, sizeof(num_str));
	len = append_str(filename, "/tmp/heredoc_", size);
	len = append_str(filename, num_str, size);
	len = append_str(filename, ".txt", size);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		write(2, "Error: cannot open file\n", 24);
		return (0);
	}
	return (1);
}

void handle_heredoc_redirection(t_exec *node, t_lexer_list *current)
{
	char tmp_filename[256];
	int tmp_fd;

	current = current->next;
	if (!current) {
		write(2, "Heredoc: Missing delimiter\n", 27);
		return;
	}
	if (!create_temp_file(tmp_filename, sizeof(tmp_filename), &tmp_fd)) {
		return;
	}

	if (!read_heredoc_content(current->str, tmp_fd)) {
		close(tmp_fd);
		return;
	}

	setup_heredoc_redirection(node, tmp_filename);
}
#include "minishell.h"

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

char	*ft_itoa(int n)
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

	temp_str = ft_itoa(n);
	if (!temp_str)
	{
		buffer[0] = '\0';
		return;
	}
	strncpy(buffer, temp_str, size - 1);
	buffer[size - 1] = '\0';
	free(temp_str);
}
#include "./minishell.h"

t_exec *create_exec_node(int id, char **cmd)
{
	t_exec *node;
	
	node = malloc(sizeof(t_exec));
	if (!node)
		return NULL;
	node->id = id;
	node->size = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->trunc = 0;
	node->append = 0;
	node->redir_input = 0;
	node->heredoc = 0;
	node->path = NULL;
	node->execs = cmd;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

void link_exec_with_pipe(t_exec *left, t_exec *right)
{
	int pipe_fds[2];
	
	if (pipe(pipe_fds) == -1) {
		perror("pipe");
		return;
	}
	left->fd_out = pipe_fds[1];
	right->fd_in = pipe_fds[0];
	left->next = right;
	right->prev = left;
}

//Precision : we will use execve after I implement it
void execute_command(t_exec *node)
{
	if (node->fd_in != 0) {
		dup2(node->fd_in, 0);
		close(node->fd_in);
	}
	if (node->fd_out != 1) {
		dup2(node->fd_out, 1);
		close(node->fd_out);
	}
	execvp(node->execs[0], node->execs);
	perror("execvp");
	exit(EXIT_FAILURE);
}
#include "./minishell.h"

// Handling > (Truncate) Redirection
void handle_truncate_redirection(t_exec *node, t_lexer_list *current)
{
    int fd;

    current = current->next;
    fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return;
    }
    close(fd);
    node->fd_out = STDOUT_FILENO;
    node->trunc = 1;
	}

// Handling >> (Append) Redirection
void handle_append_redirection(t_exec *node, t_lexer_list *current)
{
    int fd;

    current = current->next;
    fd = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
	if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return;
    }
    close(fd);
	node->fd_out = STDOUT_FILENO;
    node->append = 1;
}

// Handling < (Input) Redirection
void handle_input_redirection(t_exec *node, t_lexer_list *current)
{
    int fd;

    current = current->next;
    fd = open(current->str, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return;
    }
    close(fd);
    node->fd_in = STDIN_FILENO;
    node->redir_input = 1;
}

// Check if we have to redirect
void handle_redirection(t_exec *node, t_lexer_list *current)
{
	if (current->type == TRUNCATE) {
		handle_truncate_redirection(node, current);
	}
	else if (current->type == APPEND) {
		handle_append_redirection(node, current);
	}
	else if (current->type == REDIRECT_INPUT) {
		handle_input_redirection(node, current);
	}
	else if (current->type == HEREDOC) {
        handle_heredoc_redirection(node, current);
    }
}
