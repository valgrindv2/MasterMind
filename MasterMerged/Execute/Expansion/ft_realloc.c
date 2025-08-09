#include "../execute.h"

char    **realloc_pockets(char **old_pocket, size_t old_cap, size_t new_cap)
{
    size_t  i;
    char    **new_pocket;

    new_pocket = malloc (sizeof(char *) * new_cap);
    if (!new_pocket)
        return (NULL);
    i = 0;
    while (i < old_cap)
    {
        if (old_pocket[i])
        {
            new_pocket[i] = ft_strdup(old_pocket[i]);
            if (!new_pocket[i])
            {
                while (--i >= 0)
                    free(new_pocket[i]);
                free(new_pocket);
                return (NULL);
            }
        }
        else
            new_pocket[i] = NULL;
        i++;
    }
    return (free_argv(old_pocket), new_pocket);
}
