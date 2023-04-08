/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:38:16 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/08 05:38:11 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(const char *str, int sym)
{
	unsigned long long	res;

	res = 0;
	while (str && ft_isdigit(*str))
	{
		res = 10 * res + (*str - '0');
		if (res > 9223372036854775807 && sym == 1)
			return (-1);
		if (res > 9223372036854775807 && sym == -1)
			return (0);
		str++;
	}
	return (res * sym);
}

int	ft_atoi(const char *str)
{
	int					sym;

	sym = 1;
	while (str && (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
			|| *str == '\r' || *str == ' '))
		str++;
	if (str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sym *= (-1);
		str++;
	}
	return (count(str, sym));
}
