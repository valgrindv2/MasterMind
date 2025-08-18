#include "../execute.h"

static void free_pipe_list(t_plist *head)
{
    t_plist *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

static int	setup_pipe(int fds[2])
{
	if (pipe(fds) < 0)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static bool check_is_pipe(t_plist *curr)
{
	if (curr->next != NULL)
		return (true);
	return (false);
}

static void init_pipe_data(t_pp *p, t_tree *root, int input_fd)
{
	p->info.prev_fd = input_fd;
	p->plist = NULL;
	flatten_pipeline(root, &p->plist);
	// if pipeline fails exit.
	p->last_pid = -1;
	p->curr = p->plist;
}

// entry
int execute_pipeline(t_tree *root, t_data *data, int input_fd)
{
	t_pp	p;

	data->piped = true;
	init_pipe_data(&p, root, input_fd);
	while (p.curr)
	{
		p.info.is_pipe = check_is_pipe(p.curr);
		if (p.info.is_pipe && (setup_pipe(p.info.fds) != EXIT_SUCCESS))
				return (free_pipe_list(p.plist), EXIT_FAILURE);
		p.last_pid = fork_pipeline_node(p.curr, data, &p.info);
		if (p.last_pid == -1)
			return (free_pipe_list(p.plist), EXIT_FAILURE);
		if (p.info.prev_fd != STDIN_FILENO)
			close(p.info.prev_fd);
		if (p.info.is_pipe)
		{
			close(p.info.fds[1]);
			p.info.prev_fd = p.info.fds[0];
		}
		p.curr = p.curr->next;
	}
	if (p.info.prev_fd != STDIN_FILENO)
		close(p.info.prev_fd);
	free_pipe_list(p.plist);
	p.ret = wait_for_last_pid(p.last_pid);
	return (pipe_sighandle(), data->child_state = false, p.ret);
}
