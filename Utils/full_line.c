/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Full_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:53:29 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/28 12:54:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	replace_b_slash(char *ptr)
{
	int	i;

	i = ft_strlen(ptr);
	while (i >= 0 && ptr[i] != '\\' && ptr[i] != '|')
		i--;
	if (is_n_escaped(ptr, '\\', i))
		ptr[i] = 0;
}

char	*get_full_line(char *line)
{
	char	*temp;
	char	*new_line;

	while (!is_complete(line))
	{
		replace_b_slash(line);
		new_line = readline(">");
		if (!new_line)
		{
			return (NULL);
		}
		temp = ft_strjoin(line, new_line);
		free(line);
		free(new_line);
		line = temp;
	}
	return (line);
}
