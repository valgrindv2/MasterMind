/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:48:04 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/22 19:39:09 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_flag;

static void	closing_here_fd(t_data *data)
{
	if (data->here_fd != -1)
	{
		close(data->here_fd);
		data->here_fd = -1;
	}
}

int	list_size(t_token *list)
{
	int	size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

static void	here_doc_interruption(char *in, t_data *data, int sv)
{
	puterror("Master@Mind: Heredoc Interrupted\n");
	close(data->here_read_fd);
	data->here_read_fd = -1;
	close(data->here_fd);
	data->here_fd = -1;
	data->exit_status = 1;
	free(in);
	data->read_f = true;
	dup2(sv, STDIN_FILENO);
	close(sv);
	signal(SIGINT, sig_handler);
}

static void	single_interruption(char *in, t_data *data)
{
	puterror("Master@Mind: Single Heredoc Blocked\n");
	data->exit_status = 0;
	closing_here_fd(data);
	free(in);
}

int	here_doc_ops(t_token *id_class, t_data *data, char *del)
{
	int		sv;
	char	*in;

	sv = dup(STDIN_FILENO);
	signal(SIGINT, sig_heredoc);
	in = readline("Here_doc> ");
	while (ft_strcmp(del, in))
	{
		if (!in && g_flag == SIGINT)
			return (here_doc_interruption(in, data, sv), 0);
		else if (!in && g_flag != SIGINT)
		{
			single_interruption(in, data);
			break ;
		}
		cpy_to_file(in, data);
		in = readline("Here_doc> ");
	}
	close(sv);
	closing_here_fd(data);
	signal(SIGINT, sig_handler);
	if (!store_fd(id_class->next, data))
		return (free(in), 0);
	return (free(in), 1);
}
