/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:26 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:14 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static int	update_env_variables(t_data *data)
{
	data->env_vec = convert_list_to_envp(data->env, data);
	if (!data->env_vec)
		return (mind_free_all(PANIC), EXIT_FAILURE);
	set_env_vec(data->env_vec);
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
			return (restore_io(data, node->red == NULL), EXIT_FAILURE);
		if (add_last_executed(node, data) != EXIT_SUCCESS)
			return (restore_io(data, node->red == NULL), EXIT_FAILURE);
		node->argv = remove_nonprintables_argv(node->argv);
		if (validate_builtin(node->argv[0]))
			data->exit_status = exec_builtin(node, data);
		else
			data->exit_status = exec_node(node, data);
	}
	else
		data->exit_status = EXIT_SUCCESS;
	restore_io(data, node->red == NULL);
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
		return (data->exit_status = short_circuit_operand(node,
				node->tok, data));
	if (node->left)
		return (data->exit_status = recursive_execution(node->left, data));
	if (node->right)
		return (data->exit_status = recursive_execution(node->right, data));
	return (EXIT_SUCCESS);
}

int	execute_tree(t_tree *root, t_data *data, char **env, void *re_built)
{
	int	rec_exit_status;

	(void)re_built;
	if (!root)
		return (EXIT_FAILURE);
	set_tree(root);
	set_data(data);
	set_pwd(data->pwd_reserve);
	tree_gc_collector(root);
	if (merger(root, data, env) != EXIT_SUCCESS)
		return (perror("Merge Failed"), EXIT_FAILURE);
	rec_exit_status = recursive_execution(root, data);
	set_tree(root);
	set_data(data);
	set_pwd(data->pwd_reserve);
	set_env(data->env);
	set_env_vec(data->env_vec);
	mind_free_all(CHILL);
	return (rec_exit_status);
}
