/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/12 18:06:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strip_nl(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] != 0 && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = 0;
	return (line);
}

int	spaces_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

char	*ft_str_append(char *s, char c)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = ft_strlen(s);
	new_str = malloc(len + 2);
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	// free(s);
	return (new_str);
}

void	toggle_quteflag_n_increment(char c, int *qute_flag, int *index)
{
	if (c == '"' && *qute_flag == 0)
	{
		*qute_flag = 2;
		(*index)++;
	}
	else if (c == '\'' && *qute_flag == 0)
	{
		*qute_flag = 1;
		(*index)++;
	}
	else if ((c == '\'' && *qute_flag == 1) || (c == '"' && *qute_flag == 2))
	{
		*qute_flag = 0;
		(*index)++;
	}
}

char	*copy_variable_value(char *dst, char *src, int *index)
{
	char	*value;
	char	*name;
	int		j;
	int		name_len;

	name_len = 0;
	j = 0;
	(*index)++;
	name = get_env_name(&src[*index], &name_len);
	if (name == NULL)
		return (dst);
	value = getenv(name);
	if (value == NULL)
		return (dst);
	while (value[j])
		dst = ft_str_append(dst, value[j++]);
	(*index) += name_len + 1;
	return (dst);
}

char	*copy_string(char *s, int *index)
{
	int		qute_flag;
	char	*new_str;

	qute_flag = 0;
	new_str = NULL;
	while (s[*index] != 0 && ((s[*index] != '|' && s[*index] != '>'
				&& s[*index] != '<' && s[*index] != ' ') || qute_flag))
	{
		toggle_quteflag_n_increment(s[*index], &qute_flag, index);
		if (qute_flag == 2 && s[*index] == '$')
			new_str = copy_variable_value(new_str, s, index);
		if (((s[*index] != '"' && s[*index] != '\'') || qute_flag))
		{
			if (((s[*index] == '\n' || s[*index] == '\\')))
			{
				ft_printf("is \\ and flag =%d\n", qute_flag);
				if (qute_flag == 1)
					new_str = ft_str_append(new_str, s[*index]);
			}
			else
				new_str = ft_str_append(new_str, s[*index]);
		}
		(*index)++;
	}
	return (new_str);
}

char	*get_str(char *s, int *index)
{
	int len;
	int i;
	int expanded;
	char *new_str;

	i = 0;
	expanded = 0;
	i += spaces_count(s);
	new_str = copy_string(s, &i);
	i += spaces_count(&s[i]);
	*index = *index + i;
	return (new_str);
}