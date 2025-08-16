#include "../execute.h"

static void cmd_add_last(t_tree *node, t_plist **head)
{
    t_plist *new_pipe_cmd;
    t_plist *curr;

    new_pipe_cmd = malloc(sizeof(t_plist));
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

static void flatten_pipeline(t_tree *node, t_plist **head)
{
    t_plist *plist;

    if (!node)
        return ;
    // base case
    if (node->tok == PIPE_ID)
    {
        flatten_pipeline(node->left, head);
        flatten_pipeline(node->right, head);
    }
    else
        cmd_add_last(node, head);
}

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

static void	setup_child_io(int prev_fd, int fds[2], int is_pipe)
{
	if (prev_fd != STDIN_FILENO)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (is_pipe)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
	}
}

static pid_t	fork_pipeline_node(t_plist *node, t_data *data,
									int prev_fd, int fds[2], int is_pipe)
{
	pid_t	pid;

	data->child_state = true;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, sig_kill);
		signal(SIGQUIT, sig_kill);
		setup_child_io(prev_fd, fds, is_pipe);
		/* TODO: garbage collector cleanup here */
		exit(recursive_execution(node->cmd_node, data));
	}
	return (pid);
}

static int	wait_for_last_pid(pid_t last_pid)
{
	int		w_pid;
	int		status;
	int		ex_st;

	ex_st = 0;
	w_pid = -1;
	while ((w_pid = wait(&status)) > 0)
	{
		if (w_pid == last_pid)
			ex_st = WEXITSTATUS(status);
	}
	return (ex_st);
}
// entry
int	execute_pipeline(t_tree *root, t_data *data, int input_fd)
{
	t_plist	*plist;
	t_plist	*curr;
	int		prev_fd;
	int		fds[2];
	pid_t	last_pid;
	int		is_pipe;
	int		ret;

	prev_fd = input_fd;
	plist = NULL;
	flatten_pipeline(root, &plist);
	last_pid = -1;
	curr = plist;
	while (curr)
	{
		is_pipe = curr->next != NULL;
		if (is_pipe && setup_pipe(fds) != EXIT_SUCCESS)
			return (free_pipe_list(plist), EXIT_FAILURE);
		last_pid = fork_pipeline_node(curr, data, prev_fd, fds, is_pipe);
		if (last_pid == -1)
			return (free_pipe_list(plist), EXIT_FAILURE);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (is_pipe)
		{
			close(fds[1]);
			prev_fd = fds[0];
		}
		curr = curr->next;
	}
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	free_pipe_list(plist);
	ret = wait_for_last_pid(last_pid);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!restore_previous_state(STDIN_FILENO, data))
	{
		// Garbage collector;
		exit(F);
	}
	if (WIFSIGNALED(ret))
		printf("\n");
	data->child_state = false;
	return (ret);
}
