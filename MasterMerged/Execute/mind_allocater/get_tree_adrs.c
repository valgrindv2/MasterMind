#include "../execute.h"

static void	add_arg_list_to_gc(t_arg *arg)
{
	while (arg)
	{
		if (arg->value)
			allocate_gc(arg->value);
		allocate_gc(arg);
		arg = arg->next;
	}
}

static void	add_red_list_to_gc(t_red *red)
{
	while (red)
	{
		if (red->value)
			allocate_gc(red->value);
		allocate_gc(red);
		red = red->next;
	}
}

static void	add_double_str_to_gc(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		allocate_gc(arr[i++]);
	allocate_gc(arr);
}

void	tree_gc_collector(t_tree *node)
{
	if (!node)
		return ;
	if (node->value)
		allocate_gc(node->value);
	add_double_str_to_gc(node->argv);
	add_arg_list_to_gc(node->arg);
	add_red_list_to_gc(node->red);
	allocate_gc(node);
	tree_gc_collector(node->left);
	tree_gc_collector(node->right);
}
