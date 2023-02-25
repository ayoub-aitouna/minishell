src = main.c parsing/parsing.c parsing/parsing_utils.c parsing/copy_str.c \
		parsing/expand_functions.c parsing/m_node.c parsing/strings_functions.c\
		parsing/files.c parsing/here_doc.c parsing/syntax.c  parsing/start.c\
		parsing/garbage.c  parsing/paths.c  parsing/Signals.c \
		exec/main_exec.c exec/builtin/change_directory.c exec/builtin/echo.c \
		exec/builtin/pwd.c exec/builtin/env.c  Utils/equals.c  Utils/random.c \
		Utils/int_utils.c Utils/status.c Utils/Strings.c parsing/env.c 

obj = ${src:.c=.o}

NAME =  minishell

# CFLAGS = -Wall -Werror -Wextra
incldlib = -I/Users/aaitouna/homebrew/opt/readline/include
libreadline = -lreadline -L/Users/aaitouna/homebrew/opt/readline/lib
libft = libft/libft.a

all: $(NAME)

$(NAME) : $(obj) $(libft)
	gcc $(obj) $(libft) $(libreadline) $() -o $(NAME)

$(libft):
	make bonus --directory=libft

clean_libft:
	make clean  --directory=libft

clean : clean_libft
	rm -rf $(obj) $(mandatory_obj) $(bonus_obj)

fclean : clean clean_libft
	rm -rf $(NAME) $(libft) $(CHECKER)

re : fclean $(NAME)

files = $(shell git diff --name-only HEAD)

commit_and_push: fclean
	git add . && git commit -m "changes $(files)" && git push;