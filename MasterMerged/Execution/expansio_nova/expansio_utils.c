#include "../../Parse/minishell.h"

typedef struct s_expand_node
{
    char                *content;
    struct s_expand_node *next;
} t_expand_node;

static t_expand_node *create_node(char *content)
{
    t_expand_node *node = allocate_gc(malloc(sizeof(t_expand_node)));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

static void add_node_back(t_expand_node **head, t_expand_node *new_node)
{
    t_expand_node *current;

    if (!head || !new_node)
        return;
    
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

static char *list_to_string(t_expand_node *head)
{
    t_expand_node *current;
    char *result;
    int i;
    int j;

    i = 0;
    current = head;
    while (current != NULL)
    {
        j = 0;
        while (current->content[j] != '\0')
        {
            i++;
            j++;
        }
        current = current->next;
    }
    result = allocate_gc(malloc(i + 1));
    if (!result)
        return (NULL);
    i = 0;
    current = head;
    while (current != NULL)
    {
        j = 0;
        while (current->content[j] != '\0')
        {
            result[i] = current->content[j];
            i++;
            j++;
        }
        current = current->next;
    }
    result[i] = '\0';

    return (result);
}

static char *get_var_value(char *var_name, t_data *data)
{
    char *value;

    if (var_name == NULL)
        return (allocate_gc(ft_strdup("")));

    if (ft_strcmp(var_name, "?") == 0)
        return (allocate_gc(ft_itoa(data->exit_status)));
    if (ft_strcmp(var_name, "$") == 0)
        return (allocate_gc(ft_itoa(data->pid)));
    
    value = find_in_env(data->env, var_name);
    if (value == NULL)
        return (allocate_gc(ft_strdup("")));
    return (allocate_gc(ft_strdup(value)));
}

char *expand_double_quoted(char *str, t_data *data)
{
    t_expand_node   *head;
    int             i;
    char            *var_value;
    char            *char_str;
    int             start;

    head = NULL;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\t')
        {
            i++;
            if (str[i] == '?')
            {
                var_value = get_var_value("?", data);
                add_node_back(&head, create_node(var_value));
                i++;
            }
            else if (str[i] == '$') // $$
            {
                var_value = get_var_value("$", data);
                add_node_back(&head, create_node(var_value));
                i++;
            }
            else
            {
                start = i;
                while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
                    i++;
                var_value = get_var_value(ft_substr(str, start, i - start), data);
                if (var_value != NULL)
                    add_node_back(&head, create_node(var_value));
            }
        }
        else
        {
            char_str = ft_substr(str, i, 1);
            add_node_back(&head, create_node(char_str));
            i++;
        }
    }

    return (list_to_string(head));
}
