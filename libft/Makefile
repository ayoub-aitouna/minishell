SRCS_FILES := ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
	    	ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
			ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
			ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memcpy.c \
			ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
			ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
			ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c \
			ft_printf/src/ft_printf.c ft_printf/src/ft_calc_num_base_size.c \
			ft_printf/src/ft_converter_base_hex.c ft_printf/src/ft_put_unsigned.c\
			ft_printf/src/print_hex.c ft_printf/src/print_ptr_adress.c \
			get_next_line/get_next_line_utils.c get_next_line/get_next_line.c


OBJS_FILES	:= $(SRCS_FILES:.c=.o)

BONUS_FILES	:=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
						ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
						ft_lstmap.c ft_lstnew.c ft_lstsize.c

BONUS_OBJS_FILES	:= $(BONUS_FILES:.c=.o)

CC	:= cc

RM	:= rm -f

CFLAGS	:= 

AR	:= ar crs

NAME	:= libft.a

all:	$(NAME)

$(NAME):	$(OBJS_FILES)
	$(AR) $(NAME) $(OBJS_FILES)

clean:
	$(RM) $(OBJS_FILES) $(BONUS_OBJS_FILES)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)

bonus:	$(OBJS_FILES) $(BONUS_OBJS_FILES)
	$(AR) $(NAME) $(OBJS_FILES) $(BONUS_OBJS_FILES)

.PHONY:	all clean fclean re bonus
