CC = cc
READLINE_DIR := ../lib/readline/install
LDFLAGS += -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses

CFLAG = -I$(READLINE_DIR)/include # zdt readline library (MAC) #-Wall -Wextra -Werror 
HEADER = execute.h 
NAME = execute
SRC = main.c tree_executers/execute_tree.c tree_executers/shortcircuit.c \
		tree_executers/subshell.c o_builtins/o_bultins.c o_builtins/o_echo.c \
		o_builtins/env_utils.c o_builtins/o_expand.c tree_executers/exec_color.c \
		tree_pipeline/tree_pipeline.c tree_builders/parse_helpers.c tree_builders/create_tree.c \
		tree_builders/better_split.c tree_builders/build_tree.c \
		tree_builders/print_tree.c

GRN=\033[0;32m
RED=\033[0;31m
BLU=\033[0;34m
END=\033[0m

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(RED) _, _  _,  _, ___ __, __,   _, _ _ _, _ __,"
	@echo " |\/| /_\ (_   |  |_  |_)   |\/| | |\ | | \\"
	@echo " |  | | | , )  |  |   | \   |  | | | \| |_/"
	@echo " ~  ~ ~ ~  ~   ~  ~~~ ~ ~   ~  ~ ~ ~  ~ ~  $(END)"
	@$(CC) $(OBJ) $(CFLAG) $(LDFLAGS) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all     