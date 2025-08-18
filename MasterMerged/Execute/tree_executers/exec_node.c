#include "../execute.h"

static char	*search_in_cwd(char *cmd)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*full_path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	tmp = allocate_gc(ft_strjoin(cwd, "/"));
	full_path = allocate_gc(ft_strjoin(tmp, cmd));
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}

char	*find_in_path(char *cmd, t_envlist *env)
{
	t_path	pt;

	while (env && ft_strcmp(env->variable, "PATH") != 0)
		env = env->next;
	if (!env || !env->value || !env->value[0])
		return (search_in_cwd(cmd));
	pt.paths = ft_split(env->value, ':');
	pt.i = 0;
	while (pt.paths[pt.i])
	{
		pt.tmp = allocate_gc(ft_strjoin(pt.paths[pt.i], "/"));
		pt.full_path = allocate_gc(ft_strjoin(pt.tmp, cmd));
		if (access(pt.full_path, X_OK) == 0)
			return (pt.full_path);
		pt.i++;
	}
	return (NULL);
}

static char	*get_absolute_path(char *cmd, t_envlist *env, int *flag, int *err)
{
	char	*path;

	path = NULL;
	if (!cmd || !*cmd)
		return (*err = 127, NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (is_it_dir(cmd))
			return (*err = 21, NULL);
		if (access(cmd, X_OK) == 0)
			return (*err = errno, allocate_gc(ft_strdup(cmd)));
		else if (access(cmd, X_OK) == -1 || access(cmd, F_OK) == -1)
			return (*flag = 1, *err = errno, allocate_gc(ft_strdup(cmd)));
		return (NULL);
	}
	path = find_in_path(cmd, env);
	if (!path)
		return (*err = 127, NULL);
	return (path);
}

static int	handle_child(t_tree *node, t_data *data)
{
	char	*path;
	int		flag;
	int		err_number;

	path = NULL;
	flag = 0;
	err_number = 0;
	path = get_absolute_path(node->argv[0], data->env, &flag, &err_number);
	if (!path)
		exit(err_number);
	if (path[o_ft_strlen(path) - 1] == '/' || flag == 1)
	{
		if (err_number != 0)
			exit(err_number);
	}
	printf("===> %s\n", path);
	execve(path, node->argv, data->env_vec);
	exit(pipe_child_free(1));
}

int	exec_node(t_tree *node, t_data *data)
{
	pid_t	id;
	int		ex_status;

	if (node->fake == true)
		return (EXIT_SUCCESS);
	start_signals();
	id = fork();
	if (id == -1)
		return (mind_free_all(PANIC), EXIT_FAILURE);
	if (id == 0)
	{
		signal(SIGINT, sig_kill);
		signal(SIGQUIT, sig_kill);
		handle_child(node, data);
	}
	waitpid(id, &ex_status, 0);
	pipe_sighandle();
	if (WIFEXITED(ex_status))
		return (errors_msgs(WEXITSTATUS(ex_status)));
	if (WIFSIGNALED(ex_status))
		return (printf("\n"), 128 + WTERMSIG(ex_status));
	return (ex_status);
}
