/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/18 19:30:13 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int spaces_count(char *s)
{
	int i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

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
		else if (flag == 2)
			str = ft_str_append(str, s[0]);
		else if (s[1] && ft_strchr("\"\\\'", s[1]))
			str = ft_str_append(str, s[1]);
		if (s[1] && ft_strchr("\"\\\'", s[1]) && flag != 1)
			(*index)++;
	}
	else if (s[0] == '\n')
	{
		if (flag == 1)
			str = ft_str_append(str, s[0]);
		else
			str = str;
	}
	else
		str = ft_str_append(str, s[0]);
	return (str);
}

char *copy_string(char *s, int *index, int expande)
{
	int qute_flag;
	char *new_str;

	qute_flag = 0;
	new_str = NULL;
	while (s[*index] != 0 && (is_token_sep(s[*index]) || qute_flag))
	{
		if (s[*index] == '"' || s[*index] == '\'')
			toggle_quteflag(s[*index], &qute_flag);
		else
		{
			if (qute_flag != 1 && s[*index] == '$' && expande)
			{
				new_str = copy_variable_value(new_str, s, index);
				if ((s[*index] == '"' && qute_flag == 2))
					qute_flag = 0;
			}
			else if (((s[*index] != '"' && s[*index] != '\'') || qute_flag))
				new_str = concate_str(&s[*index], new_str, qute_flag, index);
		}
		(*index)++;
	}
	return (new_str);
}

void copy_string_t_args(char *s, m_node *node, int *index)
{
	int qute_flag;
	char *new_str;

	qute_flag = 0;
	new_str = NULL;
	while (s[*index] != 0 && (is_token_sep(s[*index]) || qute_flag))
	{
		if (s[*index] == '"' || s[*index] == '\'')
			toggle_quteflag(s[*index], &qute_flag);
		else
		{
			if (qute_flag == 0 && s[*index] == '$')
				splite_env_val(s, node, index);
			else if (qute_flag == 2 && s[*index] == '$')
			{
				new_str = copy_variable_value(new_str, s, index);
				if ((s[*index] == '"' && qute_flag == 2))
					qute_flag = 0;
			}
			else
				new_str = concate_str(&s[*index], new_str, qute_flag, index);
		}
		(*index)++;
	}
	add_arg_t_node(node, new_str);
}

void add_arg_t_node(m_node *node, char *str)
{
	if (str)
	{
		if (!node->command)
			node->command = ft_strdup(str);
		printf("132 : %p\n", str);
		node->arguments = append(node->arguments, str);
	}
}

char *get_str(char *s, int *index, int expande)
{
	int len;
	int i;
	int expanded;
	char *new_str;

	i = 0;
	expanded = 0;
	i += spaces_count(s);
	new_str = copy_string(s, &i, expande);
	i += spaces_count(&s[i]);
	*index = *index + i;
	return (new_str);
}

void parse_arguments(char *s, m_node *node, int *index)
{
	int len;
	int i;
	int expanded;

	i = 0;
	expanded = 0;

	i += spaces_count(s);
	copy_string_t_args(s, node, &i);
	i += spaces_count(&s[i]);
	*index = *index + i;
}