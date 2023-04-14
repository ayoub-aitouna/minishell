src = parsing/parsing.c\
        parsing/parsing_utils.c\
        parsing/copy_str.c \
        parsing/expand_functions.c \
        parsing/t_node.c \
        parsing/strings_functions.c\
        parsing/files.c\
        parsing/here_doc.c\
        parsing/syntax/syntax.c\
        parsing/syntax/helper.c\
        parsing/start.c\
        parsing/garbage.c \
        parsing/paths.c \
        parsing/Signals.c \
        parsing/print.c \
        Utils/equals.c\
        Utils/random.c\
        Utils/int_utils.c\
        Utils/status.c\
        Utils/Strings.c\
        parsing/env.c \
        Utils/promt.c\
        Utils/full_line.c\
        Utils/her_doc_interrupte.c \
        exec/exec.c \
        exec/exuc_utlis.c\
        exec/implement_builtins/echo.c\
        exec/implement_builtins/unset.c\
        exec/implement_builtins/export/export.c\
        exec/implement_builtins/export/underscore_env.c \
        exec/implement_builtins/export/export_utils.c\
        exec/implement_builtins/export/export_env.c\
        exec/implement_builtins/export/main_export.c\
        exec/implement_builtins/export/reset_export.c\
        exec/implement_builtins/exit.c\
        exec/implement_builtins/env.c\
        exec/implement_builtins/cd_pwd.c\
        exec/implement_builtins/builtins.c\
        exec/pipes/get_path.c \
        exec/pipes/piping.c\
        exec/implement_builtins/export//export_equal.c\

main = main/main.c

B_NAME = bonushell
Shell_src = Shell/main.c\
        Shell/tree.c\
        Shell/exec/exec.c

# Directories
OBJ_DIR := objects

#object files
main_obj                := $(patsubst %.c,$(OBJ_DIR)/%.o,$(main))
obj                             := $(patsubst %.c,$(OBJ_DIR)/%.o,$(src))
PROGRESSBINARY  := $(OBJ_DIR)/progress
Shell_obj               := ${Shell_src:.c=.o}
#NAMES
Bonus = bonus
NAME =  minishell
USER := $(USER)
cc = cc
files = $(shell git diff --name-only HEAD)

# CFLAGS          := -Wall -Werror -Wextra
incldlib        := -I/Users/${USER}/homebrew/opt/readline/include
libreadline     := -lreadline -L/Users/${USER}/homebrew/opt/readline/lib
libft           := libft/libft.a
DUBGGER         := -fsanitize=address -g3
PROGRESS        := 0
newer_file      := $(SRCS_FILES)
TOTAL           := $(words $(newer_file))

all: updated_files CALC_TOTAL $(NAME)

updated_files :
	$(eval newer_file = $(shell (find . -name "*.c" -not -path "./libft/*"  -type f -newer $(NAME)) 2>/dev/null || find . -name "*.c" -type f -not -path "./libft/*"))

CALC_TOTAL : $(updated_files)
	$(eval TOTAL = $(shell expr $(words $(newer_file)) - 1))

$(PROGRESSBINARY) :
	@$(CC) tools/progress.c -o $(PROGRESSBINARY)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(cc) ${CFLAGS} -c $< -o $@
	@$(eval PROGRESS = $(shell expr $(PROGRESS) + 1))
	@./$(PROGRESSBINARY) $(PROGRESS) $(TOTAL)

all: $(NAME)

$(NAME) : $(PROGRESSBINARY)  $(main_obj)  $(obj) $(libft)
	@ echo "Compiling MINISHELL "
	@ ${cc} $(main_obj) $(obj) $(libft) ${CFLAGS} $(libreadline) $(DUBGGER) -o $(NAME)
	@ echo "\tDone.\n"

$(libft):
	@ make -s bonus --directory=libft

clean_libft:
	@ make clean -s  --directory=libft

clean : clean_libft
	@ echo "Removing object files ."
	@ rm -rf $(main_obj) $(Shell_obj) $(obj) $(mandatory_obj) $(bonus_obj) $(PROGRESSBINARY)
	@ echo "\tDone.\n"

fclean : clean clean_libft
	@ echo "Removing $(NAME) ."
	@ rm -rf $(NAME) $(libft) $(CHECKER) $(B_NAME)
	@ echo "\tDone.\n"

re : fclean all

commit_and_push: fclean
	git add . && git commit -m "changes $(files)" && git push;

.PHONY : clean flcean updated_files CALC_TOTAL commit_and_push clean_libft
