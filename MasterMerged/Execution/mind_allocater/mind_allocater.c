/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_allocater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:54:47 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:56 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

t_mind_alloc	**get_head(void)
{
	static t_mind_alloc	*gc = NULL;

	return (&gc);
}

int	add_to_gc(void *new_address)
{
	t_mind_alloc	**head;
	t_mind_alloc	*new_alloc;

	new_alloc = malloc(sizeof(t_mind_alloc));
	if (!new_alloc)
	{
		free(new_address);
		mind_free_all(PANIC);
	}
	head = get_head();
	new_alloc->ptr = new_address;
	new_alloc->free_at_end = false;
	new_alloc->next = *head;
	*head = new_alloc;
	return (EXIT_SUCCESS);
}

void	mind_free_all(bool panic)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;
	t_tree			**tree;
	t_envlist		**env;

	tree = get_tree();
	clean_tree_fds(*tree);
	close_io();
	head = get_head();
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = tmp;
	}
	*get_head() = NULL;
	if (panic)
	{
		env = get_env();
		free_envlist(*env);
		free(*get_pwd_reserve());
		free_argv(*get_env_vec());
		exit(peak_status());
	}
}

int	add_to_gc_no_ex(void *new_address)
{
	t_mind_alloc	**head;
	t_mind_alloc	*new_alloc;

	new_alloc = malloc(sizeof(t_mind_alloc));
	if (!new_alloc)
	{
		free(new_address);
		return (EXIT_FAILURE);
	}
	head = get_head();
	new_alloc->ptr = new_address;
	new_alloc->free_at_end = false;
	new_alloc->next = *head;
	*head = new_alloc;
	return (EXIT_SUCCESS);
}

void	*allocate_gc_no_exit(void *ptr)
{
	if (!ptr)
		return (NULL);
	if (add_to_gc_no_ex(ptr) != EXIT_SUCCESS)
		return (NULL);
	return (ptr);
}
