#include "../../Parse/minishell.h"

static t_arg	*create_new_arg_node(char *value, t_arg *original_arg)
{
	t_arg	*new_node;

	new_node = allocate_gc(malloc(sizeof(t_arg)));
	
	new_node->value = allocate_gc(ft_strdup(value));
	if (new_node->value == NULL)
		return (NULL);
	new_node->tok = original_arg->tok;
	new_node->was_s_quote = original_arg->was_s_quote;
	new_node->was_d_quote = original_arg->was_d_quote;

	new_node->space_next = original_arg->space_next;
	
	new_node->next = NULL;
	return (new_node);
}
t_arg	*split_and_create_nodes(char *expanded_value, t_arg *original_arg)
{
	char	**split_result;
	t_arg	*head;
	t_arg	*current;
	t_arg	*new_node;
	int		i;

	split_result = tab_split(expanded_value, " \t");
    if (split_result == NULL)
		return (NULL);
	if (split_result[0] == NULL)
	{
		new_node = create_new_arg_node("", original_arg);
		if (new_node == NULL)
			return (NULL);
		new_node->space_next = original_arg->space_next;
		return (new_node);
	}
	head = NULL;
	current = NULL;
	i = 0;
	while (split_result[i] != NULL)
	{
		new_node = create_new_arg_node(split_result[i], original_arg);
		if (split_result[i] != NULL && split_result[i + 1] != NULL)
			new_node->space_next = true;
		else
			new_node->space_next = original_arg->space_next; 
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	
	return (head);
}
