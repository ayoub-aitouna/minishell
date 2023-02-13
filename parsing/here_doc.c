/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:30:17 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/13 16:50:05 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(char *limiter)
{
	char	*line;
	int		fd;

	printf("limiter %s \n", limiter);
	fd = open(".temp_file", O_CREAT | O_RDWR, 0664);
	while (1)
	{
		line = readline("here_doc> ");
		if (line == NULL)
			break ;
		if (ft_strlen(limiter) == ft_strlen(line) && !ft_strncmp(line, limiter,
				ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(fd);
	return (open(".temp_file", O_RDONLY));
}
