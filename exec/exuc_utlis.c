/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_utlis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 06:08:19 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/11 13:16:34 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);
}

void	exit_msg(char *msg, int i)
{
	printf("%s", msg);
	printf("killing by %d \n", i);
	exit(i);
}

int	f_isdigit(int c)
{
	if (c >= '0' && c <= '8')
		return (1);
	return (0);
}

int	ft_is_alnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) \
		|| (c >= 48 && c <= 57) || c == '_')
		return (1);
	return (0);
}
