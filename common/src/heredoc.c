/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakamba <lakamba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:39:53 by lakamba           #+#    #+#             */
/*   Updated: 2025/01/06 16:31:15 by lakamba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	setup_heredoc_redirection(t_exec *node, const char *tmp_filename)
{
	node->fd_in = open(tmp_filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		perror("open heredoc");
		unlink(tmp_filename);
		return ;
	}
	unlink(tmp_filename);
	node->heredoc = 1;
}

int	read_heredoc_content(char *delimiter, int fd)
{
	char	buffer[1024];
	size_t	bytes_read;

	while (1)
	{
		write(1, "> ", 2);
		bytes_read = read(0, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (is_delimiter(buffer, delimiter))
			break ;
		write(fd, buffer, bytes_read);
	}
	return (1);
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

static int	open_heredoc_file(const char *filename)
{
	int	tmp_fd;

	tmp_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0600);
	if (tmp_fd == -1)
		perror("Heredoc: Could not create file");
	return (tmp_fd);
}

void	handle_heredoc_redirection(t_exec *node, t_lx *current)
{
	const char	*tmp_filename;
	int			tmp_fd;

	tmp_fd = open_heredoc_file(tmp_filename);
	if (tmp_fd == -1)
		return ;
	while (current && current->next && current->type == HEREDOC)
	{
		current = current->next;
		if (!current)
		{
			write(2, "Heredoc: Missing delimiter\n", 27);
			close(tmp_fd);
			unlink(tmp_filename);
			return ;
		}
		if (!read_heredoc_content(current->str, tmp_fd))
		{
			close(tmp_fd);
			unlink(tmp_filename);
			return ;
		}
	}
	close(tmp_fd);
	setup_heredoc_redirection(node, tmp_filename);
}
