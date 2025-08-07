/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:15:02 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 03:05:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int  g_flag;
void	f(void)
{
	system("leaks minishell");
}

void	check_fd_leaks(void)
{
	char	cmd[64];

	snprintf(cmd, sizeof(cmd), "lsof -p %d", getpid());
	printf("=== FD Leak Check ===\n");
	system(cmd);
}

void	voiders(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

t_tree	*masterpasrse(char *input, t_data *data, t_token **prompts)
{
	t_token	*token;
	
	if (!edge_braces(input, data))
		return (NULL);
	// printf("no_sef > %d\n", data->no_sef);
	token = get_identity(input, data);
	// clean_id_class(&token, FAIL);
	*prompts = re_identity(token);
	clean_id_class(prompts, FAIL);
	// return (build_tree(*prompts));
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;
	t_tree	*tree;
	t_token	*re_built;

	tree = NULL;
	input = NULL;
	voiders(argc, argv, env);
	init_data_struct(&data, env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_flag = 0;
		input = readline("\033[32mMaster@Mindv3.0> \033[0m");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
			add_history(input);
		tree = masterpasrse(input, &data, &re_built);
		// print_tree(tree);
		// execute_tree(tree, &data, env, re_built);
	}
	return (free_argv(data.env_vec), free_envlist(data.env),
		free(input), EXIT_SUCCESS);
}

/*
		'ls' || (cat | ls ) && << eof | cat -e << ok | "cat" 
*/