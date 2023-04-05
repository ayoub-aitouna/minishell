/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/04 05:09:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	spaces_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

int	is_qute(char *s, int i)
{
	return ((s[i] == '"' || s[i] == '\'') && (i == 0 || (i > 0 && s[i
			- 1] != '\\')));
}

void	add_arg_t_node(m_node *node, char *str)
{
	if (str)
	{
		if (!node->command)
			node->command = ft_strdup(str);
		node->arguments = append(node->arguments, str);
	}
}

char	*get_input_value(char *s, m_node *node, int *index, int mode)
{
	int		i;
	char	*value;

	i = 0;
	i += spaces_count(s);
	value = copy_string_t_args(s, node, &i, mode);
	i += spaces_count(&s[i]);
	*index = *index + i;
	return (value);
}
