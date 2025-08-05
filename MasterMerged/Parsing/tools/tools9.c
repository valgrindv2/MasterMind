/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:48:04 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/05 03:01:20 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void here_doc_interruption(char *in, t_data *data, int sv)
{
	puterror("Master@Mind: Herdoc Interrupted\n");
	close(data->here_fd);
	data->here_fd = -1;
	data->exit_status = 1;
	free(in);
	dup2(sv, STDIN_FILENO);
	close(sv);
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
		// why sigheredoc didnt work on the inside of the loop ?
		// how does the global var gets reseted to zero after the singla (CTRL + C) ?
		if (!in)
		{
			here_doc_interruption(in, data, sv);
			return (0);
			// may check for fd and laeks
		}
		cpy_to_file(in, data);
		in = readline("Here_doc> ");
	}
	close(sv);
	signal(SIGINT, sig_handler);
	if (!store_fd(id_class, data))
		return (free(in), 0);
	return (free(in), 1);
}
