/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 00:20:37 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/07 08:21:02 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../../../includes/types.h"
# include "../../../includes/minishell.h"
# include "../../exec.h"

void	add_new_env(char **env, char **old_env, char **arguments);
char	**get_new_env(char **old_env, char **arguments);
void	print_export(char **export, m_node *node);
void	export_command(m_node *node, char **old_export, char	**old_env);
char	*add_quotes(char *str, int is_env);
char	*add_plus_string(char **export, char *new_str);
int		is_value(char *argument);
int		get_start(char *argument);
int		is_equal_plus(char *argument);
int		is_forbidden_char(char *argument);
int		string_exists(char **export, int n, char *argument, int len);
void	add_new_export(char **export, char **old_export, char **arguments);
char	**get_new_export(char **old_export, char **str);
char	**reset_forbidden_env(char **name);
char	**reset(char **env, char **argument);
char	**remove_duplicate(char **export);
void	underscore_export(char **export);
char	**export_underscore(char **export, m_node *node);
char	*get_underscore(char **export, m_node *node);
void	sorted_list(char **export, int len);
void	remove_env(char **env);
char	*change_env(char **env);
char	*pwd_env(char **env);

#endif
