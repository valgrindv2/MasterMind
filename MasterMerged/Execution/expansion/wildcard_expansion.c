/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:00:58 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:54 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static char	**fill_files_array(int count)
{
	t_ff	ff;

	if (!init_asterisk(&ff, count))
		return (NULL);
	ff.i = 0;
	ff.entry = readdir(ff.dir);
	while (ff.entry)
	{
		if (ff.entry->d_name[0] != '.')
		{
			ff.files[ff.i] = ft_strdup(ff.entry->d_name);
			if (!ff.files[ff.i])
			{
				while (--ff.i >= 0)
					free(ff.files[ff.i]);
				return (free(ff.files), closedir(ff.dir), NULL);
			}
			ff.i++;
		}
		ff.entry = readdir(ff.dir);
	}
	return (ff.files[ff.i] = NULL, closedir(ff.dir), ff.files);
}

char	**get_all_files(void)
{
	int	count;

	count = count_files();
	return (fill_files_array(count));
}

static t_arg	*create_arg_node(char *value, t_grammar tok)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->value = allocate_gc_no_exit(ft_strdup(value));
	if (!new->value)
		return (free(new), NULL);
	new->tok = tok;
	new->was_s_quote = 0;
	new->was_d_quote = 0;
	new->space_next = 1;
	new->next = NULL;
	return (new);
}

int	expand_star_in_arg(t_arg *arg)
{
	t_wcard	wc;

	wc.files = get_all_files();
	if (!wc.files || !wc.files[0])
		return (EXIT_SUCCESS);
	sort_files(wc.files);
	wc.next = arg->next;
	arg->value = allocate_gc_no_exit(ft_strdup(wc.files[0]));
	if (!arg->value)
		return (free_argv(wc.files), EXIT_FAILURE);
	arg->was_s_quote = 0;
	arg->was_d_quote = 0;
	arg->space_next = 1;
	wc.curr = arg;
	wc.i = 1;
	while (wc.files[wc.i])
	{
		wc.new_node = allocate_gc_no_exit(create_arg_node(wc.files[wc.i++],
					wc.curr->tok));
		if (!wc.new_node)
			return (free_argv(wc.files), EXIT_FAILURE);
		wc.curr->next = wc.new_node;
		wc.curr = wc.new_node;
	}
	return (wc.curr->next = wc.next, free_argv(wc.files), EXIT_SUCCESS);
}

int	try_expand_wildcard(t_arg *arg)
{
	if (arg->was_s_quote)
		return (EXIT_SUCCESS);
	if (arg->was_d_quote)
		return (EXIT_SUCCESS);
	if (!ft_strchr(arg->value, '*') || ft_strcmp(arg->value, "*"))
		return (EXIT_SUCCESS);
	if (expand_star_in_arg(arg) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
