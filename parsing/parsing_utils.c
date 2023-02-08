#include "../minishell.h"

int	spaces_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

char	*get_str(char *s, int *index)
{
	int		len;
	int		i;
	int		j;
	int		k;
	int		flag;
	char	*new_str;

	len = 0;
	i = 0;
	k = 0;
	flag = 0;
	i += spaces_count(s);
	j = i;
	while (s[i] != 0 && ((s[i] != '|' && s[i] != '>' && s[i] != '<'
				&& s[i] != ' ') || flag))
	{
		if (s[i] == '\'' && flag == 0)
			flag = 1;
		else if (s[i] == '\'')
			flag = 0;
		i++;
		len++;
	}
	new_str = malloc(len + 1);
	ft_strlcpy(new_str, &s[j], len + 1);
	i += spaces_count(&s[i]);
	*index = *index + i;
	return (new_str);
}

size_t	size(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i++])
		;
	return (i);
}
char	*strip_nl(char *line)
{
	int	i;

	i = 0;
	while (line[i] != 0 && line[i] != '\n')
	{
		i++;
	}
	if (line[i] == '\n')
		line[i] = 0;
	return (line);
}

m_node	*new_m_node()
{
	m_node	*new_node;

	new_node = malloc(sizeof(m_node));
	if (!new_node)
		return (NULL);
	new_node->input_file = -1;
	new_node->commend = NULL;
	new_node->arguments = NULL;
	new_node->output_file = -1;
	return (new_node);
}
