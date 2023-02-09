#include "../minishell.h"

int	spaces_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

size_t	calculate_len(char *s)
{
	int		qute_flag;
	size_t	i;

	qute_flag = 0;
	i = 0;
	while (s[i] != 0 && ((s[i] != '|' && s[i] != '>' && s[i] != '<'
				&& s[i] != ' ') || qute_flag))
	{
		if (s[i] == '"' && qute_flag == 0)
			qute_flag = 2;
		else if (s[i] == '\'' && qute_flag == 0)
			qute_flag = 1;
		else if ((s[i] == '\'' && qute_flag == 1) || (s[i] == '"'
					&& qute_flag == 2))
			qute_flag = 0;
		i++;
	}
	qoute(qute_flag, 0);
	return (i);
}

char	*get_str(char *s, int *index)
{
	int		len;
	int		i;
	char	*new_str;

	i = 0;
	i += spaces_count(s);
	len = calculate_len(&s[i]);
	new_str = malloc(len + 1);
	ft_strlcpy(new_str, &s[i], len + 1);
	i += spaces_count(&s[i + len]);
	*index = *index + i + len;
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
		i++;
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
