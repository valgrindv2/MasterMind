#include "../execute.h"

void    *mind_allocater(size_t size, t_mind_alloc **head)
{
    void            *ptr;
    t_mind_alloc    *new_alloc;

    ptr = malloc (size);
    if (!ptr)
        return (NULL);
    new_alloc = malloc (sizeof(t_mind_alloc));
    if (!new_alloc)
        return (free(ptr), NULL);
    new_alloc->ptr = ptr;
    new_alloc->next = *head;
    *head = new_alloc;
    return (ptr);
}
void Mind_free(t_mind_alloc *head)
{
    t_mind_alloc *tmp;

    if (!head)
        return ;
    while (head)
    {
        tmp = head->next;
        free(head->ptr);
        free(head);
        head = tmp;
    }
}
