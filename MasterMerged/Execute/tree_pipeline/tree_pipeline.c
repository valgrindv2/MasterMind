/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:27:03 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 05:10:08 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	setup_pipe(int fds[2])
{
	if (pipe(fds) == -1)
	{
		mind_free_all(PANIC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool	check_is_pipe(t_plist *curr)
{
	if (curr->next != NULL)
		return (true);
	return (false);
}

static void	init_pipe_data(t_pp *p, t_tree *root, int input_fd)
{
	p->info.prev_fd = input_fd;
	p->plist = NULL;
	flatten_pipeline(root, &p->plist);
	p->last_pid = -1;
	p->curr = p->plist;
}

static void	update_prev(t_pp *p)
{
	close(p->info.fds[1]);
	p->info.fds[1] = -1;
	p->info.prev_fd = p->info.fds[0];
}

int	execute_pipeline(t_tree *root, t_data *data, int input_fd)
{
	t_pp	p;

	init_pipe_data(&p, root, input_fd);
	while (p.curr)
	{
		p.info.is_pipe = check_is_pipe(p.curr);
		if (p.info.is_pipe && (setup_pipe(p.info.fds) != EXIT_SUCCESS))
			return (EXIT_FAILURE);
		p.last_pid = fork_pipeline_node(p.curr, data, &p.info);
		if (p.last_pid == -1)
			return (EXIT_FAILURE);
		if (p.info.prev_fd != STDIN_FILENO && p.info.prev_fd != -1)
		{
			close(p.info.prev_fd);
			p.info.prev_fd = -1;
		}
		if (p.info.is_pipe)
			update_prev(&p);
		p.curr = p.curr->next;
	}
	if (p.info.prev_fd != STDIN_FILENO && p.info.prev_fd != -1)
		close(p.info.prev_fd);
	p.ret = wait_for_last_pid(p.last_pid);
	return (pipe_sighandle(), data->child_state = false, p.ret);
}
