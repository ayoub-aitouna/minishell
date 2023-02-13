/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/02/13 15:28:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 15:28:48 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./colors.h"
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

int	here_doc(char *limiter);
void	parse_cur_command(char *line, t_list **list);
void	parse(char *line, t_list **list);
void	tty(void);
char	*get_str(char *s, int *index);
size_t	size(char **ptr);
char	*strip_nl(char *line);
m_node	*new_m_node();
void	printf_list(t_list *list);
char	**get_env(char **p);
m_node	*new_m_node(void);
char	*strip_nl(char *line);
char	*get_str(char *s, int *index);
int	spaces_count(char *s);
char	*get_env_name(char *s, int *index);
size_t	size(char **ptr);
char	**append(char **Strings, char *String);
size_t	string_list_len(char **list);
void	exec(void *content);
int	open_input_file(char *line, int *i);
int	open_output_file(char *line, int *i);
char	*check_syntax(char *line, char **msg);
void	toggle_quteflag(char c, int *qute_flag);
void	toggle_quteflag_n_increment(char c, int *qute_flag, int *index);
char	*ft_str_append(char *s, char c);
void	free_list(char **list);
void	update_command(m_node *node);
void	clear_node(void *content);
void	handle_sigint(int sig);
char	*get_path(void);
char	*get_fullpath(char *s);
void	print_name(void);
#endif
