#include "minishell.h"
#include <stdio.h>

int	Score(int set, int getter_setter)
{
	static int	a;

	a = 0;
	if (getter_setter == -1)
		return (a);
	a = set;
	return (a);
}

size_t	calculate_len(int *expanded)
{
	*expanded = (*expanded) + 10;
	printf("%d", (*expanded) + 10);
	return (0);
}

int	main(void)
{
	int i = 0;
	calculate_len(&i);
	printf("PATH = %s ", getenv("LL"));
}