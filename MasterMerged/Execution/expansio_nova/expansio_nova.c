#include "../../Parse/minishell.h"

static bool	should_expand(t_arg *arg)
{
	if (arg->was_s_quote)
		return (false);
	if (arg->value == NULL || arg->value[0] == '\0')
		return (false);
	if (arg->value[0] == '$' && (arg->value[1] == '\0' 
		|| arg->value[1] == ' ' || arg->value[1] == '\t'
		|| arg->value[1] == '\'' || arg->value[1] == '\"'))
		return (false);
	return (true);
}
static t_arg	*last_arg(t_arg *list)
{
	t_arg	*current;

	if (list == NULL)
		return (NULL);
	
	current = list;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

static int	process_expansion(t_arg *arg, t_data *data, t_arg **curr, bool in_assign)
{
	char	*expanded_value;
	t_arg	*new_nodes;
	t_arg	*last_new_node;

	if (arg->was_d_quote || in_assign)
		arg->value = expand_double_quoted(arg->value, data);
	else
	{
		expanded_value = expand_double_quoted(arg->value, data);
		new_nodes = split_and_create_nodes(expanded_value, arg);
		last_new_node = last_arg(new_nodes);
		last_new_node->next = arg->next;
        arg->value = new_nodes->value;
        arg->tok = new_nodes->tok;
        arg->was_s_quote = new_nodes->was_s_quote;
        arg->was_d_quote = new_nodes->was_d_quote;
        arg->space_next = new_nodes->space_next;
		
		if (new_nodes->next != NULL)
			arg->next = new_nodes->next;
		else
			arg->next = NULL;
		*curr = last_new_node;
	}
	return (EXIT_SUCCESS);
}

int	expand_list_new(t_arg *arg, t_data *data)
{
	t_arg	*current;
    t_arg   *prev;

	current = arg;
    prev = NULL;
	while (current != NULL)
	{
        prev = current;
		if (should_expand(current))
		{
            if (prev != NULL && ft_strchr(prev->value, '='))
            {
                if (process_expansion(current, data, &current, true) != EXIT_SUCCESS)
				    return (EXIT_FAILURE);
            }
            else
            {
			    if (process_expansion(current, data, &current, false) != EXIT_SUCCESS)
				    return (EXIT_FAILURE);
            }
		}
        prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
