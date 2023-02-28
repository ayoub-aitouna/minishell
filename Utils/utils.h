/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:32:59 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/28 12:55:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../minishell.h"
char	*m_safe_strjoin(char *s1, char *s2, int free_mode);
char	*random_string(int len);
int		is_equal(char *s, char *s2);
char	**append(char **Strings, char *String);
char	*get_relative_path(char *HOME, char *w_directory);
char	*get_promt_text(void);
int		list_append(int **list, int new_pid, int size);
void	replace_b_slash(char *ptr);
char	*get_full_line(char *line);
#endif