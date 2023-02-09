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
/*   Created: 2023/02/09 16:32:17 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/09 16:32:17 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
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
int	qoute(int i, int mode);
char	**get_env(char **p);
m_node	*new_m_node(void);
char	*strip_nl(char *line);
char	*get_str(char *s, int *index);
int	spaces_count(char *s);
char	*get_env_name(char *s);
size_t	calculate_len(char *s, int *expanded);
void	copy_expanded(char *dst, char *src, int len);
size_t	size(char **ptr);
char	**append(char **Strings, char *String);
#endif
