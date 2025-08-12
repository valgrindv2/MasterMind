/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:52:11 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/12 14:26:46 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_flag = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
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
