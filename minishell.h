/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:43:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/23 09:43:14 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H
# include "./colors.h"
# include "./exec/builtin/built.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct node
{
	int input_file;
	char *command;
	char **arguments;
	int output_file;
} m_node;

enum file_input
{
	NONE = -3,
	NO_FILE = -1,
	ERROR = -2,
};

int	here_doc(int flag, char *limiter);
void	parse(char *line, t_list **list);
void	tty(void);
size_t	size(char **ptr);
m_node	*new_m_node(void);
void	printf_list(t_list *list);
char	**get_env(char **p);
m_node	*new_m_node(void);
int	spaces_count(char *s);
char	*get_env_name(char *s, int *index);
size_t	size(char **ptr);
char	**append(char **Strings, char *String);
size_t	string_list_len(char **list);
void	exec(t_list *list);
int	open_input_file(char *line, int *i, int input);
int	open_output_file(char *line, int *i, int output);
void	toggle_quteflag(char c, int *qute_flag);
int	toggle_flag(char c, int *qute_flag, int *index);
char	*ft_str_append(char *s, char c);
void	free_list(char **list);
char	*update_command(char *command);
void	clear_node(void *content);
void	handle_sigint(int sig);
char	*get_path(void);
char	*get_fullpath(char *s);
void	print_name(void);
int	handle_syntax(char *line);
int	is_builtin(char *s);
void	handle_sigquit(int sig);
int	is_equal(char *s, char *s2);
void	echo(char **arguments);
void	print_working_directory(void);
int	is_complete(char *line);
char	*copy_variable_value(char *dst, char *src, int *index);
char	*mini_strjoin(char const *s1, char const *s2);
int	is_token_sep(char *c, int i);
char	*concate_str(char *s, char *str, int flag, int *index);
char	*splite_env_val(char *line, char *new_str, m_node *node, int *index);
void	add_arg_t_node(m_node *node, char *str);
char	*get_input_value(char *s, m_node *node, int *index, int mode);
char	*copy_string_t_args(char *s, m_node *node, int *index, int mode);
int	is_qute(char *s, int i);
int	is_n_escaped(char *s, char c, int i);
int	is_between_qute(char *line);
char	*ft_getenv(char *name);
#endif
