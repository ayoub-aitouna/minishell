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
main_obj		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(main))
obj				:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(src))
PROGRESSBINARY 	:= $(OBJ_DIR)/progress
Shell_obj		:= ${Shell_src:.c=.o}
#NAMES
Bonus = bonus
NAME =  minishell
USER := $(USER)
cc = cc

CFLAGS		:= -Wall -Werror -Wextra
incldlib	:= -I/Users/${USER}/homebrew/opt/readline/include
libreadline	:= -lreadline -L/Users/${USER}/homebrew/opt/readline/lib
libft		:= libft/libft.a
DUBGGER		:= -fsanitize=address -g3
PROGRESS	:= 0
TOTAL		:= $(words $(src))

all: $(NAME)

$(PROGRESSBINARY) :
	@$(CC) tools/progress.c -o $(PROGRESSBINARY)

$(OBJ_DIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	@$(cc) ${CFLAGS} -c $< -o $@
	@./$(PROGRESSBINARY) $(PROGRESS) $(TOTAL)	
	@$(eval PROGRESS = $(shell expr $(PROGRESS) + 1))

all: $(NAME)

$(NAME) : $(PROGRESSBINARY)  $(main_obj) $(obj) $(libft)
	@ echo "Comiling MINISHELL ..."
	@ ${cc} $(main_obj) $(obj) $(libft) ${CFLAGS} $(libreadline) $(DUBGGER) -o $(NAME)

$(libft):
	@ make -s bonus --directory=libft

clean_libft:
	@ make clean -s  --directory=libft

clean : clean_libft
	@ echo "removing object files ..."
	@ rm -rf $(main_obj) $(Shell_obj) $(obj) $(mandatory_obj) $(bonus_obj) $(PROGRESSBINARY)

fclean : clean clean_libft
	@ echo "removing MINISHELL ..."
	@ rm -rf $(NAME) $(libft) $(CHECKER) $(B_NAME)

re : fclean $(NAME)

files = $(shell git diff --name-only HEAD)

commit_and_push: fclean
	git add . && git commit -m "changes $(files)" && git push;

$(B_NAME): $(Shell_obj)  $(obj) $(libft)
	@ ${cc} -fsanitize=address -g $(Shell_obj) $(obj) $(libft)  $(libreadline) -o $(B_NAME)

$(Bonus): $(B_NAME)
