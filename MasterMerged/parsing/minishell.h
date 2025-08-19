/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:32:22 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/19 06:28:29 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>

// Macros
# define F 1
# define C 2
# define S 0
# define T 1
# define N 0
# define NL 0
# define SYN 1
# define START 0
# define END 1
# define PWD 1
# define SQ 0
# define DQ 1
# define ENV 0
# define EXP 1
# define INIT 0
# define MARK 0
# define DEMARK 1
# define LAST 0
# define INSIDE 1
# define D_INIT 1
# define OLDPWD 0
# define L_POW 1
# define M_POW 2
# define H_POW 3
# define FAKE "F4K3"
# define SEF_DOC 1
# define HERE_SEF 0
# define SEF_ALL 1
# define ALL_SEF 0
# define HEREDOC1 1
# define REC_LIMIT 400
# define HEREDOC2 2
# define ONE_QUOTE 9
# define EXPAND '$'
# define DUO_QUOTE 10
# define RED_ARG_CLEAN 0
# define CLEAN 1
# define FAIL 0
# define POINT_ONLY 0
# define POINT_N_GET 0
# define ANOMALY -1111
# define EXIT_OVER_LIMIT 2147483650
# define MAX_FLOW 0
# define UNIT_HEREDOC 0
# define UNIT_SPACE_NEXT 1
# define NEW_LINE "newline"
# define BRACE_ERR "MasterMind: Invalid Use Of Braces"
# define QUOTES_ERR "MasterMind: Invalid Use Of Quotes"
# define CL_BEFORE "MasterMind: Closing Brace With No Open"
# define P_W_D "PWD"
# define OLD_PWD "OLDPWD"
# define HOME "HOME"
# define SYNTAX "MasterMind: Syntax Error Near Unexpected Token "

// Operators
# define OR '|'
# define AND '&'
# define PIPE '|'
# define RED_IN '<'
# define RED_OUT '>'
# define RED_APP '>'
# define HERE_DOC '<'
# define WILD_CARD '*'
# define EXPANSION '$'
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define SPACE ' '
# define BRACE_OP '('
# define BRACE_CL ')'
# define N_LINE "\n"
# define MINUS '-'
# define TAB '\t'

// Enum Of IDs
typedef enum grammar
{
	PIPE_ID, // |
	RED_IN_ID, // <
	RED_OUT_ID, // >
	RED_APP_ID, // >>
	HERE_DOC_ID, // <<
	AND_ID, // &&
	OR_ID, // ||
	BRACE_O_ID, // (
	BRACE_C_ID, // )
	S_QUOTE_ID, // ''
	D_QUOTE_ID, // ""
	STRING_ID, // Commands & Arguments
	DEL_ID, // Here_doc Delimiter
	INPUT_FILE_ID, // Input File
	OUTPUT_FILE_ID, // Output File
	INPUT_APP_FILE_ID, // Input Append File
	COMMAND_ID, // Command
	ARG_ID, // Argument
}	t_grammar;

// Redirections Files List
typedef struct s_red
{
	char			*value;
	t_grammar		tok;
	int				fd_here_doc;
	int				was_s_quote;
	int				was_d_quote;
	struct s_red	*next;
}	t_red;

// Commands Arguments List
typedef struct s_arg
{
	char			*value;
	t_grammar		tok;
	int				was_s_quote;
	int				was_d_quote;
	bool			space_next;
	struct s_arg	*next;
}	t_arg;

// Preparsing List For Braces
typedef struct s_brace
{
	char			*value;
	struct s_brace	*next;
}	t_brace;

// MasterMindTree
typedef struct s_tree
{
	char			*value;
	char			**argv;
	t_grammar		tok;
	int				op_case;
	int				here_doc_fd;
	int				was_s_quote;
	int				was_d_quote;
	bool			fake;
	struct s_red	*red;
	struct s_arg	*arg;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// Linked List Holding The Enviroment
typedef struct s_envlist
{
	char				*value;
	bool				pointed;
	char				*variable;
	bool				exported;
	struct s_envlist	*next;
}	t_envlist;

// Linked List Holding The ExportList
typedef struct s_exportlist
{
	char				*value;
	bool				pointed;
	char				*variable;
	struct s_exportlist	*next;
}	t_exportlist;

// pocket insertion struct.
typedef struct s_pocket
{
	int		i;
	int		j;
	int		keylen;
	char	*value;
	size_t	cap;
}	t_pocket;

// garbage collector
typedef struct s_mind_alloc
{
	void				*ptr;
	bool				free_at_end;
	struct s_mind_alloc	*next;
}	t_mind_alloc;

// Expand Helper Struct
typedef struct s_udouble
{
	int		i;
	int		j;
	char	**new_pocket;
	int		mc_argc;
	char	**split;
}	t_udouble;

// Struct Holding MasterMind Data
typedef struct s_data
{
	int				to_exp;
	int				to_env;
	int				append;
	int				here_fd;
	int				is_child;
	int				here_case;
	int				here_minus;
	int				exit_status;
	int				fail;
	int				i;
	t_exportlist	*exp;
	t_envlist		*env;
	char			**env_vec;
	bool			check;
	bool			unreach;
	bool			chpwd;
	bool			no_sef;
	int				ch_fail;
	int				br_fail;
	int				flag;
	bool			read_f;
	char			*home_p;
	char			*pwd_reserve;
	bool			unset_status;
	bool			export_status;
	int				here_read_fd;
	struct termios	saved_state;
	int				saved_in;
	int				saved_out;
	bool			env_is_set;
	int				pid;
	t_pocket		pc;
	t_tree			*head;
	char			*last_executed;
	int				anon_start;
	char			**pockets;
	bool			child_state;
	bool			piped;
}	t_data;

// Linked List To Store Each Entity
// Where Each Entity With its Id
typedef struct s_token
{
	int				op;
	int				br;
	bool			end;
	int				power;
	bool			used;
	int				firsts;
	int				brace_c;
	int				brace_o;
	int				op_case;
	bool			marked;
	bool			in_acc;
	bool			al_used;
	int				here_done;
	int				here_times;
	bool			space_next;
	int				here_doc_fd;
	int				was_single_quote;
	int				was_double_quote;
	int				quotes_syntax;
	bool			here_document_act;
	bool			del_fd;
	bool			fake;
	bool			cmd_up_next;
	bool			cmd_added;
	bool			alre_doc;
	struct s_token	*next;
	enum grammar	tok;
	char			*identity;
	t_red			*red;
	t_arg			*arg;
}	t_token;

typedef struct s_ff
{
	struct dirent	*entry;
	char			**files;
	int				i;
	DIR				*dir;
}	t_ff;

// Signal Tools
void				sig_handler(int signum);
void				sig_heredoc(int signum);
void				sig_kill(int signum);

// Debbugers
void				linkednev_db(t_envlist **env);
void				debbuger_tk(t_token *id_class);

// Initialization
void				init_data_struct(t_data *data, char **env);
void				voiders(int argc, char **argv, char **env);

// Environement List Tools
char				*copy_var(char *value_case);
t_envlist			*get_last_node(t_envlist *env);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char const *s, char c);
char				*cpy_variable(char *var_place, char *variable);
t_envlist			*add_variable_value(char *variable, char *value);
void				add_to_env(t_envlist **env, t_envlist *variable);

// Identity Tools
int					get_len(char *str);
void				puterror(char *str);
int					whitespaces(char x);
int					all_whitespaces(char x);
void				init_tool(t_token *new);
t_token				*ft_lstlast(t_token *lst);
int					set_ops(t_token *id_class);
void				ft_bzero(void *s, size_t n);
int					check_alpha(char x, char x2);
int					check_doubles(char x, char x2);
void				cpy_identity(char *dst, char *src);
int					len_of_string(char *input, int index);
t_token				*get_identity(char *input, t_data *data);
void				re_init_tool(t_token *new, t_token *old);
int					ft_strnstr(char *haystack, char *needle, size_t len);
void				add_back_identity(t_token **lst, t_token *new, int mode);
void				unit_call_space_next(t_token *id_class,
						char *input, int *index);
int					unit_call_here_doc(t_token **id_class,
						char *input, t_data *data);
t_token				*add_identity(char *content, enum grammar tok,
						int mode, t_token *infos);
int					identity_scraping(char *ident, enum grammar en,
						t_token *id, t_token **id_class);

// Identity Scrapers
char				*scrap(int *index, char *scrapped);
char				*scrap_string(char *input, int *index);
char				*scrap_braces(char *input, int *index, char *brace);
int					len_of_quote(char *input, char quote_case, int index);
char				*scrap_quote(char *input, t_data *dt, int quote_case);

// Units of Tokening
int					first_unit(char *input, int *i,
						t_token *id, t_token **id_class);
int					sec_unit(char *input, int *index,
						t_token *id, t_token **id_class);
int					third_unit(char *input, int *index,
						t_token *id, t_token **id_class);
int					forth_unit(char *input, t_data *dt,
						t_token *id, t_token **id_class);

// Builtins
void				export(t_data *data, char **args, int len);

// Tools Of Builtins
long				ft_atol(const char *str);
char				*ft_strdup(const char *s1);
int					ft_strcmp(char *s1, char *s2);
int					ft_strchr(const char *s, int c);
char				*ft_strtrim(char *s1, char *set);
int					ft_strncmp(char *s1, char *s2, int n);
char				*ft_substr(char *s, int start, int len);
bool				check_identifier(char *str, int i);

// Syntax Verification
void				puterror(char *str);
void				pop_out_brace(t_token **token);
t_token				*get_all_braces(t_token *token);
int					scan_for_doubles(t_token *token);
int					edge_braces(char *input, t_data *data);
int					doubles_verify(t_token *token, t_data *data);
int					operations_braces(char *braces, t_data *data);
int					push_br(t_token **stack_br, t_token *to_push);
void				print_error(char *error, char *err, int mode);
void				syntax_error_found(t_token *curr, t_data *data);
void				clean_stacks(t_token **stackone, t_token **stacktwo);
int					syntax_verify(t_token *token, t_data *data);
int					realt_quotes(char *input, int doubles_case,
						int index, char *err);

// Here_Document Tools
char				*ft_itoa(int n);
void				set_free(t_token *curr);
int					list_size(t_token *list);
int					takeoff_quotes(t_token *tok);
void				space_flag(t_token *id_class);
char				*get_delimiter(t_token *token);
int					get_here_times(t_token *id_class);
void				cpy_to_file(char *in, t_data *data);
void				get_quotes_state(t_token *delimiter);
int					store_fd(t_token *id_class, t_data *data);
int					change_id(t_token *next_heredoc, t_data *data);
int					sef_doc(t_token *token, t_data *data);
int					here_doc_check(t_token *id_class, t_data *data);
int					delimiter_next(t_token *next_heredoc, t_data *data);
int					hold_and_check(t_token *hold, t_token *curr);
int					here_doc_ops(t_token *id_class, t_data *data, char *del);
int					requirements(t_token *curr, t_token *id_class,
						t_data *data);

// Re_Identification Of Tokens
void				init_properties(t_token *new);
t_token				*re_builder(t_token *id_class);
int					fake_system(t_token *id_class);
t_token				*re_identity(t_token *id_class);
void				cmd_arg(t_token **curr, int *string);
void				identify_argument(t_token **id_class);
void				re_identifications(t_token *curr);

// MasterMind System
int					red_checks(t_token *curr);
t_arg				*new_argument(t_token *new);
void				set_end(t_token **op_field);
t_token				*get_file(t_token *id_class);
void				set_power(t_token *id_class, t_data *data);
t_token				*return_op(t_token *op_field);
int					arg_system(t_token *id_class);
int					red_system(t_token **id_class);
t_tree				*build_tree(t_token *id_class, t_data *data);
t_token				*delete_red(t_token **id_class);
t_arg				*last_arg_node(t_arg *arg_list);
void				set_last_cmd(t_token *id_class);
void				mark_unmarked(t_token *id_class);
void				command_ahead(t_token *id_class);
void				add_back_red(t_red **cmd, t_red *in);
int					add_token(t_token *curr, t_token **yard);
t_token				*shunting_yard_algorithm(t_token *id_class, t_data *data);
int					recursive_build(t_token *yard,
						t_tree **tree);
void				add_arg_to_list(t_arg **arg_list,
						t_arg *arg);
t_red				*redirection_cop(t_token *id_class,
						int *fail);
int					mark_ending(t_token *op_field,
						t_token **yard);
void				add_front_identity(t_token **lst,
						t_token *new);
void				check_set_cmd(t_token **curr,
						t_token **id_class);
void				check_delete(t_token **curr,
						t_token **id_class);
int					add_all_to_yard(t_token **yard,
						t_token **op_field);
void				last_cmd(t_token *curr, int *x, int *y,
						t_token **cmd);
int					remove_op(t_token **yard, t_token **op_field,
						t_token *op);
int					algo(t_token *curr, t_token **op_field,
						t_token *in, t_token **yard);
int					add_op(t_token *curr, t_token **op_field,
						t_token **yard, t_token *in);
int					add_n_remove(t_token *curr, t_token **op_field,
						t_token **yard, t_token *in);
int					algorithm_options(t_token *curr, t_token **op_field,
						t_token **yard, t_token *in);

// Cleaners Functions
void				clean_node(t_token *in);
void				cleaner_red(t_token *list);
void				cleaner_arg(t_token *list);
void				clean_fd(t_token *id_class);
void				list_cleaner(t_token **list);
void				panic(t_data *data, char *input);
void				clean_yard(t_token **yard, int mode);
void				clean_id_class(t_token **id_class, int mode);
void				tree_cleaner(t_tree **node);
void				freeiers(t_data *data, char *input);

// ouss functions  ---------------------

typedef struct s_path
{
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i;
}	t_path;

typedef struct s_plist
{
	t_tree			*cmd_node;
	struct s_plist	*next;
}	t_plist;

typedef struct s_pipe_info
{
	int		prev_fd;
	int		fds[2];
	int		is_pipe;
}	t_pipe_info;

typedef struct s_pp
{
	t_plist		*plist;
	t_plist		*curr;
	pid_t		last_pid;
	int			ret;
	int			fds[2];
	t_pipe_info	info;
}	t_pp;

typedef struct s_ifs
{
	char			*string;
	struct s_ifs	*next;
}	t_ifs;

typedef struct s_ifs_vars
{
	char	**ifs_split;
	char	**new_argv;
	t_ifs	*ifs_list;
	int		i;
	int		j;
	char	*string;
}	t_ifs_vars;

typedef struct s_convert
{
	char		**argv;
	char		**new_argv;
	size_t		argc;
	int			i;
	t_arg		*free_head;
}	t_convert;

// Restore Terminal Attributes
int					get_current_state(int fd, t_data *data);
int					restore_previous_state(int fd, t_data *data);

// Main Exec Functionality.
int					exec_node(t_tree *node, t_data *data);
int					merger(t_tree *root, t_data *data, char **env);
int					recursive_execution(t_tree *node, t_data *data);
int					execute_pipeline(t_tree *node, t_data *data, int input_fd);
int					execute_tree(t_tree *root, t_data *data,
						char **env, void *re_built);
int					short_circuit_operand(t_tree *node,
						t_grammar operand_id, t_data *data);
int					wait_for_last_pid(pid_t last_pid);
pid_t				fork_pipeline_node(t_plist *node, t_data *data,
						t_pipe_info *info);
void				flatten_pipeline(t_tree *node, t_plist **head);
void				pipe_sighandle(void);
void				start_signals(void);
int					print_exec_error(char *cmd, int code);
int					errors_msgs(int err);
int					is_it_dir(char *cmd);

// Builtins
size_t				arg_count(char **argv);
int					o_echo(t_tree *node);
void				delete(t_envlist *node);
bool				validate_builtin(char *str);
bool				valid_identifier(char *str);
bool				valid_identifier_un(char *str);
int					o_cd(t_tree *node, t_data *data);
int					o_pwd(t_tree *node, t_data *data);
int					o_env(t_tree *node, t_data *data);
int					o_exit(t_tree *node, t_data *data);
int					o_unset(t_tree *node, t_data *data);
int					o_export(t_tree *node, t_data *data);
int					exec_builtin(t_tree *node, t_data *data);
char				*reserve_tool(char *pwd, t_data *data, int two, int one);

// Export
int					add_last_executed(t_tree *node, t_data *data);
char				*get_key(char *str);
char				*get_value(char *str);
int					add_to_export_list(t_envlist **export_lst, t_envlist *env);
void				free_exp_list(t_envlist *exp_list);
int					process_export_arg(char *arg, t_data *data);
bool				valid_identifier(char *str);
bool				valid_identifier_core(char *str, int *i, bool *standalone);
bool				has_equal(char *str);
bool				has_plus(char *str);
int					process_existing_var(char *arg, t_data *data);
int					process_new_var(char *arg, t_data *data);
int					assign_new_value(char *new_var, t_envlist *env);
int					append_value(char *new_var, t_envlist *env);

// Expanding enrty functions.
int					expand_list(t_arg *arg, t_data *data);
char				*expand_var(char *str, t_data *data, bool was_d_quoted);
char				**convert_list_to_argv(t_arg *arg, t_data *data);
int					pocket_insertion(char **pockets, char *str,
						t_data *data, bool was_d_quoted);

// Expansion Utils.
char				*expand_key_wrapper(char *str, t_data *data);
char				*standalone(int *i);
char				*normal_text(char *str, int *i);
char				*expand_key(char *str, t_data *data, int keylen, int *i);
char				*join_system(t_arg **p_arg);
char				*pocket_joiner(char **pockets);
char				*o_ft_itoa(int n);
size_t				o_ft_strlen(char *s);
bool				has_space(char *str);
bool				has_equal(char *str);
bool				has_delim(char *str);
char				**ifs_pass(char **argv);
void				fail_procedure(char **pockets, t_data *data);
bool				ft_isalnum(int c);
char				*expand_special_cases(char *str, t_data *data, int *i);
int					add_ifs_back(t_ifs **head, char *str);
void				free_ifs_list(t_ifs *ifs);
char				**ifs_list_to_argv(t_ifs *head);
size_t				ifs_list_size(t_ifs *curr);
int					should_join(char *curr, char *next);
int					is_alphanum_underscore(char c);

// Anon system.
bool				anon(t_tree *node, size_t argc);
bool				still_has_anon(char *str);
char				**terminate_inside_anons(char **argv);
bool				single_anon(char *str);

// Wildcard
int					try_expand_wildcard(t_arg *arg);
void				sort_files(char **files);
int					count_files(void);
char				**alloc_files(int count);
int					init_asterisk(t_ff *ff, int count);

// garbage collector.

void				*allocate_gc(void *ptr);
void				mind_free_all(bool panic);
int					add_to_gc(void *new_address);
t_mind_alloc		**get_head(void);
void				tree_gc_collector(t_tree *node);
void				*allocate_gc_no_exit(void *ptr);
int					add_to_gc_no_ex(void *new_address);
int					pipe_child_free(int ret);
void				*env_allocate_gc(void *ptr);
char				*env_get_key(char *str);
char				*env_get_value(char *str);

// Linked env
size_t				o_ft_strlen(char *str);
size_t				envlist_size(t_envlist *env);
char				*convert_node_to_str(t_envlist *env_node);
char				**convert_list_to_envp(t_envlist *envlist, t_data *data);
int					add_to_envlist(t_envlist **envlist,
						char *str, bool exported);

// Redirections 
int					handle_red(t_tree *node, t_data *data);
void				restore_io(int saved_in, int saved_out, bool no_red);
char				*red_ifs_pass(char *str);
bool				only_spaces(char *raw);
int					red_here_doc(t_red *red, t_data *data);
int					red_in(t_red *red, t_data *data);
int					red_out(t_red *red, t_data *data);
int					red_append(t_red *red, t_data *data);
bool				check_expanded_malloc(char **expanded, t_data *data,
						t_red *curr_red);
char				*expand_heredoc(char *joined, t_red *red, t_data *data);
bool				has_ifs(char *str);
bool				expandable_check(char *str);
bool				has_ambig_space(char *str);

// Free_tree (error handling)
void				free_argv(char **argv);
void				clean_up(t_tree *tree, t_data *data);
void				free_envlist(t_envlist *env);
void				*mind_allocater(size_t size, t_mind_alloc **head);
void				Mind_free(t_mind_alloc *head);

int					expand_unqoted_d(char ***pockets, t_data *data, char *raw);
char				*append_delimiter(char *str);

char				*strjoiner(char **list, char *sep, size_t size);

void				normalize_command(char *str);
void				print_argv(char **argv);

int					merge_env(t_data *data, char **env); // why here
char				**tab_split(char *s, char *sep);
char				**remove_nonprintables_argv(char **argv);

// Builtins Tools
int					con_check(t_tree *node);
int					dir_verify(DIR *dir, char **arg);
bool				check_identifier(char *str, int i);
char				*get_path(t_envlist *env, char *name);
int					update_old(t_tree *node, t_data *data);
int					get_last_slash(char *pwd, int constant);
char				*handle_no_arg(t_tree *node, t_data *data);
int					change_unsetted(t_envlist *env, char *update);
int					change_pwd_old(char *name, t_envlist *env,
						char *update, int *chpwd);
int					reserve_pwd(t_tree *node, t_data *data,
						int one, int two);
void				check_dots(t_tree *node, int *one_dot,
						int *two_dot);
int					change_pwd(char *name, t_envlist *env,
						char *update);
void				init_cd_tools(t_tree *node, t_data *data,
						int *chpwd);

// ----------------------------------------------------------------------------
#endif