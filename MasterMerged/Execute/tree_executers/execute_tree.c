#include "../execute.h"

void	print_exec_error(char *cmd, int code)
{
	if (code == 127)
	{
		if (ft_strchr(cmd, '/'))
			dprintf(STDERR_FILENO, "Migrane: %s: No such file or directory\n", cmd);
		else
			dprintf(STDERR_FILENO, "Migrane: %s: command not found\n", cmd);
	}
	else if (code == 126)
	{
		if (o_ft_strlen(cmd) > 0 && cmd[o_ft_strlen(cmd) - 1] == '/')
			dprintf(STDERR_FILENO, "Migrane: %s: Is a directory\n", cmd);
		else
			dprintf(STDERR_FILENO, "Migrane: %s: Permission denied\n", cmd);
	}
}

static int  update_env_variables(t_data *data)
{
    data->env_vec = convert_list_to_envp(data->env, data);
    if (!data->env_vec)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static int	exec_command(t_tree *node, t_data *data)
{
	node->argv = convert_list_to_argv(node->arg, data);
	if (!node->argv)
		return (EXIT_FAILURE);
	if (!anon(node, arg_count(node->argv)) && node->argv[0])
	{
		if (node->red && handle_red(node, data) != EXIT_SUCCESS)
		return (restore_IO(data->saved_in, data->saved_out, node->red == NULL),
				EXIT_FAILURE);
		if (add_last_executed(node, data) != EXIT_SUCCESS)
			return (restore_IO(data->saved_in, data->saved_out, node->red == NULL),
				EXIT_FAILURE);
		// normalize_command(node->argv[0]);
		node->argv = remove_nonprintables_argv(node->argv);
		if (validate_builtin(node->argv[0]))
			data->exit_status = exec_builtin(node, data);
		else
			data->exit_status = exec_node(node, data);
	}
	else
		data->exit_status = EXIT_SUCCESS;
	restore_IO(data->saved_in, data->saved_out, node->red == NULL);
	if (update_env_variables(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (data->exit_status);
}

int	recursive_execution(t_tree *node, t_data *data)
{
	if (node->tok == COMMAND_ID)
		return (exec_command(node, data));
	if (node->tok == PIPE_ID)
		return (data->exit_status = execute_pipeline(node, data, STDIN_FILENO));
	if (node->tok == AND_ID || node->tok == OR_ID)
		return (data->exit_status = short_circuit_operand(node, node->tok, data));
	if (node->left)
		return (data->exit_status = recursive_execution(node->left, data));
	if (node->right)
		return (data->exit_status = recursive_execution(node->right, data));
	return (EXIT_SUCCESS);
}

// entry point.
int execute_tree(t_tree *root, t_data *data, char **env, void *re_built)
{
    int rec_exit_status;

    if (!root)
        return (mind_free_all(CHILL), EXIT_FAILURE);
    if (merger(root, data, env) != EXIT_SUCCESS)
        return (mind_free_all(PANIC), perror("Merge Failed"), EXIT_FAILURE);
    rec_exit_status = recursive_execution(root, data);
    return (mind_free_all(CHILL), rec_exit_status);
}
