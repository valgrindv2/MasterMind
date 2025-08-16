CC = cc 
SANITIZE= -fsanitize=address -g3
CFLAG = -I$(READLINE_DIR)/include #-Wall -Wextra -Werror # zdt readline library (MAC) -Wall -Wextra -Werror
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
		../Execute/o_builtins/unset_tools/unsett.c\
		../Execute/o_builtins/cd_tools/cd1.c \
		../Execute/o_builtins/cd_tools/cd2.c \
		../Execute/o_builtins/cd_tools/cd3.c \
		../Execute/tree_executers/execute_tree.c ../Execute/tree_executers/merge_utils/merge_utils.c \
		../Execute/tree_pipeline/tree_pipeline.c ../Execute/tree_executers/free_tree.c \
		../Execute/tree_executers/shortcircuit.c ../Execute/tree_executers/handle_red.c \
		../Execute/o_builtins/o_bultins.c ../Execute/o_builtins/o_echo.c \
		../Execute/o_builtins/o_cd.c ../Execute/o_builtins/o_env.c \
		../Execute/o_builtins/o_exit.c ../Execute/o_builtins/export_tools/o_export.c \
		../Execute/o_builtins/export_tools/export_list_utils.c \
		../Execute/o_builtins/export_tools/process_export_arg.c \
		../Execute/o_builtins/export_tools/valid_identifier_core.c \
		../Execute/o_builtins/export_tools/valid_identifier.c \
		../Execute/o_builtins/o_pwd.c ../Execute/o_builtins/o_unset.c \
		../Execute/tree_executers/merge_utils/merge_env.c \
		../Execute/tree_executers/merge_utils/merge_env_utils.c \
		../Execute/fail_malloc.c ../Execute/o_builtins/builtin_utils.c 					\
		../Execute/Expansion/expand_arglist.c ../Execute/Expansion/expand_key.c 		\
		../Execute/Expansion/join_system.c ../Execute/Expansion/merge_arglist.c 		\
		../Execute/Expansion/pocket_expantion.c ../Execute/Expansion/pocket_insertion.c \
		../Execute/Expansion/expansion_utils.c ../Execute/tree_executers/last_exec.c 	\
		../Execute/Expansion/split_ifs.c 												\
		../Execute/Expansion/internal_field_seperator_pass.c 							\
		../Execute/Expansion/pocket_insertion_utils.c ../Execute/anon_system/anon.c		\
		../Execute/anon_system/anon_terminator.c ../Execute/Expansion/strjoiner.c \
		../Execute/o_builtins/export_tools/process_export_arg_utils.c \
		../Execute/tree_executers/merge_utils/exec_node.c ../Execute/Expansion/wildcard_expansion.c \
		../Execute/Expansion/wildcard_utils.c

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
