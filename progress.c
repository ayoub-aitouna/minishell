#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "includes/colors.h"

int ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '+')
		return (1);
	return (0);
}

static int count(const char *str, int sym)
{
	unsigned long long res;

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

int ft_atoi(const char *str)
{
	int sym;

	sym = 1;
	while (str && (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sym *= (-1);
		str++;
	}
	return (count(str, sym));
}

int main(int ac, char **av)
{
	int value;
	int total;
	double persontage;
	int i;

	if(ac < 3)
		return (0);
	i = 0;
	value = ft_atoi(av[1]);
	total = ft_atoi(av[2]);
	persontage = (((float)value) / ((float)total));
	printf("\033[A\33[2KT\r");
	printf("\rprogress %.3d, total %.3d persontage %.3d%%[", value, total, (int)(persontage * 100));
	while (i++ < value)
		printf(BLUE "#" RESET);
	if (i < total)
		printf(RED ">" RESET);
	else
		printf(BLUE "#" RESET);
	while (i++ < total)
		printf("_");
	printf("]\n");
	return (0);
}
