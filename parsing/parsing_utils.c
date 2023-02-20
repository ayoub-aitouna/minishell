/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/20 04:44:58 by aaitouna         ###   ########.fr       */
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

int	is_qute(char *s, int i)
{
	return ((s[i] == '"' || s[i] == '\'') && (i == 0 || i > 0 && s[i
			- 1] != '\\'));
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

void	parse_arguments(char *s, m_node *node, int *index)
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