/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 06:11:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/14 13:03:17 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"
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
# include "implement_builtins/export/export.h"

int		ft_strcmp(char *s1, char *s2);
void	exit_msg(char *msg, int i);
void	exit_command(t_node *node);
void	env_command(t_node *node, char **env);
void	echo_command(t_node *node);
void	unset(char **str, char **env, int i);
void	cd_command(t_node *node, char **env, char **export);
void	exec(t_list *list);
void	pwd_command(void);
void	export_command(t_node *node, char	**old_export, char	**old_env);
int		f_isdigit(int c);
void	builtins(t_node *node);
char	*get_paths(char **env, char *command);
void	unset_command(t_node *node, char **env);
char	**unset_env(char **str, char **env);
void	remove_env(char **env);
void	remove_ptr(char **env, char *ptr);
char	**update_env(char **env);
void	update(char **env);
void	multiple_pipes(t_node *node, t_list *list, int n_cmd);
char	*change_env(char **env);
char	**the_new_env(char **env, t_node *node);
int		ft_is_alnum(int c);
int		is_high_shlvl(char **env);
char	**necessary_values(char **env, int is_env);
char	**underscore_value(char **env, t_node *node);
char	**check_arguments(char **arguments);
int		is_add_plus_str(char *argument);
int		is_builtins(char *s);
void	child_builtins(t_node *node);

#endif
