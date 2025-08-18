#include "../execute.h"

// might need outside.
void    free_arg_list(t_arg *arg)
{
	t_arg   *tmp;

	if (!arg)
		return ;
	while (arg)
	{
		tmp = arg->next;
		free(arg->value);
		free(arg);
		arg = tmp;
	}
}

static size_t   arglist_size(t_arg *arg)
{
	size_t  size;

	size = 0;
	while (arg)
	{
		size++;
		arg = arg->next;
	}
	return (size);
}
// entry
char **convert_list_to_argv(t_arg *arg, t_data *data)
{
	t_convert   cv;

	if (expand_list(arg, data) != EXIT_SUCCESS)
		return (NULL);
	cv.argc = arglist_size(arg);
	cv.argv = allocate_gc(malloc((cv.argc + 1) * sizeof(char *)));
	cv.i = 0;
	while (arg)
	{
		cv.argv[cv.i++] = join_system(&arg);
	}
	cv.argv[cv.i] = NULL;
	cv.new_argv = ifs_pass(cv.argv);
	return (cv.new_argv);
}

