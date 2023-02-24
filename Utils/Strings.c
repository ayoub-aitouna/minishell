
#include "../minishell.h"

char *m_safe_strjoin(char *s1, char *s2, int free_mode)
{
	char *str = ft_strjoin(s1, s2);
	if (free_mode == 1 || free_mode == 3)
		free(s1);
	if (free_mode == 2 || free_mode == 3)
		free(s2);
	return (str);
}