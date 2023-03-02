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
#define MINISHELL_H
#include "./colors.h"
#include "./exec/builtin/built.h"
#include "./libft/libft.h"
#include "Utils/utils.h"
#include "parsing/parsing.h"
#include "types.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

size_t size(char **ptr);
char **get_env(char **p);
m_node *new_m_node(void);
void exec(t_list *list);
void free_list(char **list);
void clear_node(void *node);
void handle_sigint(int sig);
void print_name(void);
void handle_sigquit(int sig);
char *ft_getenv(char *name);
void printf_arg(char **str);
void print_table(m_node *node);
void printf_list(t_list *list);
void clear_tree(t_tree *node);
int proccess(m_node *node, int in_fd, int out_fd, int len, int index);
void run_built_in(m_node *node);
int handle_fd(int *fd);
int reset(int **proccess, int len, int pid);
#endif
