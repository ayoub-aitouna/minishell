/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:10:46 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/22 15:06:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_append(char *s, char c)
{
	int		i;
	int		len;
	char	*new_str;

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

char	*concate_str(char *s, char *str, int flag, int *index)
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

char	*on_error_clear(char **new_str_spltd, char *env_value, char *new_str,
		int *index)
{
	free_list(new_str_spltd);
	free(env_value);
	if (new_str != NULL)
		free(new_str);
	(*index)++;
	return (NULL);
}

char	*copy_string_t_args(char *s, m_node *node, int *index, int mode)
{
	int		qute_flag;
	char	*new_str;
	char	**new_str_spltd;
	char	*env_value;

	qute_flag = 0;
	new_str = NULL;
	env_value = NULL;
	while (s[*index] != 0 && (is_token_sep(s, *index) || qute_flag))
	{
		if (toggle_flag(s[*index], &qute_flag, index))
			continue ;
		if (is_n_escaped(s, '$', *index) && qute_flag != 1 && mode != 2)
		{
			if (qute_flag == 0 && mode == 0)
				new_str = splite_env_val(s, new_str, node, index);
			else
			{
				env_value = copy_variable_value(env_value, s, index);
				if (qute_flag == 2 && env_value == NULL)
					env_value = ft_str_append(env_value, 0);
				if (env_value != NULL)
				{
					new_str_spltd = ft_split(env_value, ' ');
					if (size(new_str_spltd) > 1 && qute_flag == 0)
						return (on_error_clear(new_str_spltd, env_value,
								new_str, index));
					new_str = mini_strjoin(new_str, env_value);
					if (!env_value)
						free(env_value);
					free_list(new_str_spltd);
				}
				if (qute_flag == 2 && (s[*index] == '"' && qute_flag == 2))
					qute_flag = 0;
			}
		}
		else
			new_str = concate_str(&s[*index], new_str, qute_flag, index);
		(*index)++;
	}
	if (mode != 0)
		return (new_str);
	add_arg_t_node(node, new_str);
	return (NULL);
}
