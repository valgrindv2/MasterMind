/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:17 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/22 00:12:02 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

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

static char	*get_absolute_path(char *cmd, t_envlist *env, int *err, int *ex)
{
	char	*path;

	path = NULL;
	if (!cmd || !*cmd)
		return (*err = 127, NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (is_it_dir(cmd))
			return (*err = 21, NULL);
		if (access(cmd, F_OK) == 0)
			return (*err = errno, cmd);
		return (*ex = 1, NULL);
	}
	path = find_in_path(cmd, env);
	if (!path)
		return (*err = 127, NULL);
	return (path);
}

static int	handle_child(t_tree *node, t_data *data)
{
	char	*path;
	int		err_number;
	int		exists;

	exists = 0;
	path = NULL;
	err_number = 0;
	path = get_absolute_path(node->argv[0], data->env, &err_number, &exists);
	if (!path)
	{
		if (err_number == 21)
			exit(pipe_child_free(errors_msgs(err_number, node->argv[0])));
		if (exists == 0)
			exists_zero(node, data);
		else
			path = node->argv[0];
	}
	if (execve(path, node->argv, data->env_vec) != 0)
	{
		close_saved(data);
		exit(pipe_child_free((errors_msgs(errno, node->argv[0]))));
	}
	return (EXIT_SUCCESS);
}

int	exec_node(t_tree *node, t_data *data)
{
	pid_t	id;
	int		ex_status;

	if (node->fake == true)
		return (EXIT_SUCCESS);
	if (data->here_int == true)
		return (data->here_int = false, EXIT_SUCCESS);
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
		return (WEXITSTATUS(ex_status));
	if (WIFSIGNALED(ex_status))
		return (printf("\n"), 128 + WTERMSIG(ex_status));
	return (ex_status);
}
