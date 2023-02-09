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
	readline();
}