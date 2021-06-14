CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I./libft/incs -I./incs
library = -L./libft -lft -lcurses
LIBFT = libft.a
NAME = minishell

FUNC = main \
	execute_cmd execute_cmd2 execute_cmd3 \
	execute_builtin execute_non_builtin \
	execute_convert_to execute_wait_child \
	parse_env_list execute_non_builtin2 \
	parse_cmd parse_cmd2 handle_error \
	parse_substr_env parse_substr_normal \
	parse_substr_dq parse_substr_sq \
	parse_substr_redirect \
	builtin_cd builtin_echo builtin_env \
	builtin_exit builtin_export_utils \
	builtin_export builtin_pwd builtin_unset \
	handle_termios handle_termcap \
	gnl_for_minishell gnl_for_minishell2 \
	handle_signal handle_history handle_input \
	builtin_export_utils2 \
	builtin_cd_utils

SRC = $(addprefix ./srcs/, $(addsuffix .c, $(FUNC)))
OBJ = $(addprefix ./objs/, $(addsuffix .o, $(FUNC)))

# DUBUG = -fsanitize=address

./objs/%.o : ./srcs/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $?

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(library) $(DUBUG) $(INC) $? -o $@

$(LIBFT) :
	$(MAKE) -C ./libft

clean :
	$(MAKE) -C ./libft clean
	rm -rf $(OBJ)

fclean : clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
