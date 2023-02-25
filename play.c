#include "stdio.h"

int	check_syntax(char *line)
{
	int	i;
	int	brackets_flag;

	i = 0;
	brackets_flag = 0;
	while (line[i])
	{
		if (brackets_flag < 0)
			return (0);
		if (line[i] == '(')
			brackets_flag++;
		if (line[i] == ')')
			brackets_flag--;
		i++;
	}
	printf("flag %d", brackets_flag);
	if (brackets_flag != 0)
		return (0);
	return (1);
}
int	main(int ac, char **av)
{
	if (ac > 1)
		printf("line %s, result %d", av[1], check_syntax(av[1]));
}