#include "../execute.h"

t_mind_alloc    **get_head(void)
{
    static t_mind_alloc *gc = NULL;
    return (&gc);
}

// add ptr to gc
int add_to_gc(void *new_address)
{
    t_mind_alloc **head;
    t_mind_alloc *new_alloc;

    new_alloc = malloc(sizeof(t_mind_alloc));
    if (!new_alloc)
    {
        free(new_address);
        mind_free_all(PANIC);
    }
    head = get_gc_head();
    new_alloc->ptr = new_address;
    new_alloc->next = *head;
    *head = new_alloc;
    return EXIT_SUCCESS;
}

void    *allocate_gc(void *ptr)
{
    if (!ptr)
        mind_free_all(PANIC);
    add_to_gc(ptr);
    return (ptr);
}

void mind_free_all(bool panic)
{
    t_mind_alloc **head;
    t_mind_alloc *tmp;

    head = get_gc_head();
    while (*head)
    {
        tmp = (*head)->next;
        free((*head)->ptr);
        free(*head);
        *head = tmp;
    }
    if (panic)
    {
        // free env_vec
        // free env
        exit(EXIT_FAILURE);
    }
}
