#include "../execute.h"

static bool has_star(char *str)
{
    int i;

    i = 0;
    while (str[i])
        if (str[i++] == '*')
            return (true);
    return (false);
}

static char **get_all_files(void)
{
    DIR *dir; // pointer to a structure, with directory data.
    struct dirent *entry; // pointe to a structure of file/entry data. we use this to get the file name.
    char **files; // allocated list argv
    int count; // counting files to allocated argv

    dir = opendir("."); // opens current dir
    if (!dir)
        return (NULL); // if this fails returb failure and clean up.
    count = 0; // we count the number of files for allocation.
    while ((entry = readdir(dir))) // each time we call readdir we get a pointer to a file struct in order
        if (entry->d_name[0] != '.' && entry->d_name[0] != '*')
            count++;
    closedir(dir); // we close dir to cleanup
    dir = opendir(".");
    if (!dir)
        return (NULL);
    files = malloc(sizeof(char *) * (count + 1));
    if (!files)
        return (NULL); // malloc failure.
    count = 0;
    while ((entry = readdir(dir)))
        if (entry->d_name[0] != '.' && entry->d_name[0] != '*')
            files[count++] = strdup(entry->d_name);
    files[count] = NULL;
    return (closedir(dir), files);
}

static int count_args(char **args)
{
    int i = 0;
    while (args && args[i])
        i++;
    return i;
}

static int total_size(char **argv, int file_count)
{
    int i;
    int new_size;

    i = 0;
    while (argv[i])
    {
        if (has_star(argv[i]))
            new_size += file_count;
        else
            new_size++;
        i++;
    }
    return (new_size);
}

typedef struct s_linkpattern
{
    char    **files;
    char    **new_argv;
    int     old_argc;
    int     file_count;
    int     new_size;
    int     i;
    int     j;
    int     k;
}   t_linkpattern;

static int link_patterns_to_argv(t_tree *node)
{
    t_linkpattern lp;

    lp.files = get_all_files();
    if (!lp.files)
        return (EXIT_FAILURE);
    lp.old_argc = count_args(node->argv);
    lp.file_count = count_args(lp.files);
    lp.new_size = total_size(node->argv, lp.file_count); // how many pointers in the new argv list.
    lp.new_argv = malloc(sizeof(char *) * (lp.new_size + 1));
    if (!lp.new_argv)
        return (EXIT_FAILURE);
    lp.i = 0;
    lp.k = 0;
    while (node->argv[lp.i])
    {
        if (has_star(node->argv[lp.i]))
        {
            lp.j = 0;
            while (lp.files[lp.j])
                lp.new_argv[lp.k++] = strdup(lp.files[lp.j++]);
        }
        else
            lp.new_argv[lp.k++] = strdup(node->argv[lp.i]);
        lp.i++;
    }
    lp.new_argv[lp.k] = NULL;
    free_argv(node->argv);
    node->argv = lp.new_argv;
    free_argv(lp.files);
    return (EXIT_SUCCESS);
}


// function entry
int expand_wild_cards(t_tree *node)
{
    int i;

    i = 0;
    while (node->argv[i])
        if (has_star(node->argv[i++]))
            link_patterns_to_argv(node);
    return (EXIT_SUCCESS);
}
