/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:15:02 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 06:54:55 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_flag;

void	master_tools(int argc, char **argv, char **env, t_data *data)
{
	if (!isatty(1))
		exit(F);
	voiders(argc, argv, env);
	init_data_struct(data, env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	scan_input(char *input)
{
	if (input == NULL)
	{
		printf("exit\n");
		return (0);
	}
	if (input[0] != '\0')
		add_history(input);
	return (1);
}

t_tree	*masterpasrse(char *input, t_data *data, t_token **prompts)
{
	t_token	*token;

	if (!edge_braces(input, data))
		return (NULL);
	token = get_identity(input, data);
	*prompts = re_identity(token);
	return (build_tree(*prompts));
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
		if (!scan_input(input))
			break ;
		tree = masterpasrse(input, &data, &re_built);
		execute_tree(tree, &data, env, re_built);
		if (!restore_previous_state(STDIN_FILENO, &data))
			panic(&data, input);
		if (data.read_f == false)
			g_flag = 0;
	}
	return (freeiers(&data, input), EXIT_SUCCESS);
}
