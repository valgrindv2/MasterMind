# include "../execute.h"

size_t  arg_count(char **argv)
{
    size_t  argc;

    argc = 0;
    while (argv[argc])
        argc++;
    return (argc);
}
