#ifndef EXEC_H
# define EXEC_H

#include "../includes/minishell.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include "../includes/types.h"


int 	ft_strcmp(char *s1, char *s2);
void	exit_msg(char *msg, int i);
void	exit_command(m_node *node);
void	env_command(m_node *node);
void 	echo_command(m_node *node);
void	unset(char **str, char **env, int i);
void	cd_command(m_node *node, char **env, char **export);
void	exec(t_list *list);
void 	pwd_command(m_node *node);
void	ft_swap(int *a, int *b);
void	export_command(m_node *node, char	**old_export, char	**old_env);
long	long ft_my_atoi(const char *nptr);
void 	print_list(char **str);
int		f_isdigit(int c);
char	**get_new_export(char **env , char **str);
void	builtins(m_node *node);
void	pipe_exec(m_node *node);
char 	*get_paths(char **env , char *command);
void	two_pipes(m_node *node);
int		is_builtins(m_node *node);
void	handle_signal();
void 	sigint_ctrl_C(int sig);
char 	**get_new_env(char **old_env , char **str);
void	sorted_list(char **export, int len);
void	unset_command(m_node *node , char **env);
char	**unset_env(char **str , char **env);
char	**get_new_export(char **old_export, char **str);
void	export_exist_env(char **str, char **env, char **export);
void	remove_env(char **env);
char	**update_env(char **env);
char	*change_env(char **env);
void	update(char **env);
int 	is_forbidden_char(char *str);
int		check_is_command(char **arguments, char **env);
void 	multiple_pipes(m_node *node, t_list *list, char **env);
void	redirect_input(m_node *node);
int		is_plus_equal(char *arguments);
void	add_equal_plus(char **arguments, char **export);
int		is_equal_plus(char *str);
char 	*add_quotes(char *str, int is_env);
char 	*add_plus_string(char **export , char *new_str);
int 	is_value(char *str);
char	**get_name(char **argument);
char 	**reset_forbidden_env(char **name);
int		get_start(char *argument);
char	**reset(char **env, char **argument);
char	**remove_duplicate(char **export);
int 	is_alpha_nbr(char c);
void	underscore_export(char **export);
char 	**export_underscore(char **export, m_node *node);
char	*get_underscore(char **export, m_node *node);
char	**the_new_env(char **env, m_node *node);
void	print_export(char **export, m_node *node);
char 	*shell_level(m_node *node, char **env);

# endif
