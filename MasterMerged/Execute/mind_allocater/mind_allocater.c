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

void	mind_free_all(bool panic)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;

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
		// free env_vec
		// free env
		perror("PANIC");
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

int	pipe_child_free(int ret)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;

	head = get_head();
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = tmp;
	}
	// free env_vec
	// free env
	return (ret);
}

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
