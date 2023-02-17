/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/17 19:38:50 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	spaces_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
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
	if (s != NULL)
		free(s);
	return (new_str);
}

char	*concate_str(char c, char *str, int flag)
{
	char	*res;

	if (((c == '\n' || c == '\\')))
	{
		if (flag == 1)
			res = ft_str_append(str, c);
	}
	else
		res = ft_str_append(str, c);
	if (!str)
		free(str);
	return (res);
}

char	*copy_string(char *s, int *index, int expande)
{
	int		qute_flag;
	char	*new_str;

	qute_flag = 0;
	new_str = NULL;
	while (s[*index] != 0 && ((s[*index] != '|' && s[*index] != '>'
				&& s[*index] != '<' && s[*index] != ' ') || qute_flag))
	{
		toggle_quteflag_n_increment(s[*index], &qute_flag, index);
		if (qute_flag != 1 && s[*index] == '$' && expande)
		{
			new_str = ft_strtrim(copy_variable_value(new_str, s, index), " ");
			if ((s[*index] == '"' && qute_flag == 2))
				qute_flag = 0;
		}
		else if (((s[*index] != '"' && s[*index] != '\'') || qute_flag))
			new_str = concate_str(s[*index], new_str, qute_flag);
		(*index)++;
	}
	return (new_str);
}

char	*get_str(char *s, int *index, int expande)
{
	int		len;
	int		i;
	int		expanded;
	char	*new_str;

	i = 0;
	expanded = 0;
	i += spaces_count(s);
	new_str = copy_string(s, &i, expande);
	i += spaces_count(&s[i]);
	*index = *index + i;
	return (new_str);
}
