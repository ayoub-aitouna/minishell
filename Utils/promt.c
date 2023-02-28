/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:50:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/28 12:52:06 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

char	*get_relative_path(char *HOME, char *w_directory)
{
	int		i;
	char	*relative_dir;
	char	*temp;

	relative_dir = NULL;
	i = 0;
	while (w_directory[i] && HOME[i] && w_directory[i] == HOME[i])
		i++;
	relative_dir = ft_str_append(relative_dir, ':');
	relative_dir = ft_str_append(relative_dir, '~');
	while (w_directory[i])
		relative_dir = ft_str_append(relative_dir, w_directory[i++]);
	relative_dir = m_safe_strjoin(relative_dir, RESET, 1);
	relative_dir = ft_str_append(relative_dir, '$');
	relative_dir = ft_str_append(relative_dir, ' ');
	return (relative_dir);
}

char	*get_promt_text(void)
{
	char	*working_directory;
	char	*dir;
	char	*default_promt;
	char	*HOME;
	char	*USER;

	working_directory = getcwd(NULL, 0);
	HOME = getenv("HOME");
	USER = getenv("USER");
	dir = get_relative_path(HOME, working_directory);
	default_promt = m_safe_strjoin(USER, "@", 0);
	default_promt = m_safe_strjoin(default_promt, "Mini-Shell", 1);
	default_promt = m_safe_strjoin(BOLDMAGENTA, default_promt, 2);
	default_promt = m_safe_strjoin(default_promt, RESET, 1);
	default_promt = m_safe_strjoin(default_promt, BOLDBLUE, 1);
	default_promt = m_safe_strjoin(default_promt, dir, 3);
	free(working_directory);
	return (default_promt);
}
