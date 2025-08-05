#include "../execute.h"

int short_circuit_operand(t_tree *node, t_grammar operand_id, t_data *data)
{
    int left_status = recursive_execution(node->left, data);
    if (operand_id == AND_ID) // A && B
    {
        if (left_status == EXIT_SUCCESS) 
            return (recursive_execution(node->right, data)); // if A succeeds exec B
        else
            return (left_status);
    }
    else if (operand_id == OR_ID) // A || B
    {
        if (left_status != EXIT_SUCCESS)
            return (recursive_execution(node->right, data)); // if A fail exec B
        else
            return (left_status);
    }
    return (EXIT_FAILURE); // should never return from here.
}
