/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:48:04 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:17:37 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_flag;

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

static void	single_interruption(char *in, t_data *data, int sv)
{
	puterror("Master@Mind: Single Heredoc Blocked\n");
	close(data->here_read_fd);
	data->here_read_fd = -1;
	data->exit_status = 0;
	close(data->here_fd);
	data->here_fd = -1;
	close(sv);
	free(in);
	signal(SIGINT, sig_handler);
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
			return (single_interruption(in, data, sv), 1);
		cpy_to_file(in, data);
		in = readline("Here_doc> ");
	}
	close(sv);
	close(data->here_fd);
	data->here_fd = -1;
	signal(SIGINT, sig_handler);
	if (!store_fd(id_class, data))
		return (free(in), 0);
	return (free(in), 1);
}
