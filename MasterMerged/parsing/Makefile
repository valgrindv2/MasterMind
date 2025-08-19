CC = cc 
SANITIZE= -fsanitize=address -g3
CFLAG = -I$(READLINE_DIR)/include -Wall -Wextra -Werror # zdt readline library (MAC) -Wall -Wextra -Werror
READLINE_DIR := ../lib/readline/install
LDFLAGS += -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses
H = minishell.h 
NAME = minishell
SRC = minishell.c identificators/identity_tools/identool0.c\
		identificators/identify.c identificators/identity_tools/identool1.c \
		tools/tool.c\
		tools/tool2.c identificators/units.c \
		signal_handlers/sig_handlers.c\
		signal_handlers/restore_state.c\
		tools/tools3.c tools/tools4.c tools/tools5.c\
		tools/tools6.c \
		tools/tools7.c \
		syntax/syntax.c syntax/syntax2.c syntax/syntax3.c\
		syntax/syntax4.c syntax/syntax5.c\
		identificators/identity_tools/identool2.c\
		identificators/identity_tools/identool3.c\
		identificators/identity_tools/identool4.c\
		tools/tools8.c identificators/identity_tools/identool5.c\
		identificators/identity_tools/identool6.c\
		tools/tools9.c identificators/identity_tools/identool7.c\
		identificators/identity_tools/identool8.c\
		identificators/identity_tools/identool9.c\
		re_identificators/re_identity.c re_identificators/re_identity_tools/re_identool0.c\
		re_identificators/re_identity_tools/re_identool1.c\
		re_identificators/re_identity_tools/re_identool2.c\
		re_identificators/re_identity_tools/re_identool3.c\
		re_identificators/re_identity_tools/re_identool4.c\
		re_identificators/re_identity_tools/re_identool5.c\
		re_identificators/re_identity_tools/re_identool6.c\
		re_identificators/re_identity_tools/re_identool7.c\
		mastermind/system_mind0.c mastermind/system_mind1.c\
		mastermind/mind_tools/mind_tools1.c\
		mastermind/mind_tools/mind_tools2.c mastermind/mind_tools/mind_tools3.c \
		tools/tools10.c tools/tools11.c\
		\
		\
		../execute/o_builtins/unset_tools/unsett.c\
		../execute/o_builtins/cd_tools/cd1.c \
		../execute/o_builtins/cd_tools/cd2.c \
		../execute/o_builtins/cd_tools/cd3.c \
		../execute/tree_executers/execute_tree.c ../execute/tree_executers/merge_utils/merge_utils.c \
		../execute/tree_pipeline/tree_pipeline.c ../execute/tree_executers/free_tree.c \
		../execute/tree_executers/shortcircuit.c ../execute/tree_executers/handle_red.c \
		../execute/o_builtins/o_bultins.c ../execute/o_builtins/o_echo.c \
		../execute/o_builtins/o_cd.c ../execute/o_builtins/o_env.c \
		../execute/o_builtins/o_exit.c ../execute/o_builtins/export_tools/o_export.c \
		../execute/o_builtins/export_tools/export_list_utils.c \
		../execute/o_builtins/export_tools/process_export_arg.c \
		../execute/o_builtins/export_tools/valid_identifier_core.c \
		../execute/o_builtins/export_tools/valid_identifier.c \
		../execute/o_builtins/o_pwd.c ../execute/o_builtins/o_unset.c \
		../execute/tree_executers/merge_utils/merge_env.c \
		../execute/tree_executers/merge_utils/merge_env_utils.c \
		../execute/o_builtins/builtin_utils.c 					\
		../execute/expansion/expand_arglist.c ../execute/expansion/expand_key.c 		\
		../execute/expansion/join_system.c ../execute/expansion/merge_arglist.c 		\
		../execute/expansion/pocket_expantion.c ../execute/expansion/pocket_insertion.c \
		../execute/expansion/expansion_utils.c ../execute/tree_executers/last_exec.c 	\
		../execute/expansion/split_ifs.c 												\
		../execute/expansion/internal_field_seperator_pass.c 							\
		../execute/expansion/pocket_insertion_utils.c ../execute/anon_system/anon.c		\
		../execute/anon_system/anon_terminator.c ../execute/expansion/strjoiner.c \
		../execute/o_builtins/export_tools/process_export_arg_utils.c \
		../execute/tree_executers/exec_node.c ../execute/expansion/wildcard_expansion.c \
		../execute/expansion/wildcard_utils.c ../execute/tree_executers/gnl.c \
		../execute/tree_executers/gnl_utils.c ../execute/tree_executers/tab_split.c \
		../execute/anon_system/remove_anon.c ../execute/tree_pipeline/pipeline_utils.c \
		../execute/tree_pipeline/pipehandlers.c ../execute/expansion/internal_field_utils.c \
		../execute/expansion/split_ifs_utils.c ../execute/mind_allocater/mind_allocater.c \
		../execute/tree_executers/errors_msgs.c ../execute/mind_allocater/get_tree_adrs.c \
		../execute/tree_executers/handle_red_fds.c ../execute/tree_executers/handle_red_utils.c \
		../execute/mind_allocater/mind_allocater_utils.c ../execute/o_builtins/unset_tools/unsett2.c \
		

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAG) $(SANITIZE) $(LDFLAGS) -lreadline -o $(NAME)

%.o: %.c $(H)
	@$(CC) $(CFLAG) $(SANITIZE) -c $< -o $@

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all     
