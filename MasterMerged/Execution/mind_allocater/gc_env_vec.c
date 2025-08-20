/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_env_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:48:33 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:54 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

char	***get_env_vec(void)
{
	static char	**env_vec = NULL;

	return (&env_vec);
}

void	set_env_vec(char **envp)
{
	char	***env_vec;

	env_vec = get_env_vec();
	*env_vec = envp;
}
