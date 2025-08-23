CC = cc 
SANITIZE= -fsanitize=address -g3
CFLAG = -I$(READLINE_DIR)/include -Wall -Wextra -Werror
READLINE_DIR := lib/readline/install
LDFLAGS += -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses
H = Parse/minishell.h 
NAME = minishell
SRC = Parse/minishell.c Parse/identificators/identity_tools/identool0.c\
		Parse/identificators/identify.c Parse/identificators/identity_tools/identool1.c \
		Parse/tools/tool.c\
		Parse/tools/tool2.c Parse/identificators/units.c \
		Parse/signal_handlers/sig_handlers.c\
		Parse/signal_handlers/restore_state.c\
		Parse/tools/tools3.c Parse/tools/tools4.c Parse/tools/tools5.c\
		Parse/tools/tools6.c \
		Parse/tools/tools7.c \
		Parse/syntax/syntax.c Parse/syntax/syntax2.c Parse/syntax/syntax3.c\
		Parse/syntax/syntax4.c Parse/syntax/syntax5.c\
		Parse/identificators/identity_tools/identool2.c\
		Parse/identificators/identity_tools/identool3.c\
		Parse/identificators/identity_tools/identool4.c\
		Parse/tools/tools8.c Parse/identificators/identity_tools/identool5.c\
		Parse/identificators/identity_tools/identool6.c\
		Parse/tools/tools9.c Parse/identificators/identity_tools/identool7.c\
		Parse/identificators/identity_tools/identool8.c\
		Parse/identificators/identity_tools/identool9.c\
		Parse/re_identificators/re_identity.c Parse/re_identificators/re_identity_tools/re_identool0.c\
		Parse/re_identificators/re_identity_tools/re_identool1.c\
		Parse/re_identificators/re_identity_tools/re_identool2.c\
		Parse/re_identificators/re_identity_tools/re_identool3.c\
		Parse/re_identificators/re_identity_tools/re_identool4.c\
		Parse/re_identificators/re_identity_tools/re_identool5.c\
		Parse/re_identificators/re_identity_tools/re_identool6.c\
		Parse/re_identificators/re_identity_tools/re_identool7.c\
		Parse/mastermind/system_mind0.c Parse/mastermind/system_mind1.c\
		Parse/mastermind/mind_tools/mind_tools1.c\
		Parse/mastermind/mind_tools/mind_tools2.c Parse/mastermind/mind_tools/mind_tools3.c \
		Parse/tools/tools10.c Parse/tools/tools11.c\
		\
		\
	 	Execution/o_builtins/unset_tools/unsett.c\
	 	Execution/o_builtins/cd_tools/cd1.c \
	 	Execution/o_builtins/cd_tools/cd2.c \
	 	Execution/o_builtins/cd_tools/cd3.c \
	 	Execution/tree_executers/execute_tree.c 	Execution/tree_executers/merge_utils/merge_utils.c \
	 	Execution/tree_pipeline/tree_pipeline.c 	Execution/tree_executers/free_tree.c \
	 	Execution/tree_executers/shortcircuit.c 	Execution/tree_executers/handle_red.c \
	 	Execution/o_builtins/o_bultins.c 	Execution/o_builtins/o_echo.c \
	 	Execution/o_builtins/o_cd.c 	Execution/o_builtins/o_env.c \
	 	Execution/o_builtins/o_exit.c 	Execution/o_builtins/export_tools/o_export.c \
	 	Execution/o_builtins/export_tools/export_list_utils.c \
	 	Execution/o_builtins/export_tools/process_export_arg.c \
	 	Execution/o_builtins/export_tools/valid_identifier_core.c \
	 	Execution/o_builtins/export_tools/valid_identifier.c \
	 	Execution/o_builtins/o_pwd.c 	Execution/o_builtins/o_unset.c \
	 	Execution/tree_executers/merge_utils/merge_env.c \
	 	Execution/tree_executers/merge_utils/merge_env_utils.c \
	 	Execution/o_builtins/builtin_utils.c 					\
	 	Execution/expansion/expand_arglist.c 	Execution/expansion/expand_key.c 		\
	 	Execution/expansion/join_system.c 	Execution/expansion/merge_arglist.c 		\
	 	Execution/expansion/pocket_expantion.c 	Execution/expansion/pocket_insertion.c \
	 	Execution/expansion/expansion_utils.c 	Execution/tree_executers/last_exec.c 	\
	 	Execution/expansion/split_ifs.c 												\
	 	Execution/expansion/internal_field_seperator_pass.c 							\
	 	Execution/expansion/pocket_insertion_utils.c 	Execution/anon_system/anon.c		\
	 	Execution/anon_system/anon_terminator.c 	Execution/expansion/strjoiner.c \
	 	Execution/o_builtins/export_tools/process_export_arg_utils.c \
	 	Execution/tree_executers/exec_node.c 	Execution/expansion/wildcard_expansion.c \
	 	Execution/expansion/wildcard_utils.c 	Execution/tree_executers/gnl.c \
	 	Execution/tree_executers/gnl_utils.c 	Execution/tree_executers/tab_split.c \
	 	Execution/anon_system/remove_anon.c 	Execution/tree_pipeline/pipeline_utils.c \
	 	Execution/tree_pipeline/pipehandlers.c 	Execution/expansion/internal_field_utils.c \
	 	Execution/expansion/split_ifs_utils.c 	Execution/mind_allocater/mind_allocater.c \
	 	Execution/tree_executers/errors_msgs.c 	Execution/mind_allocater/get_tree_adrs.c \
	 	Execution/tree_executers/handle_red_fds.c 	Execution/tree_executers/handle_red_utils.c \
	 	Execution/mind_allocater/mind_allocater_utils.c 	Execution/o_builtins/unset_tools/unsett2.c \
		Execution/mind_allocater/gc_env_vec.c Execution/tree_executers/data_io_clean.c \

		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAG) $(SANITIZE) $(LDFLAGS) -lreadline -o $(NAME)

%.o: %.c $(H)
	$(CC) $(CFLAG) $(SANITIZE) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all     
