LIBFT_SRC_FILES		= libft/ft_putchar_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_strlen.c 

SRC_PRINTF			=

OBJ_FILES		= $(LIBFT_SRC_FILES:.c=.o)
PRINTF_OBJ_FILES		= $(SRC_PRINTF:.c=.o)

RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
AR				= ar rcs

NAME	= libftprintf.a



$(NAME): $(OBJ_FILES) $(PRINTF_OBJ_FILES)
	$(AR) $(NAME) $(OBJ_FILES) $(PRINTF_OBJ_FILES)

all: $(NAME)

clean:
	$(RM) $(OBJ_FILES) $(PRINTF_OBJ_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)


.PHONY: all clean fclean re bonus
