/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 06:11:06 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/08 08:13:58 by kmahdi           ###   ########.fr       */
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
void	exit_command(m_node *node);
void	env_command(m_node *node);
void	echo_command(m_node *node);
void	unset(char **str, char **env, int i);
void	cd_command(m_node *node, char **env, char **export);
void	exec(t_list *list);
void	pwd_command(void);
void	export_command(m_node *node, char	**old_export, char	**old_env);
int		f_isdigit(int c);
void	builtins(m_node *node);
char	*get_paths(char **env, char *command);
int		is_builtins(m_node *node);
void	unset_command(m_node *node, char **env);
char	**unset_env(char **str, char **env);
void	remove_env(char **env);
char	**update_env(char **env);
void	update(char **env);
void	multiple_pipes(m_node *node, t_list *list, int n_cmd);
char	*change_env(char **env);
char	**the_new_env(char **env, m_node *node);
int		ft_is_alnum(int c);
int		is_high_shlvl(char **env);
char	**necessary_values(char **env);

#endif
