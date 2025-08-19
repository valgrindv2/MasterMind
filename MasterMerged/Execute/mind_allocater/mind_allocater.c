/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_allocater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:54:47 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 05:51:43 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

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

// free env_vec
// free env

void	mind_free_all(bool panic)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;
	t_tree			**tree;
	t_envlist		**env;
	char			**pwd;

	tree = get_tree();
	clean_tree_fds(*tree);
	head = get_head();
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = tmp;
	}
	if (panic)
	{
		perror("PANIC");
		env = get_env();
		free_envlist(*env);
		pwd = get_pwd_reserve();
		free(*pwd);
		exit(EXIT_FAILURE);
	}
}

int	add_to_gc_no_ex(void *new_address)
{
	t_mind_alloc	**head;
	t_mind_alloc	*new_alloc;

	new_alloc = malloc(sizeof(t_mind_alloc));
	if (!new_alloc)
		return (EXIT_FAILURE);
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
