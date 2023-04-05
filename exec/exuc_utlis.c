#include "exec.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	
	while(s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);

}

void	exit_msg(char *msg, int i)
{
	printf("%s", msg);
	exit(i);
}

void sorted_list(char **export, int len)
{
	char *temp;
	int i;
	int j;
	
	i = 0;
    while (i < len  - 1) 
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (strcmp(export[j], export[j + 1]) > 0) 
			{
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	f_isdigit(int c)
{
	if (c >= '0' && c <= '8')
		return (1);
	return (0);
}
void remove_env(char **env)
{
	char	**va_unset;
	va_unset = env + 1;
	while (va_unset && *va_unset)
	{
		*(va_unset - 1) = *va_unset;
		va_unset++;
	}
	*(va_unset - 1) = NULL;
	free(*(va_unset));
}
