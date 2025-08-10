#include "../minishell.h"

void linkednev_db(t_envlist **env)
{
    t_envlist *trav;

    trav = *env;
    printf("Debbugging The Linked ENV...\n");
    while(trav != NULL)
    {
        printf("%s%s\n", trav->variable, trav->value);
        trav = trav->next;
    }
}