/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:26:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/09 20:27:00 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '+')
		return (1);
	return (0);
}

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
	int	sym;

	sym = 1;
	while (str && (*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sym *= (-1);
		str++;
	}
	return (count(str, sym));
}

int	main(int ac, char **av)
{
	int		value;
	int		total;
	double	percentage;
	int		i;

	if (ac < 3)
		return (0);
	i = 0;
	value = ft_atoi(av[1]);
	total = ft_atoi(av[2]);
	percentage = (((float)value) / ((float)total));
	printf("\033[A\33[2K\r");
	printf("\r	");
	while (i++ < value)
		printf("\u25A0");
	while (i++ < total)
		printf("\u25A1");
	printf(" %d%%", (int)(percentage * 100));
	printf("\n");
	return (0);
}
