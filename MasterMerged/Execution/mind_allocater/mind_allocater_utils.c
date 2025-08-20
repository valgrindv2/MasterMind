/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_allocater_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:54:47 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:56 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

char	*env_get_value(char *str)
{
	int		equals;
	bool	has_equal;
	char	*value;

	if (!str)
		return (perror("NULL Key in envp."), NULL);
	equals = 0;
	has_equal = false;
	while (str[equals])
	{
		if (str[equals++] == '=')
		{
			has_equal = true;
			break ;
		}
	}
	if (has_equal)
		value = ft_substr(str, equals, o_ft_strlen(str));
	else
		value = ft_strdup("");
	return (value);
}

char	*env_get_key(char *str)
{
	int		equals;
	bool	has_equal;
	char	*key;

	if (!str)
		return (perror("NULL Key in envp."), NULL);
	equals = 0;
	has_equal = false;
	while (str[equals])
	{
		if (str[equals] == '+' || str[equals] == '=')
		{
			has_equal = true;
			break ;
		}
		equals++;
	}
	if (has_equal)
		key = ft_substr(str, 0, equals);
	else
		key = ft_strdup(str);
	return (key);
}

int	env_add_to_gc(void *new_address)
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
	new_alloc->free_at_end = true;
	new_alloc->next = *head;
	*head = new_alloc;
	return (EXIT_SUCCESS);
}

void	*env_allocate_gc(void *ptr)
{
	if (!ptr)
		mind_free_all(PANIC);
	env_add_to_gc(ptr);
	return (ptr);
}

void	*allocate_gc(void *ptr)
{
	if (!ptr)
		mind_free_all(PANIC);
	add_to_gc(ptr);
	return (ptr);
}
