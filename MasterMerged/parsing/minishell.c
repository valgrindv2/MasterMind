/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:15:02 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/11 18:49:29 by ayel-bou         ###   ########.fr       */
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
	// (void)env;
}

t_tree	*masterpasrse(char *input, t_data *data, t_token **prompts)
{
	t_token	*token;
	
	if (!edge_braces(input, data))
		return (NULL);
	token = get_identity(input, data);
	*prompts = re_identity(token);
	// debbuger_tk(*prompts);
	// read_files(*prompts);
	// clean_id_class(prompts, FAIL);
	return (build_tree(*prompts));
	// return (NULL);
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
	// isatty
	while (1)
	{
		g_flag = 0;
		input = readline("Master@Mindv3.0> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		tree = masterpasrse(input, &data, &re_built);
		// print_tree(tree);
		execute_tree(tree, &data, env, re_built);
	}
	return (free(data.pwd_reserve), free_argv(data.env_vec), free_envlist(data.env),
		free(input), EXIT_SUCCESS);
}

/*

	'ls' || (cat | ls ) && << eof | cat -e << ok | "cat" 
		<< eof << ok << ok2 l <<f << f2 << f4 | cat << eof << ok2 | (cat | clear) FAIL HEREDOC DELIMITER SCRAPP
		(ls -la > f2 << eof) && << ok3 SEF FALSE POSITIVE

		Master@Mindv3.0> ls | cat << eof << ok2 << ok3 && (cat || pwd) | cd > f1 || (ls -la > f2 << eof) && << ok3 | >f10 >f11 echo $? || (ls *)
		Here_doc> eof
		Here_doc> ok2
		Here_doc> ok3
		new Del >> eof
		Here_doc> eof
		MasterMind: Syntax Error Near Unexpected Token `&&'
		Master@Mindv3.0> (ls -la >(ls -la > f2 << eof) && << ok3
		new Del >> eof
		Here_doc> eof
		MasterMind: Syntax Error Near Unexpected Token `&&'
		Master@Mindv3.0> (ls -la >ls | cat << eof << ok2 << ok3 && (cat || pwd) | cd > f1 || (ls -la > f2 << eof) | << ok3 | >f10 >f11 echo $? || (ls *)
		Here_doc> eof
		Here_doc> ok2
		Here_doc> ok3
		new Del >> eof
		Here_doc> eof
		MasterMind: Syntax Error Near Unexpected Token `|'
		Master@Mindv3.0> ls | cat << eof << ok2 << ok3 && (cat || pwd) | cd > f1 || ls -la > f2 << eof | << ok3 | >f10 >f11 echo $? || (ls *)
		Here_doc> eof
		Here_doc> ok2
		Here_doc> ok3
		Here_doc> eof
		MasterMind: Syntax Error Near Unexpected Token `|'
		Master@Mindv3.0> ls | cat << eof << ok2 << ok3 && (cat || pwd) | cd > f1 || << ok3 | >f10 >f11 echo $? || (ls *)
		Here_doc> eof
		Here_doc> ok2
		Here_doc> ok2
		Here_doc> ok3
		MasterMind: Syntax Error Near Unexpected Token `||'
		Master@Mindv3.0> ls | cat << eof << ok2 << ok3 && (cat || pwd) | cd > f1

*/