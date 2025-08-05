#include "../../execute.h"

int con_check(t_tree *node)
{
    if (node->argv[1][0] == '.' && node->argv[1][1] == '\0')
        return (0);
    if (node->argv[1][0] == '.' && node->argv[1][1] == '.'
        && node->argv[1][2] == '\0')
        return (0);
    return (1);
}