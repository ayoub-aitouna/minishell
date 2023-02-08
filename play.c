#include"minishell.h"
#include<stdio.h>

int Score(int set, int getter_setter)
{
	static int a = 0;
	if(getter_setter == -1)
		return (a);
	a = set;
	return (a);
}

int main()
{
	int i = 0;
	while (i < 10)
	{
		if(i > 1 && i % 2 == 0)
			Score(i, 0);
		printf("the score is %d \n", Score(0, -1));
		i++;
	}
}