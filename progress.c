#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

int main(int ac, char **av)
{
	int value = 0;
	int total = 0;
	int i = 0;

	if(ac >= 3)
	{
		value = ft_atoi(av[1]);
		total = ft_atoi(av[2]);
	}
	printf("\e[1;1H\e[2J\n");
	printf("\rprogress %d, total %d [", value , total);
	while (i < value) {
		printf("=");
		i++;
	}
	printf(">");
	while (i < total) {
		printf(" ");
		i++;
	}
	printf("]\n");
	usleep(100000);
	return (0);
}
