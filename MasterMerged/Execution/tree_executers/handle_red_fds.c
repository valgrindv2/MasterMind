/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:31:09 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:17 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

int	red_in(t_red *red, t_data *data)
{
	int	in_fd;

	(void)data;
	in_fd = open(red->value, O_RDONLY);
	if (in_fd == -1)
		return (perror("Master@Mind: "), EXIT_FAILURE);
	if (dup2(in_fd, STDIN_FILENO) == -1)
		return (puterror("Master@Mind: "), puterror(red->value),
			close(in_fd), EXIT_FAILURE);
	close(in_fd);
	return (EXIT_SUCCESS);
}

int	red_out(t_red *red, t_data *data)
{
	int	out_fd;

	(void)data;
	out_fd = open(red->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd == -1)
		return (perror("Master@Mind: "), EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (puterror("Master@Mind: "), puterror(red->value),
			perror(" "), close(out_fd), EXIT_FAILURE);
	close(out_fd);
	return (EXIT_SUCCESS);
}

int	red_append(t_red *red, t_data *data)
{
	int	out_fd;

	(void)data;
	out_fd = open(red->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd == -1)
		return (perror("Master@Mind: "), EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (puterror("Master@Mind: "), puterror(red->value),
			perror(" "), close(out_fd), EXIT_FAILURE);
	close(out_fd);
	return (EXIT_SUCCESS);
}

int	read_file(t_red *red, char **joined)
{
	char	*file;
	char	*tmp;

	file = get_next_line(red->fd_here_doc);
	if (!file)
		return (EXIT_SUCCESS);
	while (file)
	{
		tmp = *joined;
		*joined = gnl_ft_strjoin(*joined, file);
		if (!*joined)
		{
			free(tmp);
			free(file);
			get_next_line(-1);
			return (mind_free_all(PANIC), EXIT_FAILURE);
		}
		free(tmp);
		free(file);
		file = get_next_line(red->fd_here_doc);
	}
	get_next_line(-1);
	return (EXIT_SUCCESS);
}

int	red_here_doc(t_red *red, t_data *data)
{
	char	*joined ;
	char	*expanded;
	int		pipefd[2];

	if (red->fd_here_doc == -1)
		return (data->here_int = true, EXIT_SUCCESS);
	data->here_int = false;
	joined = NULL;
	read_file(red, &joined);
	if (!joined)
		joined = ft_strdup("");
	allocate_gc(joined);
	expanded = expand_heredoc(joined, red, data);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), mind_free_all(PANIC), EXIT_FAILURE);
	write(pipefd[1], expanded, o_ft_strlen(expanded));
	close(pipefd[1]);
	close(red->fd_here_doc);
	red->fd_here_doc = pipefd[0];
	if (dup2(red->fd_here_doc, STDIN_FILENO) == -1)
		return (perror("dup2"), mind_free_all(PANIC), EXIT_FAILURE);
	close(red->fd_here_doc);
	red->fd_here_doc = -1;
	return (EXIT_SUCCESS);
}
