/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:52:11 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/19 08:54:42 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_flag = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		if (g_flag != SIGINT)
			printf("\n");
		rl_on_new_line();
		rl_redisplay();
		**get_exit_status() = 1;
	}
	else if (signum == SIGQUIT)
		return ;
}

void	sig_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_flag = SIGINT;
		close(STDIN_FILENO);
	}
}

void	sig_kill(int signum)
{
	if (signum == SIGINT)
		mind_free_all(PANIC);
	else if (signum == SIGQUIT)
		mind_free_all(PANIC);
}
