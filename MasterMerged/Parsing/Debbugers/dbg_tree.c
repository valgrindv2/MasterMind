#include "../minishell.h"
#include <string.h>
#include <stdio.h>

// Translate grammar token to string
static const char *grammar_to_str(enum grammar tok)
{
    switch (tok)
    {
        case PIPE_ID:            return "PIPE";
        case RED_IN_ID:          return "RED_IN";
        case RED_OUT_ID:         return "RED_OUT";
        case RED_APP_ID:         return "RED_APP";
        case HERE_DOC_ID:        return "HERE_DOC";
        case AND_ID:             return "AND";
        case OR_ID:              return "OR";
        case BRACE_O_ID:         return "BRACE_O";
        case BRACE_C_ID:         return "BRACE_C";
        case S_QUOTE_ID:         return "S_QUOTE";
        case D_QUOTE_ID:         return "D_QUOTE";
        case STRING_ID:          return "STRING";
        case DEL_ID:             return "DEL";
        case INPUT_FILE_ID:      return "INPUT_FILE";
        case OUTPUT_FILE_ID:     return "OUTPUT_FILE";
        case INPUT_APP_FILE_ID:  return "INPUT_APP_FILE";
        case COMMAND_ID:         return "COMMAND";
        case ARG_ID:             return "ARG";
        default:                 return "UNKNOWN";
    }
}

// Print a single node’s info
static void print_node(t_tree *node)
{
    if (!node)
        return;

    printf("%s", grammar_to_str(node->tok));

    if (node->value)
    {
        printf(" [%s]\n", node->value);
        if (node->tok == DEL_ID)
        {
            printf("Was S Quoted >> %d\n", node->was_s_quote);
            printf("Was D Quoted >> %d\n", node->was_d_quote);
        }
    }
    else
        printf("\n");

    if (node->red)
        printer_red(node->red, " [Red] ");
    if (node->arg)
        printer_arg(node->arg, " [Arg] ");
}

// Recursive helper to print tree with visual branches
static void ft_print_tree(t_tree *node, const char *prefix, int is_last)
{
    if (!node)
        return;

    // Print current prefix + branch
    printf("%s", prefix);
    if (is_last)
        printf("└─ ");
    else
        printf("├─ ");

    // Print current node
    print_node(node);

    // Prepare new prefix (safe version)
    char new_prefix[1024];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "   " : "│  ");

    // Count children
    int child_count = 0;
    if (node->left) child_count++;
    if (node->right) child_count++;

    int index = 0;
    if (node->left)
    {
        index++;
        ft_print_tree(node->left, new_prefix, index == child_count);
    }
    if (node->right)
    {
        index++;
        ft_print_tree(node->right, new_prefix, index == child_count);
    }
}

// Entry function
void print_tree(t_tree *root)
{
    if (!root)
        return;

    ft_print_tree(root, "", 1);
}
