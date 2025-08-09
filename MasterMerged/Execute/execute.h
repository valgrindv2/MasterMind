#ifndef EXECUTE_H
# define EXECUTE_H

# include "../Parsing/minishell.h"
# define RECURS_LIMIT (size_t)500
# define EXECVE_FAILURE 127
# define EXPORTED true
# define NO_VALUE false





// text colors
# define RED "\e[31m"
# define GRN "\e[32m"
# define BLU "\e[34m"
# define YLW "\e[33m"
# define MGN "\e[35m"
# define CYN "\e[36m"
# define RST "\e[97m"


// // ----------------------------------------------------------------------------
// #pragma once
// // Enable/disable failing malloc
// void trigger_malloc_fail_next(const char *file, int line);

// // The actual malloc wrapper
// void *fail_malloc(size_t size, const char *file, int line);

// // Macro to replace malloc() with our controlled version
// #define malloc(size) fail_malloc(size, __FILE__, __LINE__)
// // ----------------------------------------------------------------------------




/*




# include <stdlib.h> // for constants
# include <stdbool.h> // for booleans

// for readline function.
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

#include <unistd.h> // for write

#include <signal.h> // for signal handling.
void    sig_handler(int signum); // signal handlers

typedef struct s_osdata
{
    char    **env;
}   t_osdata;


# define NODE_COMMAND 0
# define NODE_REDIR 1
# define NODE_PIPE 2
# define NODE_OR 3
# define NODE_AND 4
# define NODE_GROUP 5


typedef struct s_cmd
{
    char        **argv; // command arguments, null if anything else
    struct s_cmd *right; // right cmd
    struct s_cmd *left; // left cmd
    t_osdata    *osdata; // pointer to my data struct in main.
}   t_cmd;

// struct for flattened pipes, linear pipeline
typedef struct s_pipe_list
{
    t_cmd               *cmd;
    struct s_pipe_list  *next;
}   t_pipe_list;

// function to execute tree node
void    execute_tree(t_cmd *root, t_osdata *osdata);
int pipe_node(t_cmd *node, t_osdata *osdata);
int exec_colored(char **argv, char **envp);

// recursive executer.
int recursive_execution(t_cmd *node, t_osdata *osdata);

// short - circuit - operand.
int short_circuit_operand(t_cmd *node, t_cmd_id operand_id, t_osdata *osdata);

// subshell and grouping logic for parenthesis.
int subshell_group(t_cmd *node, t_osdata *osdata);


// builtins
bool    validate_builtin(char *str);
int exec_builtin(t_cmd *node, t_osdata *osdata);
void expand_env_variables(t_cmd *node, char **env);
char *get_env_value(char *variable, char **env);

// builtins. (just for testing)
int o_echo(t_cmd *node, t_osdata *osdata);



//--------------------- [  Helpers  ] -----------------------------------------------
// t_cmd *execute_tree(t_cmd *cmd);
t_cmd   *create_tree(char *input); // create the command tree from input
t_cmd   *create_leaf(char *input, t_cmd_id id, t_osdata *osdata); // create a single node, usually root
t_cmd   *add_right(t_cmd **root, char *input, t_cmd_id id);
t_cmd   *add_left(t_cmd **root, char *input, t_cmd_id id);

// parse helpers.
char	**ft_split(char const *s, char c);
void	free_argv(char **av, bool argc_2);
void	print_argv(char *name, char **argv);

// simple tokenizer wrapper built on ft_split, to insure building the tree and returns the head
t_cmd   *o_tokenizer(char *line, t_osdata *osdata);
char **better_split(const char *s);
size_t match_sep(const char *s);

// better split helpers
int	ft_strncmp(const char *s1, const char *s2, size_t n); // my ft_strcmp is flawed fix later.
int	ft_strcmp(char *s1, char *s2);
void	*lst_free(char **lst, size_t j);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);

// tree builder 
t_cmd *build_tree(t_osdata *osdata, char **tokens);
void print_tree(t_cmd *root);
const char *cmd_id_to_str(t_cmd_id id);
//execve helpers.
char    *get_absolute_path(char *cmd);
//--------------------- [^^^ Helpers ^^^] ---------------------------------------------

char	*ft_strjoin(char const *s1, char const *s2);
*/

# endif // EXECUTE_H