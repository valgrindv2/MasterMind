/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_field_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:27:07 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

size_t	ifs_list_size(t_ifs *curr)
{
	size_t	size;

	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

int	add_ifs_back(t_ifs **head, char *str)
{
	t_ifs	*new;
	t_ifs	*curr;

	new = allocate_gc(malloc(sizeof(t_ifs)));
	new->string = allocate_gc(ft_strdup(str));
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (EXIT_SUCCESS);
}

char	**ifs_list_to_argv(t_ifs *head)
{
	size_t	size;
	t_ifs	*curr;
	char	**argv;
	size_t	i;

	i = 0;
	size = ifs_list_size(head);
	argv = allocate_gc(malloc(sizeof(char *) * (size + 1)));
	if (!argv)
		return (NULL);
	curr = head;
	while (i < size)
	{
		argv[i] = allocate_gc(ft_strdup(curr->string));
		curr = curr->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
