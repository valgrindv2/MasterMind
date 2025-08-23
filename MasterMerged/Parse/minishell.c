/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:15:02 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/23 16:02:24 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_flag;

void	master_tools(int argc, char **argv, char **env, t_data *data)
{
	if (!isatty(0) || !isatty(1))
	{
		puterror("Master@Mind: Shell not executed as a device input\n");
		exit(F);
	}
	if (argc > 1)
	{
		puterror("Master@Mind: Shell does not accept arguments\n");
		exit(F);
	}
	voiders(argc, argv, env);
	init_data_struct(data, env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	set_exit_status(&data->exit_status);
}

int	scan_input(char *input, t_data *data)
{
	if (input == NULL)
	{
		printf("exit\n");
		freeiers(data, input);
		exit (data->exit_status);
	}
	if (input[0] != '\0')
		add_history(input);
	return (1);
}

t_tree	*masterpasrse(char **input, t_data *data, t_token **prompts)
{
	t_token	*token;

	data->no_sef = true;
	if (!evaluate_case(*input, data))
		return (puterror("Master@Mind: Invalid Use Of Braces\n"),
			data->exit_status = 258, free(*input), *input = NULL, NULL);
	data->here_node = 0;
	token = get_identity(*input, data);
	*prompts = re_identity(token);
	return (build_tree(*prompts, data));
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;
	t_tree	*tree;
	t_token	*re_built;

	tree = NULL;
	input = NULL;
	master_tools(argc, argv, env, &data);
	while (1)
	{
		if (!get_current_state(STDIN_FILENO, &data))
			return (freeiers(&data, input), EXIT_SUCCESS);
		input = readline("Master@Mindv3.0> ");
		g_flag = 0;
		if (!scan_input(input, &data))
			break ;
		tree = masterpasrse(&input, &data, &re_built);
		execute_tree(tree, &data, env, re_built);
		if (!restore_previous_state(STDIN_FILENO, &data))
			panic(&data, input);
	}
	return (freeiers(&data, input), EXIT_SUCCESS);
}
