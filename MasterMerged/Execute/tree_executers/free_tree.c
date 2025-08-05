#include "../execute.h"

void free_envlist(t_envlist *env)
{
    t_envlist   *tmp;

    if (!env)
        return ;
    while (env)
    {
        tmp = env->next;
        free(env->value);
        free(env->variable);
        free(env);
        env = tmp;
    }
}

static void free_redir(t_red *red)
{
    t_red *tmp;

    if (!red)
        return ;
    while (red)
    {
        tmp = red->next;
        free(red->value);
        free(red);
        red = tmp;
    }
}

void free_argv(char **argv)
{
    int i;

    i = 0;
    if (!argv)
        return ;
    while (argv[i])
    {
        free(argv[i++]);
    }
    free (argv);
}

void    free_tree(t_tree *node)
{
    if (!node)
        return ;

    if (node->left)
        free_tree(node->left);
    if (node->right)
        free_tree(node->right);
    free(node->value);
    free_argv(node->argv);
    free_redir(node->red);
    if (node->here_doc_fd != -1)
        close(node->here_doc_fd);
    free(node);
}

void    clean_up(t_tree *tree, t_data *data)
{
    if (tree)
    {
        free_tree(tree);
        tree = NULL;
    }
}
