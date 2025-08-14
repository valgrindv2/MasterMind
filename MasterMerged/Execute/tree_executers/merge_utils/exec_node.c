#include "../../execute.h"

static char	*find_in_path(char *cmd, t_envlist *env)
{
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i;

	while (env && ft_strcmp(env->variable, "PATH") != 0)
		env = env->next;
	if (!env || !env->value)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (free_argv(paths), full_path);
		free(full_path);
		i++;
	}
	free_argv(paths);
	return (NULL);
}

static char	*get_absolute_path(char *cmd, t_envlist *env)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (find_in_path(cmd, env));
}

static void	print_exec_error(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		dprintf(STDERR_FILENO, "Migrane: %s: No such file or directory\n", cmd);
	else
		dprintf(STDERR_FILENO, "Migrane: %s: command not found\n", cmd);
}

static int	handle_child(t_tree *node, t_data *data)
{
	char	*path;

	path = get_absolute_path(node->argv[0], data->env);
	execve(path, node->argv, data->env_vec);
	print_exec_error(node->argv[0]);
	// TODO: garbage collector cleanup here
	free(path);
	free_argv(data->env_vec);
	free_envlist(data->env);
	exit(EXECVE_FAILURE);
}

int	exec_node(t_tree *node, t_data *data)
{
	pid_t	id;
	int		ex_status;

	if (node->fake == true)
		return (EXIT_SUCCESS);
	id = fork(); // protect.
	if (id == 0)
		handle_child(node, data);
	waitpid(id, &ex_status, 0);
	if (WIFEXITED(ex_status))
		return (WEXITSTATUS(ex_status));
	if (WIFSIGNALED(ex_status))
		return (128 + WTERMSIG(ex_status));
	return (ex_status);
}
