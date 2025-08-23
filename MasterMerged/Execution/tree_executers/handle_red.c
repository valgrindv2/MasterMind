/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:30:33 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/22 23:38:20 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static void	init_red(t_data *data, t_tree *node, t_red **curr_red)
{
	data->saved_in = dup(STDIN_FILENO);
	if (data->saved_in == -1)
	{
		mind_free_all(PANIC);
	}
	data->saved_out = dup(STDOUT_FILENO);
	if (data->saved_out == -1)
	{
		close(data->saved_in);
		mind_free_all(PANIC);
	}
	*curr_red = node->red;
}

static int	redirect_current(t_red *curr_red, t_data *data)
{
	if (curr_red->tok == INPUT_FILE_ID)
	{
		if (red_in(curr_red, data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else if (curr_red->tok == OUTPUT_FILE_ID)
	{
		if (red_out(curr_red, data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else if (curr_red->tok == INPUT_APP_FILE_ID)
	{
		if (red_append(curr_red, data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else if (curr_red->tok == DEL_ID)
	{
		if (red_here_doc(curr_red, data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool	ambig_wrapper(char *str, bool ambig_dollar,
	bool dquoted, bool squoted)
{
	if (!squoted && !dquoted
		&& str[0] == '*' && str[1] == '\0')
		return (true);
	if (!ambig_dollar)
		return (false);
	if (!dquoted && has_ambig_space(str))
		return (true);
	if (!dquoted && str[0] == ANON)
		return (true);
	return (false);
}

int	handle_red(t_tree *node, t_data *data)
{
	t_red	*curr_red;
	char	*expanded;
	bool	ambig;
	char	*og;

	init_red(data, node, &curr_red);
	while (curr_red)
	{
		ambig = expandable_check(curr_red->value);
		og = allocate_gc(ft_strdup(curr_red->value));
		check_expanded_malloc(&expanded, data, curr_red);
		curr_red->value = expanded;
		if (curr_red->tok != DEL_ID && ambig_wrapper(curr_red->value,
				ambig, curr_red->was_d_quote, curr_red->was_s_quote))
			return (puterror("Master@Mind: ambiguous redirect\n"),
				data->exit_status = EXIT_FAILURE, EXIT_FAILURE);
		curr_red->value = red_ifs_pass(curr_red->value);
		if (redirect_current(curr_red, data) != EXIT_SUCCESS)
			return (data->exit_status = EXIT_FAILURE, EXIT_FAILURE);
		curr_red = curr_red->next;
	}
	return (EXIT_SUCCESS);
}

// check if -1; re init back to -1 fds
void	restore_io(t_data *data, bool no_red)
{
	if (no_red)
		return ;
	if (dup2(data->saved_in, STDIN_FILENO) == -1)
		mind_free_all(PANIC);
	if (dup2(data->saved_out, STDOUT_FILENO) == -1)
		mind_free_all(PANIC);
	if (data->saved_in != -1)
	{
		close(data->saved_in);
		data->saved_in = -1;
	}
	if (data->saved_out != -1)
	{
		close(data->saved_out);
		data->saved_out = -1;
	}
}
