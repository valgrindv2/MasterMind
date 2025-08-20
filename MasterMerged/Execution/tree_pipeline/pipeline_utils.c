/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:23:33 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:21 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static void	cmd_add_last(t_tree *node, t_plist **head)
{
	t_plist	*new_pipe_cmd;
	t_plist	*curr;

	new_pipe_cmd = allocate_gc(malloc(sizeof(t_plist)));
	if (!new_pipe_cmd)
		return ;
	new_pipe_cmd->cmd_node = node;
	new_pipe_cmd->next = NULL;
	if (!*head)
		*head = new_pipe_cmd;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_pipe_cmd;
	}
}

void	flatten_pipeline(t_tree *node, t_plist **head)
{
	if (!node)
		return ;
	if (node->tok == PIPE_ID)
	{
		flatten_pipeline(node->left, head);
		flatten_pipeline(node->right, head);
	}
	else
		cmd_add_last(node, head);
}

static	void	setup_child_io(int prev_fd, int fds[2], int is_pipe)
{
	if (prev_fd != STDIN_FILENO)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			close(prev_fd);
			mind_free_all(PANIC);
		}
		close(prev_fd);
	}
	if (is_pipe)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			close(fds[0]);
			close(fds[1]);
			mind_free_all(PANIC);
		}
		close(fds[0]);
		close(fds[1]);
	}
}

pid_t	fork_pipeline_node(t_plist *node, t_data *data, t_pipe_info *info)
{
	pid_t	pid;
	int		ret;

	data->child_state = true;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		mind_free_all(PANIC);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, sig_kill);
		signal(SIGQUIT, sig_kill);
		setup_child_io(info->prev_fd, info->fds, info->is_pipe);
		ret = recursive_execution(node->cmd_node, data);
		exit(pipe_child_free(ret));
	}
	return (pid);
}

int	wait_for_last_pid(pid_t last_pid)
{
	int		w_pid;
	int		status;
	int		ex_st;

	ex_st = 0;
	w_pid = -1;
	w_pid = wait(&status);
	while (w_pid > 0)
	{
		if (w_pid == last_pid)
			ex_st = WEXITSTATUS(status);
		w_pid = wait(&status);
	}
	return (ex_st);
}
