/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:19:33 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:54:08 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*name_generator(void)
{
	long	n;
	long	*nb;
	char	*name;
	char	*gename;

	nb = malloc(sizeof(long *));
	if (!nb)
		return (NULL);
	n = (long)nb;
	name = ft_itoa(n);
	if (!name)
		return (free(nb), NULL);
	gename = ft_strjoin("/tmp/", name);
	if (!gename)
		return (free(name), free(nb), NULL);
	free(name);
	free(nb);
	return (gename);
}

void	cpy_to_file(char *in, t_data *data)
{
	int	i;

	i = 0;
	while (in[i])
	{
		write(data->here_fd, &in[i], 1);
		i++;
	}
	write(data->here_fd, "\n", 1);
	free(in);
}

static char	*scrap_del(char *delimiter)
{
	int		i;
	char	*del;

	i = 0;
	del = malloc(get_len(delimiter) + 1);
	if (!del)
		return (NULL);
	while (delimiter[i])
	{
		del[i] = delimiter[i];
		i++;
	}
	del[i] = '\0';
	return (del);
}

static int	open_heredoc(t_token *id_class, t_token *curr, t_data *data)
{
	char	*del;
	char	*gename;

	if (!sef_doc(id_class, data))
		return (0);
	gename = name_generator();
	if (!gename)
		return (0);
	del = scrap_del(get_delimiter(curr));
	if (!del)
		return (free(gename), 0);
	data->here_fd = open(gename, O_CREAT | O_WRONLY, 0777);
	if (data->here_fd == -1)
		return (free(del), free(gename), 0);
	data->here_read_fd = open(gename, O_RDONLY, 0777);
	if (data->here_read_fd == -1)
		return (close(data->here_fd), data->here_fd = -1,
			free(del), free(gename), 0);
	unlink(gename);
	if (!here_doc_ops(curr, data, del))
		return (free(del), free(gename), 0);
	return (free(del), free(gename), 1);
}

int	here_doc_check(t_token *id_class, t_data *data)
{
	t_token	*curr;

	curr = id_class;
	while (curr != NULL)
	{
		if (requirements(curr, id_class, data))
		{
			curr->here_times = 0;
			if (!change_id(curr->next, data)
				|| !open_heredoc(id_class, curr, data))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}
