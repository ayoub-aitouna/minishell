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
/*   Created: 2023/02/23 09:43:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/23 09:43:14 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./colors.h"
# include "./exec/builtin/built.h"
# include "./libft/libft.h"
# include "Utils/utils.h"
# include "parsing/parsing.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include "types.h"

size_t	size(char **ptr);
char	**get_env(char **p);
m_node	*new_m_node(void);
void	exec(t_list *list);
void	free_list(char **list);
void	clear_node(void *content);
void	handle_sigint(int sig);
void	print_name(void);
void	handle_sigquit(int sig);
char	*ft_getenv(char *name);
void	printf_arg(char **str);
void	print_table(m_node *node);
void	printf_list(t_list *list);
#endif
