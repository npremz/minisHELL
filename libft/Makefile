NAME = libft.a

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_tolower.c ft_toupper.c

SOURCES_BON = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c ft_lstdelone.c

SOURCES_PERS = get_next_line_bonus.c get_next_line_utils_bonus.c chars.c numbers.c ft_printf.c ft_utoa.c ft_utoa_base.c \
				ft_lutoa_base.c ft_isinstr.c ft_atoi_base.c free_utils.c

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BON = $(SOURCES_BON:.c=.o)

OBJECTS_PERS = $(SOURCES_PERS:.c=.o)

HEADER = libft.h

GCC_FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)
	@echo "\033[0;32m"
	@echo " _     ___ ____     ____ ___  __  __ ____ ___ _     _____ ____  "
	@echo "| |   |_ _| __ )   / ___/ _ \|  \/  |  _ \_ _| |   | ____|  _ \ "
	@echo "| |    | ||  _ \  | |  | | | | |\/| | |_) | || |   |  _| | | | |"
	@echo "| |___ | || |_) | | |__| |_| | |  | |  __/| || |___| |___| |_| |"
	@echo "|_____|___|____/   \____\___/|_|  |_|_|  |___|_____|_____|____/ "
	@echo "\033[0m"

$(NAME): $(OBJECTS) $(OBJECTS_BON) $(OBJECTS_PERS)
	@ar -src $(NAME) $(OBJECTS) $(OBJECTS_BON) $(OBJECTS_PERS)

$(OBJECTS):
	@cc $(GCC_FLAGS) -c -I $(HEADER) ${@:.o=.c} -o $@

$(OBJECTS_BON):
	@cc $(GCC_FLAGS) -c -I $(HEADER) ${@:.o=.c} -o $@

$(OBJECTS_PERS):
	@cc $(GCC_FLAGS) -c -I $(HEADER) ${@:.o=.c} -o $@

clean:
	@rm -f $(OBJECTS) ${OBJECTS_BON} $(OBJECTS_PERS)

fclean:
	@rm -f $(NAME) $(OBJECTS) $(OBJECTS_BON) $(OBJECTS_PERS)

re: fclean all

.PHONY: all clean fclean re
