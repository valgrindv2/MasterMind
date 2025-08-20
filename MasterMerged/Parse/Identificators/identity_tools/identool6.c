/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:23:39 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 05:03:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_con(t_token *curr)
{
	if (curr->tok == PIPE_ID
		|| curr->tok == OR_ID || curr->tok == AND_ID || curr->tok == RED_APP_ID
		|| curr->tok == RED_IN_ID || curr->tok == RED_OUT_ID
		|| curr->tok == HERE_DOC_ID || curr->tok == BRACE_C_ID
		|| curr->tok == BRACE_O_ID)
		return (0);
	return (1);
}

void	set_free(t_token *curr)
{
	t_token	*temp;

	temp = NULL;
	while (curr)
	{
		free(curr->identity);
		free(temp);
		temp = curr;
		if (!curr->next)
		{
			free(temp);
			temp = NULL;
			break ;
		}
		curr = curr->next;
	}
}

static void	free_nodes_del(t_token *delimiter, char *del_join)
{
	t_token	*after_delimiter;

	free(delimiter->identity);
	delimiter->identity = del_join;
	delimiter->tok = DEL_ID;
	after_delimiter = delimiter->next;
	get_quotes_state(delimiter);
	if (check_con(after_delimiter))
	{
		set_free(after_delimiter);
		delimiter->next = NULL;
	}
}

static char	*join_delimiter(char *del_join, t_token *delimiter, int index)
{
	int		i;
	char	*del;
	char	*tmp;

	i = 0;
	del = malloc(get_len(delimiter->identity) + 1);
	if (!del)
		return (NULL);
	while (delimiter->identity[i])
	{
		del[i] = delimiter->identity[i];
		i++;
	}
	del[i] = '\0';
	tmp = ft_strdup(del_join);
	if (!tmp && index > 0)
		return (free(del), NULL);
	free(del_join);
	del_join = ft_strjoin(tmp, del);
	if (!del_join)
		return (free(tmp), free(del), NULL);
	free(del);
	free(tmp);
	return (del_join);
}

int	delimiter_next(t_token *next_heredoc, t_data *data)
{
	int		index;
	char	*del_join;
	t_token	*delimiter;

	index = 0;
	del_join = NULL;
	delimiter = next_heredoc;
	if (next_heredoc->next == NULL
		|| next_heredoc->space_next == true)
		return (0);
	while (next_heredoc)
	{
		if (!takeoff_quotes(next_heredoc))
			return (data->fail = true, free(del_join), 0);
		del_join = join_delimiter(del_join, next_heredoc, index);
		if (!del_join)
			return (data->fail = true, 0);
		if (next_heredoc->space_next == true
			|| (next_heredoc->next && !check_con(next_heredoc->next)))
			break ;
		next_heredoc = next_heredoc->next;
		index++;
	}
	return (free_nodes_del(delimiter, del_join), 1);
}
