NAME		:=  minishell

COMP		:= 	cc
CFLAGS		:= 	-Wall -Wextra -Werror -fsanitize=address -g

SRC			:=	main.c ft_exec_cmd_line.c \
				ft_create_token_list.c ft_set_word_token.c \
				ft_set_operator_token.c ft_set_token_value.c \
				ft_token_quote.c ft_token_type_bool.c \
				ft_set_wildcard_for_cmd_list.c \
				ft_set_wildcard_for_cmd_list_2.c ft_set_wildcard_for_cmd_list_3.c\
				ft_update_wildcard_bool_list.c ft_set_wildcard_name_path.c\
				ft_update_path_before.c ft_get_wildcard_value.c ft_wildcard_cmp.c \
				ft_unclosed_command_line.c ft_token_parenthesis.c \
				ft_create_cmd_list.c ft_set_cmd.c ft_set_cmd_utils.c \
				ft_create_cmd_tree.c ft_exec_cmd_tree.c ft_launch_exec.c\
				ft_launch_builtout.c ft_open_redirection.c ft_redirection_here_doc.c \
				ft_exec.c ft_exit_child.c ft_token_free.c ft_cmd_free.c \
				ft_exec_builtin.c ft_sighandle.c

BUILTIN		:= cd.c echo.c env.c exit.c export.c pwd.c unset.c

ENV			:= env_init.c env_utils.c error.c free.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
BUILTINS	:= $(addprefix ./srcs/builtins/, $(BUILTIN))
ENVS		:= $(addprefix ./srcs/env/, $(ENV))
OBJ 		:= $(SRCS:.c=.o) $(BUILTINS:.c=.o) $(ENVS:.c=.o)
INC			:= minishell.h
INCS		:= $(addprefix ./includes/, $(INC))

LIBNAME = libft/libft.a
LIBPATH = libft/

READLINE = -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
# -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
# -lreadline -L ~/homebrew/opt/readline/lib -I ~/homebrew/opt/readline/include

all: $(NAME)

bonus: $(NAME_bonus)

$(NAME): $(LIBNAME) $(OBJ) Makefile
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -lft $(READLINE)
	@echo "\033[0;32m"
	@echo " ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    "
	@echo "▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    "
	@echo "▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    "
	@echo "▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    "
	@echo "▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒"
	@echo "░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░"
	@echo "░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░"
	@echo "░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   "
	@echo "       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░"
	@echo "\033[0m"

$(LIBNAME):
	@make -C $(LIBPATH) all

%.o: %.c $(INCS)
	@$(COMP) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ)
	@echo "\033[0;31m$(NAME) clean: \033[0;32mOK\033[0;0m"

fclean:
	@make -C $(LIBPATH) fclean
	@rm -f $(OBJ) $(NAME)
	@echo "\033[0;31m$(NAME) fclean: \033[0;32mOK\033[0;0m"

re: fclean all

.PHONY: all clean fclean re
