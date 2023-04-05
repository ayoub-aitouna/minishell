/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:21:25 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*random_string(int len)
{
	char	*str;
	char	*buff;
	int		fd;
	int		i;
	int		index;

	str = malloc(len + 1);
	buff = malloc(1);
	fd = open("/dev/random", O_RDONLY);
	i = 0;
	index = 0;
	while (i < 100 && index <= len)
	{
		if (read(fd, buff, 1) == -1)
			break ;
		if (ft_isalnum(buff[0]))
			str[index++] = buff[0];
		i++;
	}
	str[index] = 0;
	return (str);
}
