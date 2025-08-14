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

    cv.free_head = arg;
    if (expand_list(arg, data) != EXIT_SUCCESS)
        return (free_arg_list(cv.free_head), NULL);
    cv.argc = arglist_size(arg);
    cv.argv = malloc((cv.argc + 1) * sizeof(char *));
    if (!cv.argv)
        return (free_arg_list(cv.free_head), NULL);
    cv.i = 0;
    while (arg)
    {
        cv.argv[cv.i] = join_system(&arg);  // join args if needed
        if (!cv.argv[cv.i++])
        {
            while (--cv.i >= 0)
                free(cv.argv[cv.i]);
            return (free(cv.argv), free_arg_list(cv.free_head), NULL);
        }
    }
    cv.argv[cv.i] = NULL;
    cv.new_argv = ifs_pass(cv.argv);
    if (!cv.new_argv)
        return (free_argv(cv.argv), free_arg_list(cv.free_head), NULL);
    return (free_argv(cv.argv), free_arg_list(cv.free_head), cv.new_argv);
}

