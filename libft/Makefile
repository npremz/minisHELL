NAME		:=		libft.a

COMP		:=		cc
CFLAGS		:=		-Wall -Wextra -Werror

SRC_io		:= 		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c get_next_line.c ft_printf.c \
					ft_putnbr_flag.c ft_putpointer_flag.c ft_putstr_flag.c \
					ft_setflag.c ft_conversion.c

SRC_string	:= 		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_strlen.c \
					ft_strchr.c ft_strrchr.c ft_strlcpy.c ft_strlcat.c \
					ft_strncmp.c ft_strnstr.c ft_strdup.c ft_striteri.c \
					ft_strmapi.c ft_substr.c ft_strtrim.c ft_strjoin.c \
					ft_split.c ft_atoi.c ft_atod.c ft_itoa.c \
					ft_itoa.c

SRC_memory	:= 		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
					ft_memchr.c ft_memcmp.c ft_calloc.c ft_free.c

SRC_list	:= 		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c  ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
					ft_lstmap.c

SRC_other	:= 		ft_ternary_op.c

SRCS_io		:= 		$(addprefix ./srcs/io/, $(SRC_io))
SRCS_string	:= 		$(addprefix ./srcs/string/, $(SRC_string))
SRCS_memory	:= 		$(addprefix ./srcs/memory/, $(SRC_memory))
SRCS_list	:= 		$(addprefix ./srcs/list/, $(SRC_list))
SRCS_other	:= 		$(addprefix ./srcs/other/, $(SRC_other))
SRCS		:= 		$(SRCS_io) $(SRCS_string) $(SRCS_memory) $(SRCS_list) $(SRCS_other)
OBJ			:=		$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rsc $(NAME) $(OBJ)
	@echo "\033[0;34mlibft compilation: \033[0;32mOK\033[0;0m"

%.o: %.c
	@$(COMP) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[0;31mlibft clean: \033[0;32mOK\033[0;0m"

fclean:
	@rm -f $(OBJ) $(NAME)
	@echo "\033[0;31mlibft fclean: \033[0;32mOK\033[0;0m"

re: fclean all

.PHONY: all clean fclean re
