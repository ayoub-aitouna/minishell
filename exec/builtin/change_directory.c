/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:22:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/14 14:36:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

char	*get_directory(char *directory)
{
	char	*new_directory;
	char	*HOME;
	int		i;

	i = 0;
	HOME = getenv("HOME");
	new_directory = NULL;
	if (directory == NULL || !ft_strlen(directory))
		return (HOME);
	if (directory[0] == '~')
	{
		while (HOME[i])
			new_directory = ft_str_append(new_directory, HOME[i++]);
		i = 1;
		while (directory[i])
			new_directory = ft_str_append(new_directory, directory[i++]);
		return (new_directory);
	}
	return (directory);
}

void	change_directory(char *directory)
{
	chdir(get_directory(directory));
}
