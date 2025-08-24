/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arglist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:51 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

void	free_arg_list(t_arg *arg)
{
	t_arg	*tmp;

	if (!arg)
		return ;
	while (arg)
	{
		tmp = arg->next;
		free(arg->value);
		free(arg);
		arg = tmp;
	}
}

static size_t	arglist_size(t_arg *arg)
{
	size_t	size;

	size = 0;
	while (arg)
	{
		size++;
		arg = arg->next;
	}
	return (size);
}

char	**convert_list_to_argv(t_arg *arg, t_data *data)
{
	t_convert	cv;

	if (expand_list_new(arg, data) != EXIT_SUCCESS) // this is the function i use the data struct to acces env list. 
		return (NULL);
	cv.argc = arglist_size(arg);
	cv.argv = allocate_gc(malloc((cv.argc + 1) * sizeof(char *)));
	cv.i = 0;
	while (arg)
	{
		cv.argv[cv.i++] = join_system(&arg);
	}
	cv.argv[cv.i] = NULL;
	cv.new_argv = ifs_pass(cv.argv);
	return (cv.new_argv);
}
