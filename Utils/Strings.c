#include "../minishell.h"

size_t	size(char **ptr)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return (0);
	while (ptr[i])
		i++;
	return (i);
}

char	**append(char **Strings, char *String)
{
	int		i;
	int		len;
	char	**new_Strings;

	i = 0;
	if (Strings == NULL)
		len = 0;
	else
		len = size(Strings);
	new_Strings = malloc((len + 2) * sizeof(char *));
	while (i < len)
	{
		new_Strings[i] = ft_strdup(Strings[i]);
		i++;
	}
	new_Strings[i++] = String;
	new_Strings[i] = NULL;
	if (Strings != NULL)
		free_list(Strings);
	return (new_Strings);
}

char	*m_safe_strjoin(char *s1, char *s2, int free_mode)
{
	char *str = ft_strjoin(s1, s2);
	if (free_mode == 1 || free_mode == 3)
		free(s1);
	if (free_mode == 2 || free_mode == 3)
		free(s2);
	return (str);
}