#include "../inc/minishell.h"

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
	
	printf("heredoc count : %d\nnum_str : %s\n\n", heredoc_count, num_str);
	printf("size : %ld", size);
	
	len = append_str(filename, "/tmp/heredoc_", size);
	printf("len1 = %ld\n", len);
	printf("filename -1 : %s$\n", filename);
	len = append_str(filename, num_str, size);
	printf("len2 = %ld\n", len);
	len = append_str(filename, ".txt", size);
	if (len >= size)
		return(0);
	printf("filename : %s$\n", filename);
	printf("len3 = %ld\n", len);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len = 0;
	fprintf(stderr, "fd --> %d\n", *fd);
	if (*fd == -1)
	{
		//write(2, "Error: cannot open file\n", 24);
		perror("open failed");
		return (0);
	}
	return (1);
}

void handle_heredoc_redirection(t_exec *node, t_lx *current)
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
