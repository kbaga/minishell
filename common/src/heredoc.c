#include "../inc/minishell.h"

void setup_heredoc_redirection(t_exec *node, const char *tmp_filename)
{
	node->fd_in = open(tmp_filename, O_RDONLY);
	if (node->fd_in == -1) 
	{
	perror("open heredoc");
	unlink(tmp_filename);
	return;
	}
	unlink(tmp_filename);
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

// int	create_temp_file(char *filename, size_t size, int *fd)
// {
// 	static int	heredoc_count = 0;
// 	char		num_str[10];
// 	// size_t		len;
	
// 	int_to_string(heredoc_count++, num_str, sizeof(num_str));
	
// 	// printf("heredoc count : %d\nnum_str : %s\n\n", heredoc_count, num_str);
// 	// printf("size : %ld", size);
	
// 	// len = append_str(filename, "/tmp/heredoc_", size);
// 	// len = append_str(filename, num_str, size);
// 	// printf("len2 = %ld\n", len);
// 	// len = append_str(filename, ".txt", size);
// 	// if (len >= size)
// 	// 	return(0);
// 	// printf("filename : %s$\n", filename);
// 	// printf("len3 = %ld\n", len);
// 	*fd = open("./tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	// len = 0;
// 	fprintf(stderr, "fd --> %d\n", *fd);
// 	if (*fd == -1)
// 	{
// 		//write(2, "Error: cannot open file\n", 24);
// 		perror("open failed");
// 		return (0);
// 	}
// 	return (1);
// }


void handle_heredoc_redirection(t_exec *node, t_lx *current)
{
	const char *tmp_filename = "/tmp/heredoc.txt";
	int tmp_fd;

	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("Heredoc: Could not create file");
		return;
	}
	while (current && current->next && current->type == HEREDOC) 
	{
		current = current->next;
		if (!current) 
		{
			write(2, "Heredoc: Missing delimiter\n", 27);
			close(tmp_fd);
			unlink(tmp_filename);
			return;
		}
		// Read the heredoc content and append to the same fd
		if (!read_heredoc_content(current->str, tmp_fd))
		{
			close(tmp_fd);
			unlink(tmp_filename);
			return;
		}
	}
	close(tmp_fd); // Close the file after writing all heredocs
	setup_heredoc_redirection(node, tmp_filename);
}
