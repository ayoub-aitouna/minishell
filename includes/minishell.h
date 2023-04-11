/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:32:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/09 20:32:57 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./colors.h"
# include "../libft/libft.h"
# include "../Utils/utils.h"
# include "../parsing/parsing.h"
# include "../exec/exec.h"
# include "types.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

size_t	size(char **ptr);
char	**get_env(char **p);
t_node	*new_t_node(void);
void	exec(t_list *list);
void	free_list(char **list);
void	clear_node(void *node);
void	handle_sigint(int sig);
void	print_name(void);
void	handle_sigquit(int sig);
char	*ft_getenv(char *name);
void	printf_arg(char **str);
void	print_table(t_node *node);
void	printf_list(t_list *list);
void	clear_tree(t_tree *node);
void	child_quit(int sig);
char	**get_export(char **p);
#endif
