NAME		:= parsing

COMP		:= 	cc
CFLAGS		:= 	-Wall -Wextra -Werror

SRC			:=	main.c ft_exec_cmd_line.c \
				ft_create_token_list.c ft_set_word_token.c \
				ft_set_operator_token.c ft_set_token_value.c \
				ft_token_quote.c ft_token_type_bool.c \
				ft_get_wildcard_cmd_list.c ft_set_wildcard_cmd_list.c \
				ft_set_wildcard_cmd_list_utils.c ft_get_wildcard_value.c \
				ft_wildcard_cmp.c ft_copy_cmd.c \
				ft_unclosed_command_line.c ft_token_parenthesis.c \
				ft_create_cmd_list.c ft_set_cmd.c ft_set_cmd_utils.c \
				ft_create_cmd_tree.c ft_exec_cmd_tree.c ft_launch_exec.c\
				ft_redirection_here_doc.c ft_exec.c ft_exit_child.c \
				ft_token_free.c ft_cmd_free.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
OBJ 		:= $(SRCS:.c=.o)
INC			:= parsing_exec.h
INCS		:= $(addprefix ./includes/, $(INC))

LIBNAME = libft/libft.a
LIBPATH = libft/

all: $(NAME)

bonus: $(NAME_bonus)

$(NAME): $(LIBNAME) $(OBJ) Makefile
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -lft
	@echo "\033[0;34m$(NAME) compilation: \033[0;32mOK\033[0;0m"

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
