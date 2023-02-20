/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:10:46 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/19 21:16:01 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_str_append(char *s, char c)
{
	int i;
	int len;
	char *new_str;

	i = 0;
	len = ft_strlen(s);
	new_str = malloc((len + 2) * sizeof(char));
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

char *concate_str(char *s, char *str, int flag, int *index)
{
	if (s[0] == '\\')
	{
		if (flag == 1)
			str = ft_str_append(str, s[0]);
		else if (flag == 2 && ft_strchr(">\"\\\'$", s[1]))
			str = ft_str_append(str, s[1]);
		else if (flag == 2 && !ft_strchr(">\"\\\'$", s[1]))
			str = ft_str_append(str, s[0]);
		else if (flag == 0 && ft_strchr(">\"\\\'$", s[1]))
			str = ft_str_append(str, s[1]);
		if (s[1] && ft_strchr(">\"\\\'$", s[1]) && flag != 1)
			(*index)++;
	}
	else if (s[0] == '\n')
	{
		if (flag == 1)
			str = ft_str_append(str, s[0]);
	}
	else
		str = ft_str_append(str, s[0]);
	return (str);
}

void copy_string_t_args(char *s, m_node *node, int *index)
{
	int qute_flag;
	char *new_str;

	qute_flag = 0;
	new_str = NULL;
	while (s[*index] != 0 && (is_token_sep(s, *index) || qute_flag))
	{
		if (is_qute(s, *index))
			toggle_quteflag_n_increment(s[*index], &qute_flag, index);
		if (s[*index] == 0 || !(is_token_sep(s, *index) || qute_flag))
			break;
		if (qute_flag == 0 && is_n_escaped(s, '$', *index))
			splite_env_val(s, node, index);
		else if (qute_flag == 2 && is_n_escaped(s, '$', *index))
		{
			new_str = copy_variable_value(new_str, s, index);
			if ((s[*index] == '"' && qute_flag == 2))
				qute_flag = 0;
		}
		else
			new_str = concate_str(&s[*index], new_str, qute_flag, index);
		(*index)++;
	}
	add_arg_t_node(node, new_str);
}

char *copy_string(char *s, int *index, int expande)
{
	int qute_flag;
	char *new_str;

	qute_flag = 0;
	new_str = NULL;
	while (s[*index] != 0 && (is_token_sep(s, *index) || qute_flag))
	{
		if (is_qute(s, *index) && qute_flag != 0)
		{
			toggle_quteflag(s[*index], &qute_flag);
			(*index)++;
			continue;
		}
		if (qute_flag != 1 && s[*index] == '$' && expande)
		{
			new_str = copy_variable_value(new_str, s, index);
			if ((s[*index] == '"' && qute_flag == 2))
				qute_flag = 0;
		}
		else
			new_str = concate_str(&s[*index], new_str, qute_flag, index);
		(*index)++;
	}
	return (new_str);
}

// sadsd >